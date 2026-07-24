/**
   @file musical_config.h

   @brief configure the PWM signal generation to get the correct musical pitches.

   @see musical_notes.h
*/

#ifndef MUSICAL_CONFIG_H
#define MUSICAL_CONFIG_H

#include "main.h"

/* Device-specific CMSIS header — auto-selected by compiler -D flag */
#if defined(STM32F0)
    #include "stm32f0xx.h"
#elif defined(STM32F1)
    #include "stm32f1xx.h"
#elif defined(STM32F2)
    #include "stm32f2xx.h"
#elif defined(STM32F3)
    #include "stm32f3xx.h"
#elif defined(STM32F4)
    #include "stm32f4xx.h"
#elif defined(STM32F7)
    #include "stm32f7xx.h"
#elif defined(STM32G0)
    #include "stm32g0xx.h"
#elif defined(STM32G4)
    #include "stm32g4xx.h"
#elif defined(STM32H5)
    #include "stm32h5xx.h"
#elif defined(STM32H7)
    #include "stm32h7xx.h"
#elif defined(STM32L0)
    #include "stm32l0xx.h"
#elif defined(STM32L1)
    #include "stm32l1xx.h"
#elif defined(STM32L4)
    #include "stm32l4xx.h"
#elif defined(STM32L5)
    #include "stm32l5xx.h"
#elif defined(STM32U5)
    #include "stm32u5xx.h"
#elif defined(STM32WB)
    #include "stm32wbxx.h"
#elif defined(STM32WL)
    #include "stm32wlxx.h"
#else
    #error "Unsupported STM32 series — add a -DSTM32Xx define to your build flags"
#endif

#define TIM_FREQ 60000000 // change this to your current TIM frequency in Hz
#define TIM_ARR 99 // change this to your TIM ARR (uint16_t)

#define BPM 144.0f // change this to your music's tempo at the quarter note
#define ARTICULATION_DELAY 5 // delay to emphasize the end of each note (in ms)

#endif /* MUSICAL_CONFIG_H */