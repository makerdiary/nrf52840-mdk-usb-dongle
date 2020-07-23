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

        while (!thread_soft_reset_was_requested())
        {
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


/**
 *@}
 **/
