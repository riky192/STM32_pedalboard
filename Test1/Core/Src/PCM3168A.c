/*
 * PCM3168.c
 *
 *  Created on: May 25, 2024
 *      Author: riccardo
 */

#include "pcm3168a.h"

// PCM3168A Register Addresses
#define PCM3168A_REG_00 0x00 // Power Down Control
#define PCM3168A_REG_40 0x40 // AOSR
#define PCM3168A_REG_41 0x41 // DOSR
#define PCM3168A_REG_50 0x50 // Digital Audio Interface Format Control 1
#define PCM3168A_REG_51 0x51 // Digital Audio Interface Format Control 2
#define PCM3168A_REG_52 0x52 // Digital Audio Interface Format Control 3
#define PCM3168A_REG_54 0x54 // Audio Interface Control


// Written by Elyakim

// Function Prototypes
static void PCM3168A_I2C_Init(I2C_HandleTypeDef *hi2c);
static void PCM3168A_SAI_Init(SAI_HandleTypeDef *hsai_a, SAI_HandleTypeDef *hsai_b);
HAL_StatusTypeDef PCM3168A_WriteRegister(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t value);

// PCM3168A Initialization
void PCM3168A_Init(I2C_HandleTypeDef *hi2c, SAI_HandleTypeDef *hsai_a, SAI_HandleTypeDef *hsai_b) {
    PCM3168A_Reset();

    PCM3168A_I2C_Init(hi2c);
    PCM3168A_SAI_Init(hsai_a, hsai_b);

    // PCM3168A Register Initialization for 48kHz, I2S/Left-Justified TDM

    // Power Down Control: Exit power down
    PCM3168A_WriteRegister(hi2c, PCM3168A_REG_00, 0x00);

    // AOSR: Audio Oversampling Rate (Default for 48kHz)
    PCM3168A_WriteRegister(hi2c, PCM3168A_REG_40, 0x80);

    // DOSR: DAC Oversampling Rate (Default for 48kHz)
    PCM3168A_WriteRegister(hi2c, PCM3168A_REG_41, 0x80);

    // Digital Audio Interface Format Control: I2S or Left-Justified TDM
    PCM3168A_WriteRegister(hi2c, PCM3168A_REG_50, 0x00); // Format control 1
    PCM3168A_WriteRegister(hi2c, PCM3168A_REG_51, 0x00); // Format control 2
    PCM3168A_WriteRegister(hi2c, PCM3168A_REG_52, 0x00); // Format control 3

    // Audio Interface Control: TDM, I2S Mode
    PCM3168A_WriteRegister(hi2c, PCM3168A_REG_54, 0x00);
}

// PCM3168A Reset
void PCM3168A_Reset(void) {
    HAL_GPIO_WritePin(PCM3168A_RESET_PORT, PCM3168A_RESET_PIN, GPIO_PIN_RESET);
    HAL_Delay(10); // 10ms delay
    HAL_GPIO_WritePin(PCM3168A_RESET_PORT, PCM3168A_RESET_PIN, GPIO_PIN_SET);
    HAL_Delay(10); // 10ms delay
}

// I2C Initialization (Assuming hi2c is already configured)
static void PCM3168A_I2C_Init(I2C_HandleTypeDef *hi2c) {
    // Add additional configuration if necessary
}

// SAI Initialization (Assuming hsai_a and hsai_b are already configured)
static void PCM3168A_SAI_Init(SAI_HandleTypeDef *hsai_a, SAI_HandleTypeDef *hsai_b) {
    // Add additional configuration if necessary
}

// Write to PCM3168A Register
HAL_StatusTypeDef PCM3168A_WriteRegister(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t value) {
    uint8_t data[2] = {reg, value};
    return HAL_I2C_Master_Transmit(hi2c, PCM3168A_I2C_ADDRESS, data, 2, HAL_MAX_DELAY);
}


