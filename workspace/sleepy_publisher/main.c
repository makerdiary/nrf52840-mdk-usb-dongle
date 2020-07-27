// generic imports
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// nrf
#include "app_scheduler.h"
#include "app_timer.h"
#include "bsp_thread.h"
#include "nrf_log_ctrl.h"
#include "nrf_log.h"
#include "nrf_log_default_backends.h"

// timer
#include "nrf.h"
#include "nrf_drv_timer.h"
#include "bsp.h"
#include "app_error.h"

// saadc
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"

// mqtt
#include "mqttsn_client.h"

// thread
#include "thread_utils.h"

#include <openthread/thread.h>
#include <openthread/thread_ftd.h>
#include <openthread/dataset_ftd.h>
#include <openthread/config.h>
#include <openthread/cli.h>
#include <openthread/diag.h>
#include <openthread/tasklet.h>
#include <openthread/platform/logging.h>

#define SCHED_QUEUE_SIZE      32                              /**< Maximum number of events in the scheduler queue. */
#define SCHED_EVENT_DATA_SIZE APP_TIMER_SCHED_EVENT_DATA_SIZE /**< Maximum app_scheduler event size. */

// mqtt-sn

#define DEFAULT_CHILD_TIMEOUT    40                                         /**< Thread child timeout [s]. */
#define DEFAULT_POLL_PERIOD      1000                                       /**< Thread Sleepy End Device polling period when MQTT-SN Asleep. [ms] */
#define SHORT_POLL_PERIOD        100                                        /**< Thread Sleepy End Device polling period when MQTT-SN Awake. [ms] */
#define SEARCH_GATEWAY_TIMEOUT   5                                          /**< MQTT-SN Gateway discovery procedure timeout in [s]. */                                   

static mqttsn_client_t      m_client;                                       /**< An MQTT-SN client instance. */
static mqttsn_remote_t      m_gateway_addr;                                 /**< A gateway address. */
static uint8_t              m_gateway_id;                                   /**< A gateway ID. */
static mqttsn_connect_opt_t m_connect_opt;                                  /**< Connect options for the MQTT-SN client. */
static uint16_t             m_msg_id           = 0;                         /**< Message ID thrown with MQTTSN_EVENT_TIMEOUT. */
static char                 m_client_id[]      = "nRF52840_publisher";      /**< The MQTT-SN Client's ID. */
static char                 m_topic_name[]     = "nRF52840_resources/led3"; /**< Name of the topic corresponding to subscriber's BSP_LED_2. */
static mqttsn_topic_t       m_topic            =                            /**< Topic corresponding to subscriber's BSP_LED_2. */
{
    .p_topic_name = (unsigned char *)m_topic_name,
    .topic_id     = 0,
};

static void bsp_event_handler(bsp_event_t event);

// end mqtt sn
// saadc

#define SAMPLES_IN_BUFFER 5
volatile uint8_t state = 1;

static const nrf_drv_timer_t m_timer = NRF_DRV_TIMER_INSTANCE(2);
static nrf_saadc_value_t     m_buffer_pool[2][SAMPLES_IN_BUFFER];
static nrf_ppi_channel_t     m_ppi_channel;
static uint32_t              m_adc_evt_counter;

// end saadc

static void find_gateway();
static bool has_valid_role();
static void wake_up(void);
static void set_radio_on(void);
static void set_radio_off(void);

/***************************************************************************************************
 * @section State
 **************************************************************************************************/

static void thread_state_changed_callback(uint32_t flags, void * p_context)
{
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "State changed! Flags: 0x%08x Current role: %d\r\n",
                 flags, otThreadGetDeviceRole(p_context));
    LEDS_OFF(LEDS_MASK);
}

/***************************************************************************************************
 * @section Initialization
 **************************************************************************************************/

/**@brief Function for initializing the Application Timer Module.
 */
