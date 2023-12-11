/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
/* ULP riscv example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "ulp_riscv.h"
#include "ulp_adc.h"
#include "esp_adc/adc_oneshot.h"
#include "ulp_main.h"
#include "ulp/example_config.h"
#include "ulp_riscv_lock.h"
#include "hal/clk_gate_ll.h"

extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_main_bin_start");
extern const uint8_t ulp_main_bin_end[] asm("_binary_ulp_main_bin_end");

static adc_oneshot_unit_handle_t adc_handle;
static void init_ulp_program(void);

static ulp_adc_cfg_t cfg = {
        .adc_n = EXAMPLE_ADC_UNIT,
        .channel = EXAMPLE_ADC_CHANNEL,
        .width = EXAMPLE_ADC_WIDTH,
        .atten = EXAMPLE_ADC_ATTEN,
        .ulp_mode = ADC_ULP_MODE_RISCV,
    };

void app_main(void)
{
    ESP_ERROR_CHECK(esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON)); // So that ULP can use SAR ADC
    init_ulp_program();
    ESP_ERROR_CHECK(esp_sleep_enable_ulp_wakeup());
    vTaskDelay(pdMS_TO_TICKS(100));
    while (1)
    {
        ESP_ERROR_CHECK(ulp_riscv_run());
        esp_light_sleep_start();
        ulp_riscv_halt();
        ulp_adc_deinit();
        printf("ULP-RISC-V woke up the main CPU\n");
        printf("Value = %" PRIu32 "\n", ulp_wakeup_result);
        vTaskDelay(pdMS_TO_TICKS(500));
        ulp_adc_init(&cfg);
    }
}

static void init_ulp_program(void)
{
    ESP_ERROR_CHECK(ulp_adc_init(&cfg));

    /*adc_oneshot_unit_init_cfg_t adc_ulp_cfg = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_RISCV
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&adc_ulp_cfg, &adc_handle));
    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_6,
        .bitwidth = ADC_BITWIDTH_DEFAULT
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, EXAMPLE_ADC_CHANNEL, &config));*/

    esp_err_t err = ulp_riscv_load_binary(ulp_main_bin_start, (ulp_main_bin_end - ulp_main_bin_start));
    ESP_ERROR_CHECK(err);

    /* The first argument is the period index, which is not used by the ULP-RISC-V timer
     * The second argument is the period in microseconds, which gives a wakeup time period of: 20ms
     */
    ulp_set_wakeup_period(0, 20000);
}
