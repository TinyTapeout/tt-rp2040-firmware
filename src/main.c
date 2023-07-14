/**
 * Copyright (c) 2023 Uri Shaked
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include "pico/bootrom.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"

#include "clkgen.h"
#include "ctrl.h"
#include "pins.h"

bool readline(char *buf, int len)
{
  int i = 0;
  while (i < len - 1)
  {
    char c = getchar();
    if (c == '\n' || c == '\r')
    {
      buf[i] = '\0';
      return stdio_usb_connected();
    }
    buf[i++] = c;
  }

  buf[i] = '\0';
  return stdio_usb_connected();
}

// Default clock configuration - 10 MHz output
struct clkgen_conf_t clkgen_config = {
    .refdiv = 1,
    .vco_freq = 1500 * MHZ,
    .postdiv1 = 5,
    .postdiv2 = 3,
    .pwm_wrap = 9,
    .pwm_duty = 5,
};

void process_commands()
{
  char line[256];
  int int_params[6];
  while (readline(line, sizeof(line)))
  {
    if (strlen(line) == 0)
    {
      continue;
    }

    if (!strcmp(line, "ping"))
    {
      printf("pong=1\n");
    }
    else if (!strcmp(line, "bootloader"))
    {
      reset_usb_boot(0, 0);
    }
    else if (!strcmp(line, "get-clock"))
    {
      printf("clock-freq=%d\n", (uint32_t)clkgen_get_freq(clkgen_config.pwm_wrap));
    }
    else if (sscanf(line, "select-design %d", &int_params[0]) == 1)
    {
      ctrl_select_design(int_params[0]);
      printf("active-design=%d\n", int_params[0]);
    }
    else if (sscanf(line, "set-clock %d %d %d %d %d %d", &int_params[0], &int_params[1], &int_params[2], &int_params[3], &int_params[4], &int_params[5]) == 6)
    {
      clkgen_config.refdiv = int_params[0];
      clkgen_config.vco_freq = int_params[1];
      clkgen_config.postdiv1 = int_params[2];
      clkgen_config.postdiv2 = int_params[3];
      clkgen_config.pwm_wrap = int_params[4];
      clkgen_config.pwm_duty = int_params[5];
      clkgen_configure(&clkgen_config);
      printf("clock-freq=%d\n", (uint32_t)clkgen_get_freq(clkgen_config.pwm_wrap));
    }
    else
    {
      printf("Invalid command\n");
    }
  }
}

int main()
{
  // Temporary output for debugging the clock
  clock_gpio_init(21, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_SYS, 1);

  ctrl_init();
  clkgen_init();
  clkgen_configure(&clkgen_config);
  stdio_init_all();

  while (true)
  {
    // Wait for USB to connect

    while (!stdio_usb_connected())
    {
      sleep_ms(100);
    }

    printf("firmware=TinyTapeout\n");
    printf("version=1\n");
    process_commands();
  }

  return 0;
}