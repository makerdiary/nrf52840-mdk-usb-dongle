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
#include "boards.h"
#include "nfc_t2t_lib.h"
#include "nfc_uri_msg.h"
#include "nrf_cli.h"
#include "nrf_log.h"


static bool m_nfc_activated = false;
/** @snippet [NFC URI usage_0] */
static const uint8_t m_url[] =
    {'m', 'a', 'k', 'e', 'r', 'd', 'i', 'a', 'r', 'y', '.', 'c', 'o', 'm'}; //URL "makerdiary.com"

uint8_t m_ndef_msg_buf[256];
/** @snippet [NFC URI usage_0] */
/**
 * @brief Callback function for handling NFC events.
 */
static void nfc_callback(void * p_context, nfc_t2t_event_t event, const uint8_t * p_data, size_t data_length)
{
    (void)p_context;

    switch (event)
    {
        case NFC_T2T_EVENT_FIELD_ON:
            bsp_board_led_on(BSP_BOARD_LED_2);
            break;

        case NFC_T2T_EVENT_FIELD_OFF:
            bsp_board_led_off(BSP_BOARD_LED_2);
            break;

        default:
            break;
    }
}

static void cmd_led(nrf_cli_t const * p_cli, size_t argc, char **argv)
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

static void cmd_led_on(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
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

	if(!strcmp(argv[1], "all"))
	{
		bsp_board_leds_on();
	}
	else
	{
		uint32_t led = atoi(argv[1]);

		if((led == 0 && strcmp(argv[1], "0")) || led >= LEDS_NUMBER)
		{
			nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Invalid LED: %s\r\n", argv[1]);
			return;
		}
		bsp_board_led_on(led);
	}
}

static void cmd_led_off(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
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

	if(!strcmp(argv[1], "all"))
	{
		bsp_board_leds_off();
	}
	else
	{
		uint32_t led = atoi(argv[1]);

		if((led == 0 && strcmp(argv[1], "0")) || led >= LEDS_NUMBER)
		{
			nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Invalid LED: %s\r\n", argv[1]);
			return;
		}
		bsp_board_led_off(led);
	}
}

static void cmd_led_invert(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
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

	uint32_t led = atoi(argv[1]);

	if((led == 0 && strcmp(argv[1], "0")) || led >= LEDS_NUMBER)
	{
		nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Invalid LED: %s\r\n", argv[1]);
		return;
	}
	bsp_board_led_invert(led);
}


static void cmd_nfc(nrf_cli_t const * p_cli, size_t argc, char **argv)
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


static void cmd_nfc_start(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
	ret_code_t err_code;

    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if(argc != 1)
    {
    	nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
    	return;    	
    }

    if(m_nfc_activated)
    {
    	nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "NFC: activated\r\n");
    	return;
    }

    /* Set up NFC */
    err_code = nfc_t2t_setup(nfc_callback, NULL);
    APP_ERROR_CHECK(err_code);

    /** @snippet [NFC URI usage_1] */
    /* Provide information about available buffer size to encoding function */
    uint32_t len = sizeof(m_ndef_msg_buf);

    /* Encode URI message into buffer */
    err_code = nfc_uri_msg_encode( NFC_URI_HTTPS,
                                   m_url,
                                   sizeof(m_url),
                                   m_ndef_msg_buf,
                                   &len);

    APP_ERROR_CHECK(err_code);
    /** @snippet [NFC URI usage_1] */

    /* Set created message as the NFC payload */
    err_code = nfc_t2t_payload_set(m_ndef_msg_buf, len);
    APP_ERROR_CHECK(err_code);

    /* Start sensing NFC field */
    err_code = nfc_t2t_emulation_start();
    APP_ERROR_CHECK(err_code);

    m_nfc_activated = true;
}

static void cmd_nfc_stop(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
	ret_code_t err_code;

    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if(argc != 1)
    {
    	nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
    	return;    	
    }

    if(!m_nfc_activated)
    {
    	nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "NFC: deactivated\r\n");
    	return;
    }

    /* Start sensing NFC field */
    err_code = nfc_t2t_emulation_stop();
    APP_ERROR_CHECK(err_code);

    err_code = nfc_t2t_done();
    APP_ERROR_CHECK(err_code);

    m_nfc_activated = false;
}

static void cmd_nfc_status(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if(argc != 1)
    {
    	nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
    	return;    	
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "NFC: %s\r\n", m_nfc_activated? "activated" : "deactivated");
}


NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_led)
{
    NRF_CLI_CMD(on, NULL, "'led on {0,1,2,all}' turns on an LED", cmd_led_on),
    NRF_CLI_CMD(off,  NULL, "'led off {0,1,2,all}' turns off an LED", cmd_led_off),
    NRF_CLI_CMD(invert,  NULL, "'led invert {0,1,2}' inverts the state of an LED", cmd_led_invert),
    NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CMD_REGISTER(led, &m_sub_led, "Commands for LED control", cmd_led);


NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_nfc)
{
    NRF_CLI_CMD(start, NULL, "Activate the NFC frontend", cmd_nfc_start),
    NRF_CLI_CMD(stop, NULL, "Deactivate the NFC frontend", cmd_nfc_stop),
    NRF_CLI_CMD(status, NULL, "Show the NFC frontend status", cmd_nfc_status),
    NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CMD_REGISTER(nfc, &m_sub_nfc, "Commands for flash memory access", cmd_nfc);