static void timer_init(void)
{
    uint32_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for initializing the LEDs.
 */
static void leds_init(void)
{
    LEDS_CONFIGURE(LEDS_MASK);
    LEDS_OFF(LEDS_MASK);
}

/**@brief Function for initializing the nrf log module.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

/**@brief Function for initializing the Thread Board Support Package.
 */
static void thread_bsp_init(void)
{
    uint32_t err_code;
    err_code = bsp_init(BSP_INIT_LEDS | BSP_INIT_BUTTONS, bsp_event_handler);
    APP_ERROR_CHECK(err_code);

    err_code = bsp_thread_init(thread_ot_instance_get());
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for initializing the Thread Stack.
 */
static void thread_instance_init(void)
{
    thread_configuration_t thread_configuration =
    {
        .radio_mode            = THREAD_RADIO_MODE_RX_OFF_WHEN_IDLE,
        .autocommissioning     = true,
        .poll_period           = DEFAULT_POLL_PERIOD,
        .default_child_timeout = DEFAULT_CHILD_TIMEOUT,
    };

    thread_init(&thread_configuration);
    // thread_cli_init();
    thread_state_changed_callback_set(thread_state_changed_callback);
}

/**@brief Function for deinitializing the Thread Stack.
 *
 */
// static void thread_instance_finalize(void)
// {
//     bsp_thread_deinit(thread_ot_instance_get());
//     thread_soft_deinit();
// }

/**@brief Function for initializing scheduler module.
 */
// static void scheduler_init(void)
// {
//     APP_SCHED_INIT(SCHED_EVENT_DATA_SIZE, SCHED_QUEUE_SIZE);
// }

void setNetworkConfiguration(otInstance *aInstance)
{
    otOperationalDataset aDataset;

    memset(&aDataset, 0, sizeof(otOperationalDataset));
   
    aDataset.mActiveTimestamp                      = 1;
    aDataset.mComponents.mIsActiveTimestampPresent = true;
     
    aDataset.mChannel                      = 15;
    aDataset.mComponents.mIsChannelPresent = true;
    
    aDataset.mPanId                      = (otPanId)0x1234;
    aDataset.mComponents.mIsPanIdPresent = true;

    uint8_t MeshLocalPrefix[OT_PSKC_MAX_SIZE] = {0xfd, 0x11, 0x11, 0x11, 0x22, 0x22, 0x00, 0x00};
    memcpy(aDataset.mMeshLocalPrefix.m8, MeshLocalPrefix, sizeof(aDataset.mMeshLocalPrefix));
    aDataset.mComponents.mIsMeshLocalPrefixPresent = true;

    uint8_t key[OT_MASTER_KEY_SIZE] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    memcpy(aDataset.mMasterKey.m8, key, sizeof(aDataset.mMasterKey));
    aDataset.mComponents.mIsMasterKeyPresent = true;

#if OPENTHREAD_FTD
    otDatasetSetActive(aInstance, &aDataset);
#else
    OT_UNUSED_VARIABLE(aInstance);
#endif
}

/***************************************************************************************************
 * @section MQTT-SN
 **************************************************************************************************/


static bool has_valid_role() 
{
    if (otThreadGetDeviceRole(thread_ot_instance_get()) < OT_DEVICE_ROLE_CHILD )
    {
        // otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "THREAD: Got role < CHILD");
        return false;
    }
    return true;
}

static void find_gateway() 
{
    if (!has_valid_role()) 
    {
        return;
    }
    wake_up();
    set_radio_on();

    uint32_t err_code = mqttsn_client_search_gateway(&m_client, SEARCH_GATEWAY_TIMEOUT);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("SEARCH GATEWAY message could not be sent. Error: 0x%x\r\n", err_code);
        otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "SEARCH GATEWAY message could not be sent. Error: 0x%x\r\n", err_code);
    }
}

static void connect_mqttsn()
{
    if (!has_valid_role()) 
    {
        return;
    }
    wake_up();
    set_radio_on();

    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "Sent CONNECT");
    uint32_t err_code = mqttsn_client_connect(&m_client, &m_gateway_addr, m_gateway_id, &m_connect_opt);
    if (err_code != NRF_SUCCESS)
    {
        otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "CONNECT message could not be sent. Error: 0x%x\r\n", err_code);
    }
}

/**@brief Turns the MQTT-SN network indication LED on.
 *
 * @details This LED is on when an MQTT-SN client is in connected or awake state.
 */
// static void light_on(void)
// {
//     // BSP_LED_0_MASK = red
//     // BSP_LED_1_MASK = blue
//     // BSP_LED_2_MASK = green
//     otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "light_on");
//     LEDS_ON(BSP_LED_1_MASK);
// }

