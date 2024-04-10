/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rng.h"
#include "gpio.h"
#include "SEGGER_RTT.h"
#include "elog.h"
#include "init.h"
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {

    SEGGER_RTT_Init();
    elog_set_filter_lvl(ELOG_LVL_VERBOSE);
    elog_start();
    MPU_Config();
    CPU_CACHE_Enable();
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_RNG_Init();
    uint32_t rng;
    while (1) {
        HAL_RNG_GenerateRandomNumber(&hrng, &rng);
        HAL_GPIO_TogglePin(PE3_GPIO_Port, PE3_Pin);
        HAL_Delay(rng % 600);
        log_a("range time %d", rng % 600);
    }
}

