/**
 * Copyright (c) 2018, Nordic Semiconductor ASA
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
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nrf_cli.h"
#include "nrf_drv_saadc.h"
#include "nrf_log.h"


static void saadc_callback(nrf_drv_saadc_evt_t const * p_event)
{
    if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
    {
        //
    }
}

static void cmd_adc(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if ((argc == 1) || nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "%s %s: command not found\r\n", argv[0], argv[1]);
}

static void cmd_adc_sample(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
	ret_code_t err_code;
	nrf_drv_saadc_config_t saadc_config = NRF_DRV_SAADC_DEFAULT_CONFIG;
    nrf_saadc_channel_config_t channel_config =
        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_DISABLED);

    nrf_saadc_value_t adc_value;

    if ((argc == 1) || nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if(argc != 2)
    {
    	nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
    	return;    	
    }

    if(!strcmp(argv[1], "vdd") || !strcmp(argv[1], "Vdd") || !strcmp(argv[1], "VDD"))
    {
    	channel_config.pin_p    = NRF_SAADC_INPUT_VDD;
    }
    else
    {
    	uint32_t ain = atoi(argv[1]);
    	if((ain == 0 && strcmp(argv[1], "0")) || ain > 7) // either AIN0~AIN7 or VDD
    	{
    		nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Invalid AIN: %s\r\n", argv[1]);
			return;
    	}

    	channel_config.pin_p = ain + 1; // NRF_SAADC_INPUT_AINn = ain(0..7) + 1
    }

    /* Burst enabled to oversample the SAADC. */
    channel_config.burst    = NRF_SAADC_BURST_ENABLED;
    channel_config.acq_time = NRF_SAADC_ACQTIME_40US;

    err_code = nrf_drv_saadc_init(&saadc_config, saadc_callback);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_channel_init(0, &channel_config);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_sample_convert(0, &adc_value);
    APP_ERROR_CHECK(err_code);

    if(channel_config.pin_p == NRF_SAADC_INPUT_VDD)
    {
    	nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "VDD: %d\r\n", adc_value*3600/1024);
    }
    else
    {
    	nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "AIN%s: %d\r\n", argv[1], adc_value*3600/1024);
    }

    nrf_drv_saadc_uninit();
}

NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_adc)
{
    NRF_CLI_CMD(sample, NULL, "'adc sample {0..7,vdd}' Executes a single ADC conversion. Unit: mV", cmd_adc_sample),
    NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CMD_REGISTER(adc, &m_sub_adc, "Commands for ADC access", cmd_adc);


