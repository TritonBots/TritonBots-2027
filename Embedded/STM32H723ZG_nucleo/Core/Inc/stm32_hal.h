/* Core/Inc/stm32_hal.h */
#ifndef STM32_HAL_H
#define STM32_HAL_H

/*
 * Universal HAL include — resolves to the correct family header
 * based on the MCU macro defined in CMakeLists.txt (via -D flag).
 *
 * Add new families here as needed.
 */

#if defined(STM32F0xx)
    #include "stm32f0xx_hal.h"
#elif defined(STM32F1xx)
    #include "stm32f1xx_hal.h"
#elif defined(STM32F2xx)
    #include "stm32f2xx_hal.h"
#elif defined(STM32F3xx)
    #include "stm32f3xx_hal.h"
#elif defined(STM32F4xx)
    #include "stm32f4xx_hal.h"
#elif defined(STM32F7xx)
    #include "stm32f7xx_hal.h"
#elif defined(STM32G0xx)
    #include "stm32g0xx_hal.h"
#elif defined(STM32G4xx)
    #include "stm32g4xx_hal.h"
#elif defined(STM32H5xx)
    #include "stm32h5xx_hal.h"
#elif defined(STM32H7xx)
    #include "stm32h7xx_hal.h"
    #include "stm32h7xx_hal_gpio.h"
#elif defined(STM32L0xx)
    #include "stm32l0xx_hal.h"
#elif defined(STM32L1xx)
    #include "stm32l1xx_hal.h"
#elif defined(STM32L4xx)
    #include "stm32l4xx_hal.h"
#elif defined(STM32L5xx)
    #include "stm32l5xx_hal.h"
#elif defined(STM32U5xx)
    #include "stm32u5xx_hal.h"
#elif defined(STM32WBxx)
    #include "stm32wbxx_hal.h"
#else
    #error "Unsupported STM32 family. Add your MCU family to stm32_hal.h"
#endif

#endif /* STM32_HAL_H */