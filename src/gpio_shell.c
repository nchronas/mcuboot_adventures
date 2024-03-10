#include <stdio.h>
#include <zephyr/kernel.h>

#include <stdlib.h>

#include <zephyr/shell/shell.h>

#include <zephyr/drivers/gpio.h>

const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);

#define CONFIG_COMMS 1

#ifdef CONFIG_COMMS

const struct gpio_dt_spec emmc_en = GPIO_DT_SPEC_GET(DT_NODELABEL(emmc_en), gpios);
const struct gpio_dt_spec emmc_sel = GPIO_DT_SPEC_GET(DT_NODELABEL(emmc_sel), gpios);
const struct gpio_dt_spec emmc_rst = GPIO_DT_SPEC_GET(DT_NODELABEL(emmc_rst), gpios);


// #include "stm32h7xx_hal.h"
#include <soc.h>

#define RF_SPI_SCL_Pin GPIO_PIN_2
#define RF_SPI_SCL_GPIO_Port GPIOE
#define MIXER_RST_Pin GPIO_PIN_3
#define MIXER_RST_GPIO_Port GPIOE
#define RF_SPI_SEL_Pin GPIO_PIN_4
#define RF_SPI_SEL_GPIO_Port GPIOE
#define RF_SPI_MISO_Pin GPIO_PIN_5
#define RF_SPI_MISO_GPIO_Port GPIOE
#define RF_SPI_MOSI_Pin GPIO_PIN_6
#define RF_SPI_MOSI_GPIO_Port GPIOE
#define MMC_RST_Pin GPIO_PIN_13
#define MMC_RST_GPIO_Port GPIOC
#define TCXO_OUT_Pin GPIO_PIN_0
#define TCXO_OUT_GPIO_Port GPIOH
#define TCXO_EN_Pin GPIO_PIN_1
#define TCXO_EN_GPIO_Port GPIOH
#define EN_MIXER_Pin GPIO_PIN_0
#define EN_MIXER_GPIO_Port GPIOC
#define RF_IRQ_Pin GPIO_PIN_1
#define RF_IRQ_GPIO_Port GPIOC
#define RF_IRQ_EXTI_IRQn EXTI1_IRQn
#define EN_AMP_RX_UHF_Pin GPIO_PIN_1
#define EN_AMP_RX_UHF_GPIO_Port GPIOA
#define FLAGB_RX_S_Pin GPIO_PIN_2
#define FLAGB_RX_S_GPIO_Port GPIOA
#define VSET_AGC_S_Pin GPIO_PIN_4
#define VSET_AGC_S_GPIO_Port GPIOA
#define VSET_AGC_UHF_Pin GPIO_PIN_5
#define VSET_AGC_UHF_GPIO_Port GPIOA
#define AGC_TEMP_S_Pin GPIO_PIN_6
#define AGC_TEMP_S_GPIO_Port GPIOA
#define GAIN_SET_S_Pin GPIO_PIN_7
#define GAIN_SET_S_GPIO_Port GPIOA
#define GAIN_SET_UHF_Pin GPIO_PIN_4
#define GAIN_SET_UHF_GPIO_Port GPIOC
#define AGC_TEMP_U_Pin GPIO_PIN_5
#define AGC_TEMP_U_GPIO_Port GPIOC
#define FLT_SEL_UHF_Pin GPIO_PIN_0
#define FLT_SEL_UHF_GPIO_Port GPIOB
#define EN_AGC_UHF_Pin GPIO_PIN_1
#define EN_AGC_UHF_GPIO_Port GPIOB
#define EN_PA_UHF_Pin GPIO_PIN_2
#define EN_PA_UHF_GPIO_Port GPIOB
#define RF_RST_Pin GPIO_PIN_7
#define RF_RST_GPIO_Port GPIOE
#define ALERT_T_PA_U_Pin GPIO_PIN_8
#define ALERT_T_PA_U_GPIO_Port GPIOE
#define FLAGB_TX_UHF_Pin GPIO_PIN_9
#define FLAGB_TX_UHF_GPIO_Port GPIOE
#define FLAGB_RX_UHF_Pin GPIO_PIN_10
#define FLAGB_RX_UHF_GPIO_Port GPIOE
#define EN_RX_UHF_Pin GPIO_PIN_11
#define EN_RX_UHF_GPIO_Port GPIOE
#define ALERT_T_PCB_Pin GPIO_PIN_12
#define ALERT_T_PCB_GPIO_Port GPIOE
#define P5V_RF_EN_Pin GPIO_PIN_13
#define P5V_RF_EN_GPIO_Port GPIOE
#define LED_PE14_Pin GPIO_PIN_14
#define LED_PE14_GPIO_Port GPIOE
#define LED_PE15_Pin GPIO_PIN_15
#define LED_PE15_GPIO_Port GPIOE
#define BUS_SCL_Pin GPIO_PIN_10
#define BUS_SCL_GPIO_Port GPIOB
#define BUS_SDA_Pin GPIO_PIN_11
#define BUS_SDA_GPIO_Port GPIOB
#define FPGA_SPI_SEL_Pin GPIO_PIN_12
#define FPGA_SPI_SEL_GPIO_Port GPIOB
#define FPGA_SPI_SCL_Pin GPIO_PIN_13
#define FPGA_SPI_SCL_GPIO_Port GPIOB
#define FPGA_SPI_MISO_Pin GPIO_PIN_14
#define FPGA_SPI_MISO_GPIO_Port GPIOB
#define FPGA_SPI_MOSI_Pin GPIO_PIN_15
#define FPGA_SPI_MOSI_GPIO_Port GPIOB
#define P5V_FPGA_EN_Pin GPIO_PIN_8
#define P5V_FPGA_EN_GPIO_Port GPIOD
#define P5V_FPGA_PG_Pin GPIO_PIN_9
#define P5V_FPGA_PG_GPIO_Port GPIOD
#define ANT_DET_1_Pin GPIO_PIN_10
#define ANT_DET_1_GPIO_Port GPIOD
#define ANT_DEP_1_Pin GPIO_PIN_11
#define ANT_DEP_1_GPIO_Port GPIOD
#define ANT_DET_0_Pin GPIO_PIN_12
#define ANT_DET_0_GPIO_Port GPIOD
#define ANT_DEP_0_Pin GPIO_PIN_13
#define ANT_DEP_0_GPIO_Port GPIOD
#define ALERT_T_PA_S_Pin GPIO_PIN_14
#define ALERT_T_PA_S_GPIO_Port GPIOD
#define FLAGB_TX_S_Pin GPIO_PIN_15
#define FLAGB_TX_S_GPIO_Port GPIOD
#define MMC_EN_Pin GPIO_PIN_6
#define MMC_EN_GPIO_Port GPIOC
#define P5V_RF_PG_Pin GPIO_PIN_7
#define P5V_RF_PG_GPIO_Port GPIOC
#define MCU_MMC_D0_Pin GPIO_PIN_8
#define MCU_MMC_D0_GPIO_Port GPIOC
#define MIXER_SDA_Pin GPIO_PIN_9
#define MIXER_SDA_GPIO_Port GPIOC
#define MIXER_SCL_Pin GPIO_PIN_8
#define MIXER_SCL_GPIO_Port GPIOA
#define P3V3_RF_PG_Pin GPIO_PIN_9
#define P3V3_RF_PG_GPIO_Port GPIOA
#define MEM_SEL_Pin GPIO_PIN_10
#define MEM_SEL_GPIO_Port GPIOA
#define BUS_SPI_SCL_Pin GPIO_PIN_10
#define BUS_SPI_SCL_GPIO_Port GPIOC
#define BUS_SPI_MISO_Pin GPIO_PIN_11
#define BUS_SPI_MISO_GPIO_Port GPIOC
#define MCU_MMC_CK_Pin GPIO_PIN_12
#define MCU_MMC_CK_GPIO_Port GPIOC
#define CAN1_RX_Pin GPIO_PIN_0
#define CAN1_RX_GPIO_Port GPIOD
#define CAN1_TX_Pin GPIO_PIN_1
#define CAN1_TX_GPIO_Port GPIOD
#define MCU_MMC_CMD_Pin GPIO_PIN_2
#define MCU_MMC_CMD_GPIO_Port GPIOD
#define CAN_EN_Pin GPIO_PIN_3
#define CAN_EN_GPIO_Port GPIOD
#define CAN1_STB_Pin GPIO_PIN_4
#define CAN1_STB_GPIO_Port GPIOD
#define CAN2_EN_Pin GPIO_PIN_5
#define CAN2_EN_GPIO_Port GPIOD
#define BUS_SPI_MOSI_Pin GPIO_PIN_6
#define BUS_SPI_MOSI_GPIO_Port GPIOD
#define CAN2_STB_Pin GPIO_PIN_7
#define CAN2_STB_GPIO_Port GPIOD
#define CAN2_RX_Pin GPIO_PIN_5
#define CAN2_RX_GPIO_Port GPIOB
#define CAN2_TX_Pin GPIO_PIN_6
#define CAN2_TX_GPIO_Port GPIOB
#define SMDATA_Pin GPIO_PIN_7
#define SMDATA_GPIO_Port GPIOB
#define SMCLK_Pin GPIO_PIN_8
#define SMCLK_GPIO_Port GPIOB
#define MIXER_ENX_Pin GPIO_PIN_0
#define MIXER_ENX_GPIO_Port GPIOE
#define FLAGB_MIXER_Pin GPIO_PIN_1
#define FLAGB_MIXER_GPIO_Port GPIOE


