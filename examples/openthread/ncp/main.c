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
 * @defgroup ncp_example_main main.c
 * @{
 * @ingroup ncp_example
 * @brief An example presenting OpenThread NCP.
 *
 */
#include <stdint.h>
#include <string.h>

#include "app_scheduler.h"
#include "app_timer.h"
#include "bsp_thread.h"
#include "nrf_assert.h"
#include "nrf_log_ctrl.h"
#include "nrf_log.h"
#include "nrf_log_default_backends.h"

#include <openthread/ncp.h>
#include <openthread/tasklet.h>
#include <openthread/thread_ftd.h>
#include <openthread/platform/openthread-system.h>

#include <mbedtls/platform.h>
#include <openthread/heap.h>

#ifdef FREERTOS
#include "FreeRTOS.h"
#else
#include "mem_manager.h"
#endif

#if !OPENTHREAD_CONFIG_ENABLE_BUILTIN_MBEDTLS
#include "nrf_cc310_platform_abort.h"
#include "nrf_cc310_platform_mutex.h"
#endif /* OPENTHREAD_CONFIG_ENABLE_BUILTIN_MBEDTLS */

#define ROUTER_SELECTION_JITTER  5                               /**< A value of router selection jitter. */
#define SCHED_QUEUE_SIZE         40                              /**< Maximum number of events in the scheduler queue. */
#define SCHED_EVENT_DATA_SIZE    APP_TIMER_SCHED_EVENT_DATA_SIZE /**< Maximum app_scheduler event size. */

typedef struct
{
    otInstance * p_ot_instance;
} application_t;

static application_t m_app =
{
    .p_ot_instance = NULL
};

/***************************************************************************************************
 * @section Initialization
 **************************************************************************************************/

 /**@brief Function for initializing the Thread Stack in NCP mode.
 */
static void thread_ncp_init(void)
{
    otSysInit(0, NULL);

    m_app.p_ot_instance = otInstanceInitSingle();
    ASSERT(m_app.p_ot_instance);

    otNcpInit(m_app.p_ot_instance);

#ifdef OPENTHREAD_FTD
    otThreadSetRouterSelectionJitter(m_app.p_ot_instance, ROUTER_SELECTION_JITTER);
#endif

#ifndef OPENTHREAD_RADIO
    uint32_t err_code = bsp_thread_init(m_app.p_ot_instance);
    APP_ERROR_CHECK(err_code);
#endif
}

/**@brief Function for deinitializing the Thread Stack in NCP mode.
*/
static void thread_ncp_deinit(void)
{
#ifndef OPENTHREAD_RADIO
    bsp_thread_deinit(m_app.p_ot_instance);
#endif

    otInstanceFinalize(m_app.p_ot_instance);
    m_app.p_ot_instance = NULL;
}


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


/**@brief Function for processing Thread stack.
 */
static void thread_process(void)
{
    otTaskletsProcess(m_app.p_ot_instance);
    otSysProcessDrivers(m_app.p_ot_instance);
}

#if !defined OPENTHREAD_RADIO

static void* ot_calloc(size_t n, size_t size)
{
    return nrf_calloc(n, size);
}

static void ot_free(void *p_ptr)
{
    nrf_free(p_ptr);
}

/**@brief Function for setting up Thread platform
 */
static void platform_init(void)
{
    APP_ERROR_CHECK(nrf_mem_init());

#if !OPENTHREAD_CONFIG_ENABLE_BUILTIN_MBEDTLS
    int ret;

    ret = mbedtls_platform_set_calloc_free(ot_calloc, ot_free);
    ASSERT(ret == 0);

    ret = mbedtls_platform_setup(NULL);
    ASSERT(ret == 0);

#endif /* OPENTHREAD_CONFIG_ENABLE_BUILTIN_MBEDTLS */

    otHeapSetCAllocFree(ot_calloc, ot_free);
}

#endif /* OPENTHREAD_RADIO */

/***************************************************************************************************
 * @section Main
 **************************************************************************************************/

int main(int argc, char *argv[])
{
    log_init();
    timer_init();
    leds_init();

#if !defined OPENTHREAD_RADIO
    platform_init();
#endif

    uint32_t err_code = bsp_init(BSP_INIT_LEDS, NULL);
    APP_ERROR_CHECK(err_code);

    while (true)
    {
        thread_ncp_init();

        while (!otSysPseudoResetWasRequested())
        {
            thread_process();

            // Enter sleep state if no more tasks are pending.
            if (!otTaskletsArePending(m_app.p_ot_instance))
            {
                __WFE();
            }
        }

        thread_ncp_deinit();
    }
}

/**
 *@}
 **/