/**@brief Turns the MQTT-SN network indication LED off.
 *
 * @details This LED is on when an MQTT-SN client is in disconnected or asleep state.
 */
// static void light_off(void)
// {
//     otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "light_off");
//     LEDS_OFF(BSP_LED_1_MASK);
// }

/**@brief Puts MQTT-SN client in sleep mode.
 *
 * @details This function changes Thread Sleepy End Device polling period to default.
 */
static void sleep(void)
{
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "sleep");
    otError error;

    error = otLinkSetPollPeriod(thread_ot_instance_get(), DEFAULT_POLL_PERIOD);
    ASSERT(error == OT_ERROR_NONE);
}

/**@brief Puts MQTT-SN client in active mode.
 *
 * @details This function changes Thread Sleepy End Device polling period to short.
 */
static void wake_up(void)
{
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "wake_up");
    otError error;

    error = otLinkSetPollPeriod(thread_ot_instance_get(), SHORT_POLL_PERIOD);
    ASSERT(error == OT_ERROR_NONE);
}

/**@brief Initializes MQTT-SN client's connection options.
 */
static void connect_opt_init(void)
{
    m_connect_opt.alive_duration = MQTTSN_DEFAULT_ALIVE_DURATION,
    m_connect_opt.clean_session  = MQTTSN_DEFAULT_CLEAN_SESSION_FLAG,
    m_connect_opt.will_flag      = MQTTSN_DEFAULT_WILL_FLAG,
    m_connect_opt.client_id_len  = strlen(m_client_id),

    memcpy(m_connect_opt.p_client_id, (unsigned char *)m_client_id, m_connect_opt.client_id_len);
}

/**@brief Processes GWINFO message from a gateway.
 *
 * @details This function initializes MQTT-SN Client's connect options and launches the connect procedure.
 *
 * @param[in]    p_event  Pointer to MQTT-SN event.
 */
static void gateway_info_callback(mqttsn_event_t * p_event)
{
    m_gateway_addr  = *(p_event->event_data.connected.p_gateway_addr);
    m_gateway_id    = p_event->event_data.connected.gateway_id;
}

/**@brief Processes CONNACK message from a gateway.
 *
 * @details This function launches the topic registration procedure if necessary.
 */
static void connected_callback(void)
{
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "connected_callback");

    set_radio_off();

    uint32_t err_code = mqttsn_client_topic_register(&m_client,
                                                     m_topic.p_topic_name,
                                                     strlen(m_topic_name),
                                                     &m_msg_id);
    if (err_code != NRF_SUCCESS)
    {
        otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "REGISTER message could not be sent. Error code: 0x%x\r\n", err_code);
    }
}

/**@brief Processes DISCONNECT message from a gateway. */
static void disconnected_callback(void)
{
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "disconnected_callback");
    sleep();
}

/**@brief Processes REGACK message from a gateway.
 *
 * @details This function puts the client in sleep mode.
 *
 * @param[in] p_event Pointer to MQTT-SN event.
 */
static void regack_callback(mqttsn_event_t * p_event)
{
    m_topic.topic_id = p_event->event_data.registered.packet.topic.topic_id;
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "MQTT-SN event: Topic has been registered with ID: %d.\r\n",
                 p_event->event_data.registered.packet.topic.topic_id);

    sleep();
}

/**@brief Processes PUBACK message from a gateway.
 *
 * @details This function puts the client in sleep mode.
 */
static void puback_callback(void)
{
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "puback_callback");
    sleep();
}

/**@brief Processes DISCONNECT message being a response to sleep request.
 *
 * @details This function puts the client in sleep mode.
 */
static void sleep_callback(void)
{
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "sleep_callback");
    sleep();
}

/**@brief Processes callback from keep-alive timer timeout.
 *
 * @details This function puts the client in active mode.
 */
static void wakeup_callback(void)
{
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "wakeup_callback");
    wake_up();
}

/**@brief Processes retransmission limit reached event. */
static void timeout_callback(mqttsn_event_t * p_event)
{
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "MQTT-SN event: Timed-out message: %d. Message ID: %d.\r\n",
                  p_event->event_data.error.msg_type,
                  p_event->event_data.error.msg_id);

}

