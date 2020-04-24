/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"
#include "stm32g4xx_ll_adc.h"
#include "stm32g4xx_ll_dma.h"
#include "stm32g4xx_ll_tim.h"
#include "stm32g4xx_ll_usart.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx.h"
#include "stm32g4xx_ll_system.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_exti.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_cortex.h"
#include "stm32g4xx_ll_utils.h"
#include "stm32g4xx_ll_pwr.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define IR_SIDE_R_Pin LL_GPIO_PIN_13
#define IR_SIDE_R_GPIO_Port GPIOC
#define IR_SIDE_L_Pin LL_GPIO_PIN_14
#define IR_SIDE_L_GPIO_Port GPIOC
#define IR_FRONT_L_Pin LL_GPIO_PIN_15
#define IR_FRONT_L_GPIO_Port GPIOC
#define SEN_FRONT_R_Pin LL_GPIO_PIN_0
#define SEN_FRONT_R_GPIO_Port GPIOA
#define SEN_SIDE_R_Pin LL_GPIO_PIN_1
#define SEN_SIDE_R_GPIO_Port GPIOA
#define SEN_SIDE_L_Pin LL_GPIO_PIN_2
#define SEN_SIDE_L_GPIO_Port GPIOA
#define SEN_FRONT_L_Pin LL_GPIO_PIN_3
#define SEN_FRONT_L_GPIO_Port GPIOA
#define CS_R_Pin LL_GPIO_PIN_4
#define CS_R_GPIO_Port GPIOA
#define CLK_ENC_Pin LL_GPIO_PIN_5
#define CLK_ENC_GPIO_Port GPIOA
#define MISO_ENC_Pin LL_GPIO_PIN_6
#define MISO_ENC_GPIO_Port GPIOA
#define MOSI_ENC_Pin LL_GPIO_PIN_7
#define MOSI_ENC_GPIO_Port GPIOA
#define BATT_Pin LL_GPIO_PIN_0
#define BATT_GPIO_Port GPIOB
#define CS_L_Pin LL_GPIO_PIN_1
#define CS_L_GPIO_Port GPIOB
#define EXE_Pin LL_GPIO_PIN_2
#define EXE_GPIO_Port GPIOB
#define SPK_Pin LL_GPIO_PIN_10
#define SPK_GPIO_Port GPIOB
#define LED0_Pin LL_GPIO_PIN_11
#define LED0_GPIO_Port GPIOB
#define CS_GYRO_Pin LL_GPIO_PIN_12
#define CS_GYRO_GPIO_Port GPIOB
#define CLK_GYRO_Pin LL_GPIO_PIN_13
#define CLK_GYRO_GPIO_Port GPIOB
#define MISO_GYRO_Pin LL_GPIO_PIN_14
#define MISO_GYRO_GPIO_Port GPIOB
#define MOSI_GYRO_Pin LL_GPIO_PIN_15
#define MOSI_GYRO_GPIO_Port GPIOB
#define LED1_Pin LL_GPIO_PIN_8
#define LED1_GPIO_Port GPIOA
#define SELECT_Pin LL_GPIO_PIN_11
#define SELECT_GPIO_Port GPIOA
#define LED2_Pin LL_GPIO_PIN_12
#define LED2_GPIO_Port GPIOA
#define T_SWDIO_Pin LL_GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin LL_GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define I2C_SCL_Pin LL_GPIO_PIN_15
#define I2C_SCL_GPIO_Port GPIOA
#define LED3_Pin LL_GPIO_PIN_3
#define LED3_GPIO_Port GPIOB
#define DCM_L_0_Pin LL_GPIO_PIN_4
#define DCM_L_0_GPIO_Port GPIOB
#define DCM_L_1_Pin LL_GPIO_PIN_5
#define DCM_L_1_GPIO_Port GPIOB
#define DCM_R_0_Pin LL_GPIO_PIN_6
#define DCM_R_0_GPIO_Port GPIOB
#define DCM_R_1_Pin LL_GPIO_PIN_7
#define DCM_R_1_GPIO_Port GPIOB
#define IR_FRONT_R_Pin LL_GPIO_PIN_8
#define IR_FRONT_R_GPIO_Port GPIOB
#define I2C_SDA_Pin LL_GPIO_PIN_9
#define I2C_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
