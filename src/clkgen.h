
/**
 * Copyright (c) 2023 Uri Shaked
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CLKGEN_H
#define CLKGEN_H

struct clkgen_conf_t
{
  uint32_t refdiv;
  uint32_t vco_freq;
  uint32_t postdiv1;
  uint32_t postdiv2;
  uint32_t pwm_wrap;
  uint32_t pwm_duty;
};

extern void clkgen_init();
extern void clkgen_configure(struct clkgen_conf_t *conf);
extern double clkgen_get_freq(uint32_t pwm_wrap);

#endif // CLKGEN_H