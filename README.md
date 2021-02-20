# STM32-FreeRTOS Buildchain Example

__Goal:__ The purpose of this repository and documentation is to demonstrate a buildchain
implementation for the STM32F103C8 (STM32) microcontroller found on the _STM32 Blue Pill_ dev board.

## Components

* __CMake__ is used to generate the build tools. It is used to generate Makefiles that are
then used to compile code.
* __libopencm3__ is used as a _hardware abstraction library (HAL)_ for the STM32.
* __FreeRTOS__ is the real-time operating system used. It exposes APIs like threads,
queues, semaphores, mutexes, and other helpful constructs.

## How They Work
