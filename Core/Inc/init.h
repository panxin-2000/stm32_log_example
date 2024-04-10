//
// Created by panxin on 24-4-10.
//

#ifndef GPIO_INIT_H
#define GPIO_INIT_H

void MPU_Config(void);
void CPU_CACHE_Enable(void);
void SystemClock_Config(void);
void Error_Handler(void);
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line);
#endif

#endif //GPIO_INIT_H

