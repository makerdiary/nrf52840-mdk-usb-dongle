/**
 * Copyright (c) 2017 - 2020, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup cli_example_main main.c
 * @{
 * @ingroup cli_example
 * @brief An example presenting OpenThread CLI.
 *
 */


#include "app_scheduler.h"
#include "app_timer.h"
#include "bsp_thread.h"
#include "nrf_log_ctrl.h"
#include "nrf_log.h"
#include "nrf_log_default_backends.h"

#include "mqttsn_client.h"

#include "thread_utils.h"

#include <assert.h>
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

#define DEFAULT_CHILD_TIMEOUT    40                                         /**< Thread child timeout [s]. */
#define DEFAULT_POLL_PERIOD      1000                                       /**< Thread Sleepy End Device polling period when MQTT-SN Asleep. [ms] */
#define SHORT_POLL_PERIOD        100                                        /**< Thread Sleepy End Device polling period when MQTT-SN Awake. [ms] */
#define SEARCH_GATEWAY_TIMEOUT   5                                          /**< MQTT-SN Gateway discovery procedure timeout in [s]. */                                   

static mqttsn_client_t      m_client;                                       /**< An MQTT-SN client instance. */
static mqttsn_remote_t      m_gateway_addr;                                 /**< A gateway address. */
static uint8_t              m_gateway_id;                                   /**< A gateway ID. */
static mqttsn_connect_opt_t m_connect_opt;                                  /**< Connect options for the MQTT-SN client. */
static uint8_t              m_led_state        = 0;                         /**< Previously sent BSP_LED_2 command. */
static uint16_t             m_msg_id           = 0;                         /**< Message ID thrown with MQTTSN_EVENT_TIMEOUT. */
static char                 m_client_id[]      = "nRF52840_publisher";      /**< The MQTT-SN Client's ID. */
static char                 m_topic_name[]     = "nRF52840_resources/led3"; /**< Name of the topic corresponding to subscriber's BSP_LED_2. */
static mqttsn_topic_t       m_topic            =                            /**< Topic corresponding to subscriber's BSP_LED_2. */
{
    .p_topic_name = (unsigned char *)m_topic_name,
    .topic_id     = 0,
};

static void bsp_event_handler(bsp_event_t event);

/***************************************************************************************************
 * @section State
 **************************************************************************************************/

static void thread_state_changed_callback(uint32_t flags, void * p_context)
{
    NRF_LOG_INFO("State changed! Flags: 0x%08x Current role: %d\r\n",
                 flags, otThreadGetDeviceRole(p_context));
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
        .radio_mode        = THREAD_RADIO_MODE_RX_ON_WHEN_IDLE,
        .autocommissioning = false,
        .autostart_disable = true,
    };

    thread_init(&thread_configuration);
    thread_cli_init();
    thread_state_changed_callback_set(thread_state_changed_callback);

    uint32_t err_code = bsp_thread_init(thread_ot_instance_get());
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for deinitializing the Thread Stack.
 *
 */
static void thread_instance_finalize(void)
{
    bsp_thread_deinit(thread_ot_instance_get());
    thread_soft_deinit();
}


/**@brief Function for initializing scheduler module.
 */
static void scheduler_init(void)
{
    APP_SCHED_INIT(SCHED_EVENT_DATA_SIZE, SCHED_QUEUE_SIZE);
}


