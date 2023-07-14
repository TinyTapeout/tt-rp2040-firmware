cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(tt_firmware C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(tt_firmware
  src/clkgen.c
  src/ctrl.c
  src/main.c
)

pico_enable_stdio_uart(tt_firmware 0)
pico_enable_stdio_usb(tt_firmware 1)

pico_add_extra_outputs(tt_firmware)
target_link_libraries(
  tt_firmware
  pico_stdlib
  hardware_clocks
  hardware_pio
  hardware_pwm
)
