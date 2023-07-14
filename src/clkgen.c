/**
 * Copyright (c) 2023 Uri Shaked
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hardware/pwm.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"

#include "pins.h"
#include "clkgen.h"
#include "pico/stdlib.h"

void clkgen_init()
{
  gpio_set_function(PIN_CLK_OUT, GPIO_FUNC_PWM);
}

void clkgen_configure(struct clkgen_conf_t *config)
{
  uint pwm_slice_num = pwm_gpio_to_slice_num(PIN_CLK_OUT);
  pwm_set_enabled(pwm_slice_num, false);

  // Temporarily switch to crystal clock
  clock_configure(clk_sys,
                  CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                  CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_XOSC_CLKSRC,
                  12 * MHZ,
                  12 * MHZ);

  pll_init(pll_sys, config->refdiv, config->vco_freq, config->postdiv1, config->postdiv2);
  uint32_t pll_freq = config->vco_freq / config->postdiv1 / config->postdiv2;

  // Switch back to PLL
  clock_configure(clk_sys,
                  CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                  CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS,
                  pll_freq,
                  pll_freq);

  // PWM Config
  pwm_set_wrap(pwm_slice_num, config->pwm_wrap);
  pwm_set_chan_level(pwm_slice_num, PWM_CHAN_A, config->pwm_duty);
  pwm_set_chan_level(pwm_slice_num, PWM_CHAN_B, config->pwm_duty);
  pwm_set_enabled(pwm_slice_num, true);
}

double clkgen_get_freq(uint32_t pwm_wrap)
{
  return clock_get_hz(clk_sys) / (pwm_wrap + 1);
}