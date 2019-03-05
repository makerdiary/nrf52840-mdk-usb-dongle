/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
 * @defgroup pselreset_erase_main main.c
 * @{
 * @ingroup pselreset_erase
 * @brief Erase PSELRESET UICR register Application main file.
 *
 * This file contains the source code to erase PSELRESET UICR register.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"


// Storage buffers and variables to hold the UICR register content
static uint32_t uicr_buffer[59]    = {0x00000000};
static uint32_t pselreset[2]       = {0x00000000};
static uint32_t approtect          = 0x00000000;
static uint32_t nfcpins            = 0x00000000;
static uint32_t debugctrl          = 0x00000000;
static uint32_t regout0            = 0x00000000;


/**
 * @brief Function for application main entry.
 */
int main(void)
{
    uint32_t uicr_address = 0x10001014;

    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);

    CRITICAL_REGION_ENTER();

    if(((NRF_UICR->PSELRESET[0] & UICR_PSELRESET_CONNECT_Msk) == (UICR_PSELRESET_CONNECT_Connected << UICR_PSELRESET_CONNECT_Pos)) ||
       ((NRF_UICR->PSELRESET[1] & UICR_PSELRESET_CONNECT_Msk) == (UICR_PSELRESET_CONNECT_Connected << UICR_PSELRESET_CONNECT_Pos)))
    {
        // Read and buffer UICR register content prior to erase
        for(int i = 0; i < ARRAY_SIZE(uicr_buffer); i++)
        {
            uicr_buffer[i] = *(uint32_t *)uicr_address; 
            while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
            // Set UICR address to the next register
            uicr_address += 0x04;
        }
        pselreset[0] = NRF_UICR->PSELRESET[0];
        pselreset[1] = NRF_UICR->PSELRESET[1];
        approtect    = NRF_UICR->APPROTECT;
        nfcpins      = NRF_UICR->NFCPINS;
        debugctrl    = NRF_UICR->DEBUGCTRL;
        regout0      = NRF_UICR->REGOUT0;

        // Enable Erase mode
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Een << NVMC_CONFIG_WEN_Pos; //0x02; 
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
        
        // Erase the UICR registers
        NRF_NVMC->ERASEUICR = NVMC_ERASEUICR_ERASEUICR_Erase << NVMC_ERASEUICR_ERASEUICR_Pos; //0x00000001;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}

        // Enable WRITE mode
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos; //0x01;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}

        // Write the modified UICR content back to the UICR registers 
        uicr_address = 0x10001014;
        for(int j = 0; j < ARRAY_SIZE(uicr_buffer); j++)
        {
            // Skip writing to registers that were 0xFFFFFFFF before the UICR register were erased. 
            if(uicr_buffer[j] != 0xFFFFFFFF)
            {
                *(uint32_t *)uicr_address = uicr_buffer[j];
                // Wait untill the NVMC peripheral has finished writting to the UICR register
                while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}                
            }
            // Set UICR address to the next register
            uicr_address += 0x04;  
        }

        if(approtect != 0xFFFFFFFF)
        {
            NRF_UICR->APPROTECT     = approtect;
            while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
        }

        if(nfcpins != 0xFFFFFFFF)
        {
            NRF_UICR->NFCPINS       = nfcpins;
            while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
        }

        if(debugctrl != 0xFFFFFFFF)
        {
            NRF_UICR->DEBUGCTRL     = debugctrl;
            while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
        }

        if(regout0 != 0xFFFFFFFF)
        {
            NRF_UICR->REGOUT0       = regout0;
            while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
        }

        NVIC_SystemReset();
    }

    CRITICAL_REGION_EXIT();

    /* Toggle LEDs. */
    while (true)
    {
        for (int i = 0; i < LEDS_NUMBER; i++)
        {
            bsp_board_led_invert(i);
            nrf_delay_ms(500);
        }
    }
}

/**
 *@}
 **/
