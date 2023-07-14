/**
 * Copyright (c) 2023 Uri Shaked
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hardware/gpio.h"
#include "pins.h"
#include "ctrl.h"
#include "pico/stdlib.h"

void ctrl_init()
{
  gpio_init(PIN_CTRL_SEL_RST_N);
  gpio_init(PIN_CTRL_SEL_INC);
  gpio_init(PIN_CTRL_ENA);
  gpio_set_dir(PIN_CTRL_SEL_RST_N, GPIO_OUT);
  gpio_set_dir(PIN_CTRL_SEL_INC, GPIO_OUT);
  gpio_set_dir(PIN_CTRL_ENA, GPIO_OUT);
  gpio_put(PIN_CTRL_SEL_RST_N, 0);
  gpio_put(PIN_CTRL_SEL_INC, 0);
  gpio_put(PIN_CTRL_ENA, 0);
}

void ctrl_select_design(uint16_t mux_index)
{
  // Disable the mux
  gpio_put(PIN_CTRL_ENA, 0);

  // Pulse the reset pin
  gpio_put(PIN_CTRL_SEL_RST_N, 0);
  sleep_ms(1);
  gpio_put(PIN_CTRL_SEL_RST_N, 1);
  sleep_ms(1);
  for (uint16_t i = 0; i < mux_index; i++)
  {
    gpio_put(PIN_CTRL_SEL_INC, 1);
    sleep_us(100);
    gpio_put(PIN_CTRL_SEL_INC, 0);
    sleep_us(100);
  }

  // Enable the mux
  gpio_put(PIN_CTRL_ENA, 1);
}
