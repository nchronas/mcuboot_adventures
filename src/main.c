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

#include <zephyr/linker/linker-defs.h>

#include <zephyr/drivers/gpio.h>

const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

int main(void)
{

    printk("Address of sample %p\n", (void *)__rom_region_start);
    printk("Hello sysbuild with mcuboot! %s\n", CONFIG_BOARD);

    k_busy_wait(10000000);
    k_busy_wait(10000);

    const struct device *dev;
    uint32_t dtr = 0;

    gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);

    dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_shell_uart));
    if (!device_is_ready(dev)) {
        return 0;
    }

    while (!dtr) {
        gpio_pin_toggle_dt(&led0);
        k_sleep(K_MSEC(1000));
    }

    return 0;
}
