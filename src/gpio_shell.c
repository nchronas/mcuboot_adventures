#include <stdio.h>
#include <zephyr/kernel.h>

#include <stdlib.h>

#include <zephyr/shell/shell.h>

#include <zephyr/drivers/gpio.h>

const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);

#ifdef CONFIG_COMMS

const struct gpio_dt_spec emmc_en = GPIO_DT_SPEC_GET(DT_NODELABEL(emmc_en), gpios);
const struct gpio_dt_spec emmc_sel = GPIO_DT_SPEC_GET(DT_NODELABEL(emmc_sel), gpios);

static int cmd_init_gpio(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    int res = 0;
    res = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);

    res |= gpio_pin_configure_dt(&emmc_en, GPIO_OUTPUT_INACTIVE);
    res |= gpio_pin_configure_dt(&emmc_sel, GPIO_OUTPUT_INACTIVE);

    shell_print(sh, "Initiliazed GPIO %u", res);

    return 0;
}

SHELL_CMD_ARG_REGISTER(init_gpio, NULL, "Initialize GPIO", cmd_init_gpio, 1, 0);

static int cmd_set_gpio(const struct shell *sh, size_t argc, char **argv)
{
    if (argc != 3) {
        shell_print(sh, "Not enough arguments");
        return 0;
    }

    char gpio_node = argv[1][0];
    gpio_dt_spec *spec;

    if (gpio_node == 'e') {
        spec = &emmc_en;
    } else if (gpio_node == 'd') {
        spec = &emmc_sel;
    } else if (gpio_node == 'l') {
        spec = &led1;
    } else {
        shell_print(sh, "Wrong argument.");
        return 0;
    }

    char gpio_level = argv[2][0];
    int level = 0;

    if (gpio_level == '0') {
        level = 0;
    } else if (gpio_level == '1') {
        level = 1;
    } else {
        shell_print(sh, "Wrong argument.");
        return 0;
    }

    gpio_pin_set_dt(spec, level);

    shell_print(sh, "Set GPIO");

    return 0;
}

SHELL_CMD_ARG_REGISTER(set_gpio, NULL, "Set GPIO", cmd_set_gpio, 3, 0);

#else

static int cmd_init_gpio(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    int res = 0;
    res = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);

    shell_print(sh, "Initiliazed GPIO %u", res);

    return 0;
}

SHELL_CMD_ARG_REGISTER(init_gpio, NULL, "Initialize GPIO", cmd_init_gpio, 1, 0);

static int cmd_set_gpio(const struct shell *sh, size_t argc, char **argv)
{
    if (argc != 3) {
        shell_print(sh, "Not enough arguments");
        return 0;
    }

    char gpio_node = argv[1][0];
    struct gpio_dt_spec *spec;

    if (gpio_node == 'l') {
        spec = &led1;
    } else {
        shell_print(sh, "Wrong argument.");
        return 0;
    }

    char gpio_level = argv[2][0];
    int level = 0;

    if (gpio_level == '0') {
        level = 0;
    } else if (gpio_level == '1') {
        level = 1;
    } else {
        shell_print(sh, "Wrong argument.");
        return 0;
    }

    gpio_pin_set_dt(spec, level);

    shell_print(sh, "Set GPIO");

    return 0;
}

SHELL_CMD_ARG_REGISTER(set_gpio, NULL, "Set GPIO", cmd_set_gpio, 3, 0);

#endif
