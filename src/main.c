/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/reboot.h>
#include <stdlib.h>

#include <zephyr/shell/shell.h>
#include <version.h>
#include <zephyr/drivers/uart.h>
#include "app_version.h"

#include <zephyr/dfu/flash_img.h>
#include <zephyr/dfu/mcuboot.h>
#include <zephyr/storage/flash_map.h>

#include <zephyr/linker/linker-defs.h>


static int cmd_read_header(const struct shell *sh, size_t argc, char **argv)
{

	if(argc != 2) {
		shell_print(sh, "Not enough arguments");
		return 0;
	}

	struct mcuboot_img_header hd;
	char area_id = argv[1][0];
	uint8_t fa_id;

	if (area_id == '0') {
		fa_id = FIXED_PARTITION_ID(slot0_partition);
	} else if (area_id == '1') {
		fa_id = FIXED_PARTITION_ID(slot1_partition);
	} else {
		shell_print(sh, "Wrong argument.");
	
		return 0;
	}

	int err = boot_read_bank_header( fa_id, &hd, sizeof(hd));

	shell_print(sh, "Image header err: %d, image version %d.%d", err, hd.h.v1.sem_ver.major, hd.h.v1.sem_ver.minor);
	
	return 0;
}

SHELL_CMD_ARG_REGISTER(readhd, NULL, "read image header?", cmd_read_header, 2, 0);


static int cmd_confirmed(const struct shell *sh, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	shell_print(sh, "Is current image confirmed? %s", (boot_is_img_confirmed()? "Yes": " No :("));

	return 0;
}

SHELL_CMD_ARG_REGISTER(confirmed, NULL, "is image confirmed?", cmd_confirmed, 1, 0);


static int cmd_confirm(const struct shell *sh, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	shell_print(sh, "Confirm current image. err= %d (0 for ok)", boot_write_img_confirmed());

	return 0;
}

SHELL_CMD_ARG_REGISTER(confirm, NULL, "confirm image", cmd_confirm, 1, 0);

static int cmd_upgrade(const struct shell *sh, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	int err = boot_request_upgrade(BOOT_UPGRADE_TEST);
  
	shell_print(sh, "upgrade image. err= %d(0 for ok)", err);

	return 0;
}

SHELL_CMD_ARG_REGISTER(upgrade, NULL, "Upgrade image", cmd_upgrade, 1, 0);


int flag = 0;

static int cmd_flag(const struct shell *sh, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	shell_print(sh, "Flag= %d", flag);

	flag++;

	return 0;
}

SHELL_CMD_ARG_REGISTER(flag, NULL, "Add one", cmd_flag, 1, 0);


static int cmd_reboot(const struct shell *sh, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	shell_print(sh, "Reboot MCU Now");

	sys_reboot(0);

	return 0;
}

SHELL_CMD_ARG_REGISTER(reboot, NULL, "Reboot application", cmd_reboot, 1, 0);


static int cmd_version(const struct shell *sh, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	shell_print(sh, "Application version %s", APP_VERSION_STRING);

	return 0;
}

SHELL_CMD_ARG_REGISTER(version, NULL, "Show application version", cmd_version, 1, 0);


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
