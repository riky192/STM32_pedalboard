#ifndef PCM3168A_H
#define PCM3168A_H

#include "stm32h7xx_hal.h"

#define PCM3168A_I2C_ADDRESS (0x40 << 1) // Adjust based on your I2C address
#define PCM3168A_RESET_PIN GPIO_PIN_5
#define PCM3168A_RESET_PORT GPIOB

void PCM3168A_Init(I2C_HandleTypeDef *hi2c, SAI_HandleTypeDef *hsai_a, SAI_HandleTypeDef *hsai_b);
void PCM3168A_Reset(void);
HAL_StatusTypeDef PCM3168A_WriteRegister(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t value);

#endif // PCM3168A_H
