/**
   @file musical_config.h

   @brief configure the PWM signal generation to get the correct musical pitches.

   @see musical_notes.h
*/

#ifndef MUSICAL_CONFIG_H
#define MUSICAL_CONFIG_H

#include "stm32f103xb.h" // change to your STM32 MCU series
#include "stm32f1xx_hal.h" // change to your STM32 MCU series for HAL

#define TIM_FREQ 60000000 // change this to your current TIM frequency in Hz
#define TIM_ARR 99 // change this to your TIM ARR (uint16_t)

#define BPM 120.0f // change this to your music's tempo

#endif /* MUSICAL_CONFIG_H */