/**@brief Processes results of gateway discovery procedure. */
static void searchgw_timeout_callback(mqttsn_event_t * p_event)
{
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "MQTT-SN event: Gateway discovery result: 0x%x.\r\n", p_event->event_data.discovery);
    sleep();

}

/**@brief Function for handling MQTT-SN events. */
void mqttsn_evt_handler(mqttsn_client_t * p_client, mqttsn_event_t * p_event)
{
    switch (p_event->event_id)
    {
        case MQTTSN_EVENT_GATEWAY_FOUND:
            otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "MQTT-SN event: Client has found an active gateway.");
            gateway_info_callback(p_event);
            connect_mqttsn();
            break;

        case MQTTSN_EVENT_CONNECTED:
            otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "MQTT-SN event: Client connected.");
            connected_callback();
            break;

        case MQTTSN_EVENT_DISCONNECTED:
            otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "MQTT-SN event: Client disconnected.");
            disconnected_callback();
            break;

        case MQTTSN_EVENT_REGISTERED:
            otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "MQTT-SN event: Client registered topic.");
            regack_callback(p_event);
            break;

        case MQTTSN_EVENT_PUBLISHED:
            otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "MQTT-SN event: Client has successfully published content.");
            puback_callback();
            break;

        case MQTTSN_EVENT_SLEEP_PERMIT:
            otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "MQTT-SN event: Client permitted to sleep.");
            sleep_callback();
            break;

        case MQTTSN_EVENT_SLEEP_STOP:
            otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "MQTT-SN event: Client wakes up.");
            wakeup_callback();
            break;

        case MQTTSN_EVENT_TIMEOUT:
            otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "MQTT-SN event: Retransmission retries limit has been reached.");
            timeout_callback(p_event);
            break;

        case MQTTSN_EVENT_SEARCHGW_TIMEOUT:
            otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "MQTT-SN event: Gateway discovery procedure has finished.");
            searchgw_timeout_callback(p_event);
            break;

        default:
            break;
    }
}

/**@brief Function for initializing the MQTTSN client.
 */
static void mqttsn_init(void)
{
    uint32_t err_code = mqttsn_client_init(&m_client,
                                           MQTTSN_DEFAULT_CLIENT_PORT,
                                           mqttsn_evt_handler,
                                           thread_ot_instance_get());
    APP_ERROR_CHECK(err_code);

    connect_opt_init();
}

static void set_radio_on(void) 
{
    otError error;
    otLinkModeConfig mode;
    memset(&mode, 0, sizeof(mode));

    mode.mRxOnWhenIdle       = true;
    mode.mSecureDataRequests = true;
#ifdef OPENTHREAD_FTD
    mode.mDeviceType         = true;
    mode.mNetworkData        = true;
#endif
    error = otThreadSetLinkMode(thread_ot_instance_get(), mode);
    ASSERT(error == OT_ERROR_NONE);
}

static void set_radio_off(void) 
{
    otError error;
    otLinkModeConfig mode;
    memset(&mode, 0, sizeof(mode));

    mode.mRxOnWhenIdle       = false;
    mode.mSecureDataRequests = true;

    error = otThreadSetLinkMode(thread_ot_instance_get(), mode);
    ASSERT(error == OT_ERROR_NONE);
}

/***************************************************************************************************
 * @section buttons
 **************************************************************************************************/

static void bsp_event_handler(bsp_event_t event)
{
    if (event == BSP_EVENT_KEY_0) 
    {   
            wake_up();

            uint32_t err_code = mqttsn_client_search_gateway(&m_client, SEARCH_GATEWAY_TIMEOUT);
            if (err_code != NRF_SUCCESS)
            {
                NRF_LOG_ERROR("SEARCH GATEWAY message could not be sent. Error: 0x%x\r\n", err_code);
                otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "SEARCH GATEWAY message could not be sent. Error: 0x%x\r\n", err_code);
            }
    }         
}

/***************************************************************************************************
 * @section SAADC
 **************************************************************************************************/
void timer_handler(nrf_timer_event_t event_type, void * p_context)
{
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "SAADC timer fired");
}

