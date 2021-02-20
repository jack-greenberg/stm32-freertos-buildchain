# Always start with version requirement - it's a requirement
cmake_minimum_required(VERSION 3.12)

# Tell CMake to use our toolchain file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/toolchain.cmake")

# And start a project
project("stm32")

set(CMAKE_C_STANDARD "11") # C11

add_executable("${PROJECT_NAME}" "src/main.c")
# Produce a file 'program.elf' that can be uploaded to the MCU
set_target_properties("${PROJECT_NAME}" PROPERTIES OUTPUT_NAME "main.elf")


# Compile options and definitions that should be set globally
# For local to the project use `target_compile_definitions`
add_compile_options(
    # CPU specific
    "-mcpu=cortex-m3"
    "-mfloat-abi=soft"
    "-mthumb"
    # Non-CPU specific
    "-ffunction-sections"
    "-fdata-sections"
    "-fstack-usage"
    # Other options
    "-g3"
    "-c"
    "-Os"
    "-Wall"
)

# Set the linker flags
# Unfortunately this is the best way to set the linker flags in CMake
set_target_properties("${PROJECT_NAME}" PROPERTIES LINK_FLAGS
    "-mcpu=cortex-m3 \
    -mthumb \
    -mfloat-abi=soft \
    -T\"${CMAKE_CURRENT_LIST_DIR}/stm32f103c8.ld\" \
    -Wl,-Map=\"${PROJECT_NAME}.map\" \
    -Wl,--gc-sections \
    -static \
    -Wl,--start-group -lc -lm -Wl,--end-group"
)

set(STM32_DEFINES " \
    -DIVECT_TAB_OFFSET=0x0 \
    -DSTM32F1 \
    -DSTM32F103C8Tx \
    -DSTM32 \
    -DSTM32F10X_MD \
    ")

set(CMAKE_C_FLAGS "${STM32_DEFINES}")

include(inc/libopencm3.cmake)
include(inc/freertos.cmake)