static int cmd_tst_mmc(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    MMC_HandleTypeDef hmmc1;

    GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hmmc1.Instance==SDMMC1)
  {
  /* USER CODE BEGIN SDMMC1_MspInit 0 */

  /* USER CODE END SDMMC1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDMMC;
    PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        shell_print(sh, "error HAL %u");
    }

    /* Peripheral clock enable */
    __HAL_RCC_SDMMC1_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**SDMMC1 GPIO Configuration
    PC8     ------> SDMMC1_D0
    PC12     ------> SDMMC1_CK
    PD2     ------> SDMMC1_CMD
    */
    GPIO_InitStruct.Pin = MCU_MMC_D0_Pin|MCU_MMC_CK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = MCU_MMC_CMD_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
    HAL_GPIO_Init(MCU_MMC_CMD_GPIO_Port, &GPIO_InitStruct);
  } 


    // GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  GPIO_InitStruct.Pin = MCU_MMC_D0_Pin;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(MCU_MMC_D0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MEM_SEL_GPIO_Port, MEM_SEL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : MIXER_RST_Pin MIXER_ENX_Pin */
  GPIO_InitStruct.Pin = MIXER_RST_Pin|MIXER_ENX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : MMC_RST_Pin EN_MIXER_Pin MMC_EN_Pin */
  GPIO_InitStruct.Pin = MMC_RST_Pin|EN_MIXER_Pin|MMC_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* Initialize EMMC, in v0.2 eMMC is always ON */
  HAL_GPIO_WritePin(MMC_RST_GPIO_Port, MMC_RST_Pin, GPIO_PIN_SET); // 2.184W @ 12V
  HAL_GPIO_WritePin(MMC_EN_GPIO_Port, MMC_EN_Pin, GPIO_PIN_RESET);