void saadc_sampling_event_init(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_ppi_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    timer_cfg.bit_width = NRF_TIMER_BIT_WIDTH_32;
    err_code = nrf_drv_timer_init(&m_timer, &timer_cfg, timer_handler);
    APP_ERROR_CHECK(err_code);

    /* setup m_timer for compare event every 400ms */
    uint32_t ticks = nrf_drv_timer_ms_to_ticks(&m_timer, 2000);
    nrf_drv_timer_extended_compare(&m_timer,
                                   NRF_TIMER_CC_CHANNEL0,
                                   ticks,
                                   NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
                                   false);
    nrf_drv_timer_enable(&m_timer);

    uint32_t timer_compare_event_addr = nrf_drv_timer_compare_event_address_get(&m_timer,
                                                                                NRF_TIMER_CC_CHANNEL0);
    uint32_t saadc_sample_task_addr   = nrf_drv_saadc_sample_task_get();

    /* setup ppi channel so that timer compare event is triggering sample task in SAADC */
    err_code = nrf_drv_ppi_channel_alloc(&m_ppi_channel);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_assign(m_ppi_channel,
                                          timer_compare_event_addr,
                                          saadc_sample_task_addr);
    APP_ERROR_CHECK(err_code);
}


void saadc_sampling_event_enable(void)
{
    ret_code_t err_code = nrf_drv_ppi_channel_enable(m_ppi_channel);

    APP_ERROR_CHECK(err_code);
}

void saadc_callback(nrf_drv_saadc_evt_t const * p_event)
{
    otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "saadc_callback");
    if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
    {
        ret_code_t err_code;

        err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, SAMPLES_IN_BUFFER);
        APP_ERROR_CHECK(err_code);

        int i;
        otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "ADC event number: %d", (int)m_adc_evt_counter);

        for (i = 0; i < SAMPLES_IN_BUFFER; i++)
        {
            otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "%d", p_event->data.done.p_buffer[i]);
        }

        if (mqttsn_client_state_get(&m_client) == MQTTSN_CLIENT_CONNECTED)
        {
            int16_t val = p_event->data.done.p_buffer[0];
            char buffer[51] = {};
            sprintf(buffer, "{ \"measurement\" : %d }", val);

            otPlatLog(OT_LOG_LEVEL_DEBG, OT_LOG_REGION_UTIL, "Publishing ADC state %s", buffer);

            err_code = mqttsn_client_publish(&m_client, m_topic.topic_id, (uint8_t*)&buffer, 50, &m_msg_id);
            if (err_code != NRF_SUCCESS)
            {
                NRF_LOG_ERROR("PUBLISH message could not be sent. Error code: 0x%x\r\n", err_code);
            }
            LEDS_OFF(LEDS_MASK);
            sleep();
        }
        else if (has_valid_role())
        {
            find_gateway();
        }

        m_adc_evt_counter++;
    }
}


void saadc_init(void)
{
    ret_code_t err_code;
    nrf_saadc_channel_config_t channel_config =
        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN0);

    err_code = nrf_drv_saadc_init(NULL, saadc_callback);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_channel_init(0, &channel_config);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[0], SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[1], SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

}

void otPlatLog(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aFormat, ...)
{
    OT_UNUSED_VARIABLE(aLogLevel);
    OT_UNUSED_VARIABLE(aLogRegion);
    OT_UNUSED_VARIABLE(aFormat);

    // va_list ap;
    // va_start(ap, aFormat);
    // otCliPlatLogv(aLogLevel, aLogRegion, aFormat, ap);
    // va_end(ap);
}


/***************************************************************************************************
 * @section Main
 **************************************************************************************************/

int main(int argc, char *argv[])
{
    log_init();
    // scheduler_init();
    timer_init();
    leds_init();

    thread_instance_init();
    thread_bsp_init();

    saadc_init();

    saadc_sampling_event_init();
    saadc_sampling_event_enable();

    otInstance *instance = thread_ot_instance_get();

    setNetworkConfiguration(instance);

    /* Start the Thread network interface (CLI cmd > ifconfig up) */
    otIp6SetEnabled(instance, true);

    /* Start the Thread stack (CLI cmd > thread start) */
    otThreadSetEnabled(instance, true);

    mqttsn_init();

    while (true)
    {
        thread_process();
        // app_sched_execute();

        if (NRF_LOG_PROCESS() == false)
        {
            thread_sleep();
        }
    }
}

/**
 *@}
 **/

