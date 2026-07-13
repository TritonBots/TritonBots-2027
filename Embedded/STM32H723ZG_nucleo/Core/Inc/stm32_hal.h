/* inc/stm32_hal.h */
#ifndef STM32_HAL_H
#define STM32_HAL_H

/* Match on device-level macros (what CMake's MX_Defines_Syms actually sets),
   not family-level macros (those are defined inside the HAL headers themselves). */

/* ── STM32H7 family ── */
#if   defined(STM32H723xx) || defined(STM32H733xx) || \
      defined(STM32H743xx) || defined(STM32H753xx) || \
      defined(STM32H750xx) || defined(STM32H747xx) || \
      defined(STM32H757xx) || defined(STM32H745xx) || \
      defined(STM32H755xx) || defined(STM32H7B0xx) || \
      defined(STM32H7A3xx) || defined(STM32H7B3xx)
    #include "stm32h7xx_hal.h"

/* ── STM32F4 family ── */
#elif defined(STM32F401xC) || defined(STM32F401xE) || \
      defined(STM32F405xx) || defined(STM32F415xx) || \
      defined(STM32F407xx) || defined(STM32F417xx) || \
      defined(STM32F427xx) || defined(STM32F437xx) || \
      defined(STM32F429xx) || defined(STM32F439xx) || \
      defined(STM32F446xx) || defined(STM32F469xx) || \
      defined(STM32F479xx)
    #include "stm32f4xx_hal.h"

/* ── STM32F1 family ── */
#elif defined(STM32F100xB) || defined(STM32F100xE) || \
      defined(STM32F101x6) || defined(STM32F101xB) || \
      defined(STM32F103x6) || defined(STM32F103xB) || \
      defined(STM32F103xE) || defined(STM32F103xG) || \
      defined(STM32F105xC) || defined(STM32F107xC)
    #include "stm32f1xx_hal.h"

/* ── STM32F7 family ── */
#elif defined(STM32F722xx) || defined(STM32F723xx) || \
      defined(STM32F732xx) || defined(STM32F733xx) || \
      defined(STM32F745xx) || defined(STM32F746xx) || \
      defined(STM32F756xx) || defined(STM32F765xx) || \
      defined(STM32F767xx) || defined(STM32F769xx) || \
      defined(STM32F777xx) || defined(STM32F779xx)
    #include "stm32f7xx_hal.h"

/* ── STM32G4 family ── */
#elif defined(STM32G431xx) || defined(STM32G441xx) || \
      defined(STM32G471xx) || defined(STM32G473xx) || \
      defined(STM32G474xx) || defined(STM32G483xx) || \
      defined(STM32G484xx) || defined(STM32G491xx) || \
      defined(STM32G4A1xx)
    #include "stm32g4xx_hal.h"

/* ── STM32L4 family ── */
#elif defined(STM32L431xx) || defined(STM32L432xx) || \
      defined(STM32L433xx) || defined(STM32L442xx) || \
      defined(STM32L443xx) || defined(STM32L451xx) || \
      defined(STM32L452xx) || defined(STM32L462xx) || \
      defined(STM32L471xx) || defined(STM32L475xx) || \
      defined(STM32L476xx) || defined(STM32L485xx) || \
      defined(STM32L486xx) || defined(STM32L496xx) || \
      defined(STM32L4A6xx)
    #include "stm32l4xx_hal.h"

/* ── Add more families as needed ── */

#else
    #error "Unsupported STM32 device. Add your device macro to stm32_hal.h \
(hint: check MX_Defines_Syms in cmake/stm32cubemx/CMakeLists.txt)"
#endif

#endif /* STM32_HAL_H */