/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
/* ULP-RISC-V example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.

   This code runs on ULP-RISC-V  coprocessor
*/

#include <stdint.h>
#include "ulp_riscv_utils.h"
#include "ulp_riscv_adc_ulp_core.h"
#include "ulp_riscv_lock.h"

#include "example_config.h"

#define ULP_TIMER_PERIOD 20u //mS
#define WAKEUP_PERIOD 1000u //mS
#define CYCLES (WAKEUP_PERIOD / ULP_TIMER_PERIOD)

volatile int32_t wakeup_result;

int main (void)
{
    static uint32_t cycles = 0;
    static int32_t accumulator = 0;

    accumulator += ulp_riscv_adc_read_channel(EXAMPLE_ADC_UNIT, EXAMPLE_ADC_CHANNEL);

    if (++cycles > CYCLES)
    {
        accumulator += CYCLES / 2;
        wakeup_result = accumulator / CYCLES;
        accumulator = 0;
        cycles = 0;
        ulp_riscv_wakeup_main_processor();
    }
    
    return 0;
}
