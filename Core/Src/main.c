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
#define LOG_TAG    "main"
    SEGGER_RTT_Init();
    SEGGER_RTT_printf(0, "compile time %s %s\n", __DATE__, __TIME__);
    elog_set_filter_lvl(ELOG_LVL_VERBOSE);
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);//配置输出信息格式
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);//配置输出信息格式
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);//配置输出信息格式
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);//配置输出信息格式
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);//配置输出信息格式
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);//配置输出信息格式
    elog_set_text_color_enabled(true); //使能代码输出颜色
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
        static int i = 0;
        switch (i) {
            case ELOG_LVL_ASSERT:
                log_a("range time %d", rng % 600);
                ++i;
                break;
            case ELOG_LVL_ERROR:
                log_d("range time %d", rng % 600);
                ++i;
                break;
            case ELOG_LVL_WARN:
                log_w("range time %d", rng % 600);
                ++i;
                break;
            case ELOG_LVL_INFO:
                log_i("range time %d", rng % 600);
                ++i;
                break;
            case ELOG_LVL_DEBUG:
                log_d("range time %d", rng % 600);
                ++i;
                break;
            case ELOG_LVL_VERBOSE:
                log_v("range time %d", rng % 600);
                i = 0;
                break;
            default:
                break;
        }
    }
}

