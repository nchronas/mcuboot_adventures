# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

set(CONF_FILE prj.conf shell.conf lfs.conf mcuboot-app.conf)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/mcuboot_shell.c)
target_sources(app PRIVATE src/lfs_shell.c)
