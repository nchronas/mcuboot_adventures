/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <stdlib.h>

#include <version.h>
#include <zephyr/drivers/uart.h>
#include "app_version.h"
#include <zephyr/drivers/gpio.h>

#include <zephyr/linker/linker-defs.h>


const struct gpio_dt_spec emmc_en = GPIO_DT_SPEC_GET(DT_NODELABEL(emmc_en), gpios);
const struct gpio_dt_spec emmc_sel = GPIO_DT_SPEC_GET(DT_NODELABEL(emmc_sel), gpios);

const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);


int main(void)
{

    printk("Address of sample %p\n", (void *)__rom_region_start);
    printk("Hello sysbuild with mcuboot! %s\n", CONFIG_BOARD);

	gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
gpio_pin_set_dt(&led0, 1);
gpio_pin_set_dt(&led1, 0);


    const struct device *dev;
    uint32_t dtr = 0;

    // dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_shell_uart));
    // if (!device_is_ready(dev)) {
    //     return 0;
    // }



    while (!dtr) {
        // uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
        // k_sleep(K_MSEC(100));
        k_sleep(K_SECONDS(1));


    gpio_pin_toggle_dt(&led1);

    }

    return 0;
}

