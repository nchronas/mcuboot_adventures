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


int main(void)
{

    printk("Address of sample %p\n", (void *)__rom_region_start);
    printk("Hello sysbuild with mcuboot! %s\n", CONFIG_BOARD);

    const struct device *dev;
    uint32_t dtr = 0;

    dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_shell_uart));
    if (!device_is_ready(dev)) {
        return 0;
    }

    while (!dtr) {
        uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
        k_sleep(K_MSEC(100));
    }

    return 0;
}
