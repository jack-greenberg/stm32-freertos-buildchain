# Author: Jack Greenberg <j@jackgreenberg.co>

# Always start with version requirement - it's a requirement
cmake_minimum_required(VERSION 3.2)

# Set the project name
project("stm32-proj" LANGUAGES C)

# Use C11 Standard
set(CMAKE_C_STANDARD "11")

# Tell CMake to use the `gcc-arm-none-eabi` toolchain
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/toolchain.cmake")

# Set STM32 SoC specific variables
set(STM32_DEFINES " \
    -DIVECT_TAB_OFFSET=0x0 \
    -DSTM32F1 \
    -DSTM32F103C8Tx \
    -DSTM32 \
    -DSTM32F10X_MD \
")

include(cmake/libopencm3.cmake)

# enable asm for stm startup.s file
enable_language(ASM)
# Custom STM32 options for assembler and gcc
set(STM32_ASM_OPTIONS "-march=armv7-m -mcpu=cortex-m3 -mthumb -mlittle-endian -mthumb-interwork")
SET(CMAKE_ASM_FLAGS "${STM32_ASM_OPTIONS}" CACHE INTERNAL "asm compiler flags")
set(STM32_COMPILER_OPTIONS "${STM32_ASM_OPTIONS} \
                        -ffunction-sections \
                        -fdata-sections \
                        -mfloat-abi=soft \
                        -fmessage-length=0 \
                        -Wall -Werror \
                        -Wl,-Map=output.map -Wl,--gc-sections \
                        -lm -lc")

set(EXTRA_LINKER_FLAGS "-lm -lc --specs=nano.specs")

SET(CMAKE_C_FLAGS "${STM32_COMPILER_OPTIONS} ${COMPILER_OPTIMISATION} -std=c11" CACHE INTERNAL "c compiler flags")
SET(CMAKE_EXE_LINKER_FLAGS "${STM32_COMPILER_OPTIONS} ${LIBOPENCM3_LINKER_FLAGS} -Wl,-Map=linker.map -Wl,-cref " CACHE INTERNAL "exe link flags")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXTRA_LINKER_FLAGS} -T${LINKER_FILE}")

add_subdirectory("${CMAKE_SOURCE_DIR}/src")