//   emmc_memory.set_dir(satnogs::comms::emmc::dir::MCU);
    HAL_GPIO_WritePin(MEM_SEL_GPIO_Port, MEM_SEL_Pin, GPIO_PIN_SET);
  k_sleep(K_MSEC(1000));

	  HAL_MMC_CardInfoTypeDef pCardInfo;
	  HAL_MMC_CardStateTypeDef card_state;
	  HAL_MMC_StateTypeDef state;
      HAL_StatusTypeDef res;


  hmmc1.Instance = SDMMC1;
  hmmc1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hmmc1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hmmc1.Init.BusWide = SDMMC_BUS_WIDE_1B;
  hmmc1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hmmc1.Init.ClockDiv = 2;
  res = HAL_MMC_Init(&hmmc1);

    card_state = HAL_MMC_GetCardState(&hmmc1);
    // state = HAL_MMC_GetState(&hmmc1);

  if (res != HAL_OK)
  {
        shell_print(sh, "error HAL 2 %d, %d", res, card_state);
        return 0;

  }


    shell_print(sh, "Initiliazed HAL %d %u %d", res, (res != HAL_OK), card_state);
    
    res = HAL_MMC_GetCardInfo(&hmmc1, &pCardInfo);
    shell_print(sh, "Card info: %u %u %u %u %u %u %u, %d",pCardInfo.CardType, pCardInfo.Class,pCardInfo.RelCardAdd,pCardInfo.BlockNbr,pCardInfo.BlockSize,pCardInfo.LogBlockNbr,pCardInfo.LogBlockSize, res);

