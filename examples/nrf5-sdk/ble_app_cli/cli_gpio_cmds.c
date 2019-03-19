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
#include "nrf_gpio.h"
#include "nrf_log.h"

static const uint32_t available_pin_list[] = {
    4, 5, 6, 7, 8,
    19, 20, 21, 2, 3
};

static bool pin_available(uint32_t pin_number)
{
    bool found = false;

    for (int i = 0; i < ARRAY_SIZE(available_pin_list); ++i)
    {
        if(available_pin_list[i] == pin_number)
        {
            found = true;
            break;
        }
    }

    return found;
}


static void cmd_gpio(nrf_cli_t const * p_cli, size_t argc, char **argv)
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

static void cmd_gpio_write(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
	uint32_t pin = 0xFFFFFFFF;
	uint32_t level;

    if ((argc == 1) || nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    switch (argc - 1)
    {
    	case 1:
    	{
    		pin = atoi(argv[1]);
    		if(pin_available(pin))
    		{
    			nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Value written to P%s should be specified\r\n", argv[1]);
    		}
    		else
    		{
    			nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Invalid pin: %s\r\n", argv[1]);
    		}
    		return;
    	}

    	case 2:
    	{
    		pin = atoi(argv[1]);
    		if(pin_available(pin))
    		{
    			if(!strcmp(argv[2], "0") || !strcmp(argv[2], "1"))
    			{
    				level = atoi(argv[2]);
    				nrf_gpio_cfg_output(pin);
    				nrf_gpio_pin_write(pin, level);
    			}
    			else
    			{
    				nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameter: %s (Should be 0 or 1)\r\n", argv[2]);
    			}
    		}
    		else
    		{
    			nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Invalid pin: %s\r\n", argv[1]);
    		}
    		return;
    	}

    	default:
    	{
    		nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
    		break;
    	}
    }
}

static void cmd_gpio_read(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
	uint32_t pin = 0xFFFFFFFF;

    /* Extra defined pull_config option */
    static const nrf_cli_getopt_option_t opt[] = {
        NRF_CLI_OPT(
            "--pull",
            "-p",
            "State of the pin range pull resistor {no,down,up}"
        )
    };

    if ((argc == 1) || nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, opt, ARRAY_SIZE(opt));
        return;
    }

    switch (argc - 1)
    {
    	case 1: // cmd: gpio read pin
    	{
    		pin = atoi(argv[1]);
    		if(pin_available(pin))
    		{
    			nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_NOPULL);

    			uint32_t level = nrf_gpio_pin_read(pin);

    			nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "P%s: %d\r\n", argv[1], level);

                nrf_gpio_cfg_default(pin);
    		}
    		else
    		{
    			nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Invalid pin: %s\r\n", argv[1]);
    		}
    		return;
    	}

    	case 2: // cmd: gpio read pin -p
    	{
    		pin = atoi(argv[1]);
    		if(pin_available(pin))
    		{
    			if(!strcmp(argv[2], "-p") || !strcmp(argv[2], "--pull"))
    			{
    				nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "Configure pull option: {no,down,up}\r\n");
    			}
    			else
    			{
    				nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown option: %s\r\n", argv[2]);
    			}
    		}
    		else
    		{
    			nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Invalid pin: %s\r\n", argv[1]);
    		}
    		return;
    	}

    	case 3: //cmd: gpio read pin -p no|down|high
    	{
    		pin = atoi(argv[1]);
    		if(pin_available(pin))
    		{
    			if(!strcmp(argv[2], "-p") || !strcmp(argv[2], "--pull"))
    			{
    				if(!strcmp(argv[3], "no"))
    				{
    					nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_NOPULL);
    				}
    				else if(!strcmp(argv[3], "down"))
    				{
    					nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_PULLDOWN);
    				}
    				else if(!strcmp(argv[3], "up"))
    				{
    					nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_PULLUP);
    				}
    				else
    				{
    					nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown pull option: %s\r\n", argv[3]);
    					return;
    				}
    				uint32_t level = nrf_gpio_pin_read(pin);
    				nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "P%s: %d\r\n", argv[1], level);
                    nrf_gpio_cfg_default(pin);
    			}
    			else
    			{
    				nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown option: %s\r\n", argv[2]);
    			}
    		}
    		else
    		{
    			nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Invalid pin: %s\r\n", argv[1]);
    		}
    		return;    		
    	}

    	default:
    	{
    		nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
    		break;
    	}
    }
}

NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_gpio)
{
    NRF_CLI_CMD(write, NULL, "'gpio write {pin} {value}' writes a value to a GPIO pin", cmd_gpio_write),
    NRF_CLI_CMD(read,  NULL, "'gpio read {pin} [-p] {no,down,up}' reads the input level of a GPIO pin", cmd_gpio_read),
    NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CMD_REGISTER(gpio, &m_sub_gpio, "Commands for accessing a GPIO pin", cmd_gpio);