void setNetworkConfiguration(otInstance *aInstance)
{
    static char          aNetworkName[] = "OpenThread-a393";
    otOperationalDataset aDataset;

    memset(&aDataset, 0, sizeof(otOperationalDataset));
   
    /*
     * Fields that can be configured in otOperationDataset to override defaults:
     *     Network Name, Mesh Local Prefix, Extended PAN ID, PAN ID, Delay Timer,
     *     Channel, Channel Mask Page 0, Network Master Key, PSKc, Security Policy
     */
    aDataset.mActiveTimestamp                      = 1;
    aDataset.mComponents.mIsActiveTimestampPresent = true;
     
    /* Set Channel to 17 */
    aDataset.mChannel                      = 17;
    aDataset.mComponents.mIsChannelPresent = true;
    
    /* Set Pan ID to 0xa393 */
    aDataset.mPanId                      = (otPanId)0xA393;
    aDataset.mComponents.mIsPanIdPresent = true;

    /* Set mMeshLocalPrefix to fda5:ecbe:8107:b60d::/64 */
    uint8_t MeshLocalPrefix[OT_PSKC_MAX_SIZE] = {0xfd, 0xa5, 0xec, 0xbe, 0x81, 0x07, 0xb6, 0x0d};
    memcpy(aDataset.mMeshLocalPrefix.m8, MeshLocalPrefix, sizeof(aDataset.mMeshLocalPrefix));
    aDataset.mComponents.mIsMeshLocalPrefixPresent = true;

    /* Set mPSKc to 99 3f 68 51 16 9d 25 6b 53 62 eb df 34 41 31 d0 */
    uint8_t PSKc[OT_PSKC_MAX_SIZE] = {0x99, 0x3F, 0x68, 0x51, 0x16, 0x9D, 0x25, 0x6B, 0x53, 0x62, 0xEB, 0xDF, 0x34, 0x41, 0x31, 0xD0};
    memcpy(aDataset.mPskc.m8, PSKc, sizeof(aDataset.mPskc));
    aDataset.mComponents.mIsExtendedPanIdPresent = true;
    
    /* Set Extended Pan ID to 0a ab 0a 1b f8 26 bb c4 */
    uint8_t extPanId[OT_EXT_PAN_ID_SIZE] = {0x0A, 0xAB, 0x0A, 0x1B, 0xF8, 0x26, 0xBB, 0xC4};
    memcpy(aDataset.mExtendedPanId.m8, extPanId, sizeof(aDataset.mExtendedPanId));
    aDataset.mComponents.mIsPskcPresent = true;
    
    /* Set master key to 04 02 98 29 dd f0 11 b3 fd 23 50 22 9c bc fc a2 */
    uint8_t key[OT_MASTER_KEY_SIZE] = {0x04, 0x02, 0x98, 0x29, 0xDD, 0xF0, 0x11, 0xB3, 0xFD, 0x23, 0x50, 0x22, 0x9C, 0xBC, 0xFC, 0xA2};
    memcpy(aDataset.mMasterKey.m8, key, sizeof(aDataset.mMasterKey));
    aDataset.mComponents.mIsMasterKeyPresent = true;

    /* Set Network Name to OTCodelab */
    size_t length = strlen(aNetworkName);
    assert(length <= OT_NETWORK_NAME_MAX_SIZE);
    memcpy(aDataset.mNetworkName.m8, aNetworkName, length);
    aDataset.mComponents.mIsNetworkNamePresent = true;

#if OPENTHREAD_FTD
    otDatasetSetActive(aInstance, &aDataset);
    
    /* Set the router selection jitter to override the 2 minute default.
       CLI cmd > routerselectionjitter 20
       Warning: For demo purposes only - not to be used in a real product */
    uint8_t jitterValue = 20;
    otThreadSetRouterSelectionJitter(aInstance, jitterValue);
#else
    OT_UNUSED_VARIABLE(aInstance);
#endif
}

/***************************************************************************************************
 * @section MQTT-SN
 **************************************************************************************************/


/**@brief Turns the MQTT-SN network indication LED on.
 *
 * @details This LED is on when an MQTT-SN client is in connected or awake state.
 */
static void light_on(void)
{
    LEDS_ON(BSP_LED_3_MASK);
}

/**@brief Turns the MQTT-SN network indication LED off.
 *
 * @details This LED is on when an MQTT-SN client is in disconnected or asleep state.
 */
static void light_off(void)
{
    LEDS_OFF(BSP_LED_3_MASK);
}

/**@brief Puts MQTT-SN client in sleep mode.
 *
 * @details This function changes Thread Sleepy End Device polling period to default.
 */
static void sleep(void)
{
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
    light_on();

    uint32_t err_code = mqttsn_client_topic_register(&m_client,
                                                     m_topic.p_topic_name,
                                                     strlen(m_topic_name),
                                                     &m_msg_id);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("REGISTER message could not be sent. Error code: 0x%x\r\n", err_code);
    }
}

/**@brief Processes DISCONNECT message from a gateway. */
static void disconnected_callback(void)
{
    light_off();
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
    NRF_LOG_INFO("MQTT-SN event: Topic has been registered with ID: %d.\r\n",
                 p_event->event_data.registered.packet.topic.topic_id);

    sleep();
}

/**@brief Processes PUBACK message from a gateway.
 *
 * @details This function puts the client in sleep mode.
 */
static void puback_callback(void)
{
    sleep();
}

/**@brief Processes DISCONNECT message being a response to sleep request.
 *
 * @details This function puts the client in sleep mode.
 */
static void sleep_callback(void)
{
    sleep();
}

/**@brief Processes callback from keep-alive timer timeout.
 *
 * @details This function puts the client in active mode.
 */
static void wakeup_callback(void)
{
    wake_up();
}

/**@brief Processes retransmission limit reached event. */
static void timeout_callback(mqttsn_event_t * p_event)
{
    NRF_LOG_INFO("MQTT-SN event: Timed-out message: %d. Message ID: %d.\r\n",
                  p_event->event_data.error.msg_type,
                  p_event->event_data.error.msg_id);
}

/**@brief Processes results of gateway discovery procedure. */
static void searchgw_timeout_callback(mqttsn_event_t * p_event)
{
    NRF_LOG_INFO("MQTT-SN event: Gateway discovery result: 0x%x.\r\n", p_event->event_data.discovery);
    sleep();
}