//   uint32_t CardType;                     /*!< Specifies the card Type                         */

//   uint32_t Class;                        /*!< Specifies the class of the card class           */

//   uint32_t RelCardAdd;                   /*!< Specifies the Relative Card Address             */

//   uint32_t BlockNbr;                     /*!< Specifies the Card Capacity in blocks           */

//   uint32_t BlockSize;                    /*!< Specifies one block size in bytes               */

//   uint32_t LogBlockNbr;                  /*!< Specifies the Card logical Capacity in blocks   */

//   uint32_t LogBlockSize;                 /*!< Specifies logical block size in bytes           */

    uint8_t wData[512] = {0};
    uint8_t rData[512] = {0};

    strncpy(wData, "Hello LSF\n", 10);
    wData[10] = 0;

    res = HAL_MMC_WriteBlocks(&hmmc1, wData, 1, 1, 1000);
    if (res != HAL_OK)
    {
            shell_print(sh, "error HAL 3 %d", res);
            return 0;
    }

    res = HAL_MMC_ReadBlocks(&hmmc1, rData, 1, 1, 1000);
    if (res != HAL_OK)
    {
            shell_print(sh, "error HAL 4 %d", res);
            return 0;
    }

    rData[10] = 0;

    shell_print(sh, "Read block %s", rData);

/*	for (block = 0; block < pCardInfo.BlockNbr; block++) {
		ret = HAL_MMC_WriteBlocks(&hmmc1, wData, 1, 1, 1000);
		ret = HAL_MMC_ReadBlocks(&hmmc1, rData, 1, 1, 1000);
		if (ret != HAL_OK) break;
	}*/


    return 0;
}

SHELL_CMD_ARG_REGISTER(tst_mmc, NULL, "Initialize GPIO", cmd_tst_mmc, 1, 0);



static int cmd_init_gpio(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    int res = 0;
    res = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);

    res |= gpio_pin_configure_dt(&emmc_en, GPIO_OUTPUT_INACTIVE);
    res |= gpio_pin_configure_dt(&emmc_sel, GPIO_OUTPUT_ACTIVE);
    res |= gpio_pin_configure_dt(&emmc_rst, GPIO_OUTPUT_INACTIVE);

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

    if (gpio_node == 'e') {
        spec = &emmc_en;
    } else if (gpio_node == 'd') {
        spec = &emmc_sel;
    } else if (gpio_node == 'l') {
        spec = &led1;    
    } else if (gpio_node == 'r') {
        spec = &emmc_rst;
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

static int cmd_tst_gpio(const struct shell *sh, size_t argc, char **argv)
{



    gpio_pin_set_dt(&emmc_rst, 0);
    k_sleep(K_MSEC(1000));
    gpio_pin_set_dt(&emmc_sel, 1);
    gpio_pin_set_dt(&emmc_en, 0);

    shell_print(sh, "Fingers crossed");

    return 0;
}

SHELL_CMD_ARG_REGISTER(tst, NULL, "Testing mount configuration GPIO", cmd_tst_gpio, 1, 0);

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