/**@brief Function for handling MQTT-SN events. */
void mqttsn_evt_handler(mqttsn_client_t * p_client, mqttsn_event_t * p_event)
{
    switch (p_event->event_id)
    {
        case MQTTSN_EVENT_GATEWAY_FOUND:
            NRF_LOG_INFO("MQTT-SN event: Client has found an active gateway.\r\n");
            gateway_info_callback(p_event);
            break;

        case MQTTSN_EVENT_CONNECTED:
            NRF_LOG_INFO("MQTT-SN event: Client connected.\r\n");
            connected_callback();
            break;

        case MQTTSN_EVENT_DISCONNECTED:
            NRF_LOG_INFO("MQTT-SN event: Client disconnected.\r\n");
            disconnected_callback();
            break;

        case MQTTSN_EVENT_REGISTERED:
            NRF_LOG_INFO("MQTT-SN event: Client registered topic.\r\n");
            regack_callback(p_event);
            break;

        case MQTTSN_EVENT_PUBLISHED:
            NRF_LOG_INFO("MQTT-SN event: Client has successfully published content.\r\n");
            puback_callback();
            break;

        case MQTTSN_EVENT_SLEEP_PERMIT:
            NRF_LOG_INFO("MQTT-SN event: Client permitted to sleep.\r\n");
            sleep_callback();
            break;

        case MQTTSN_EVENT_SLEEP_STOP:
            NRF_LOG_INFO("MQTT-SN event: Client wakes up.\r\n");
            wakeup_callback();
            break;

        case MQTTSN_EVENT_TIMEOUT:
            NRF_LOG_INFO("MQTT-SN event: Retransmission retries limit has been reached.\r\n");
            timeout_callback(p_event);
            break;

        case MQTTSN_EVENT_SEARCHGW_TIMEOUT:
            NRF_LOG_INFO("MQTT-SN event: Gateway discovery procedure has finished.\r\n");
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

/***************************************************************************************************
 * @section buttons
 **************************************************************************************************/

static void led_state_pub(uint8_t led_state)
{
    uint32_t err_code = mqttsn_client_publish(&m_client, m_topic.topic_id, &led_state, 1, &m_msg_id);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("PUBLISH message could not be sent. Error code: 0x%x\r\n", err_code)
    }
}

static void publish(void)
{
    m_led_state = m_led_state == 1 ? 0 : 1;
    led_state_pub(m_led_state);
}

static void bsp_event_handler(bsp_event_t event)
{
    if (otThreadGetDeviceRole(thread_ot_instance_get()) < OT_DEVICE_ROLE_CHILD )
    {
        (void)event;
        return;
    }

    switch (event)
    {
        case BSP_EVENT_KEY_1:
        {
            wake_up();

            uint32_t err_code = mqttsn_client_search_gateway(&m_client, SEARCH_GATEWAY_TIMEOUT);
            if (err_code != NRF_SUCCESS)
            {
                NRF_LOG_ERROR("SEARCH GATEWAY message could not be sent. Error: 0x%x\r\n", err_code);
            }
            break;
        }

        case BSP_EVENT_KEY_2:
        {
            wake_up();

            uint32_t err_code;

            if (mqttsn_client_state_get(&m_client) == MQTTSN_CLIENT_CONNECTED)
            {
                err_code = mqttsn_client_disconnect(&m_client);
                if (err_code != NRF_SUCCESS)
                {
                    NRF_LOG_ERROR("DISCONNECT message could not be sent. Error: 0x%x\r\n", err_code);
                }
            }
            else
            {
                err_code = mqttsn_client_connect(&m_client, &m_gateway_addr, m_gateway_id, &m_connect_opt);
                if (err_code != NRF_SUCCESS)
                {
                    NRF_LOG_ERROR("CONNECT message could not be sent. Error: 0x%x\r\n", err_code);
                }
            }
            break;
        }

        case BSP_EVENT_KEY_3:
        {
            wake_up();
            publish();
            break;
        }

        default:
        {
            break;
        }
    }
}

/***************************************************************************************************
 * @section Main
 **************************************************************************************************/

int main(int argc, char *argv[])
{
    log_init();
    scheduler_init();
    timer_init();
    leds_init();

    uint32_t err_code = bsp_init(BSP_INIT_LEDS, NULL);
    APP_ERROR_CHECK(err_code);

    while (true)
    {
        thread_instance_init();
        otInstance *instance = thread_ot_instance_get();

        setNetworkConfiguration(instance);

        /* Start the Thread network interface (CLI cmd > ifconfig up) */
        otIp6SetEnabled(instance, true);

        /* Start the Thread stack (CLI cmd > thread start) */
        otThreadSetEnabled(instance, true);

        thread_bsp_init();
        mqttsn_init();

        while (!thread_soft_reset_was_requested())
        {
            // NRF_LOG_ERROR("loop!");
            thread_process();
            app_sched_execute();

            if (NRF_LOG_PROCESS() == false)
            {
                thread_sleep();
            }
        }

        thread_instance_finalize();
    }
}

void otPlatLog(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aFormat, ...)
{
    OT_UNUSED_VARIABLE(aLogLevel);
    OT_UNUSED_VARIABLE(aLogRegion);
    OT_UNUSED_VARIABLE(aFormat);

    va_list ap;
    va_start(ap, aFormat);
    otCliPlatLogv(aLogLevel, aLogRegion, aFormat, ap);
    va_end(ap);
}


/**
 *@}
 **/

