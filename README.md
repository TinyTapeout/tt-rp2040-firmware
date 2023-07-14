# tt-rp2040-firmware

A simple firmware for the Tiny Tapeout breakout board with the RP2040 microcontroller.

## Pinout

| Pin | Function     | Signal    |
| --- | ------------ | --------- |
| 0   | Controller   | SEL_RST_N |
| 1   | Controller   | SEL_INC   |
| 2   | Controller   | ENA       |
| 3   | Clock Output | CLK       |

## Commands

The firmware supports the following commands over the USB serial port:

| Command              | Description                                                  |
| -------------------- | ------------------------------------------------------------ |
| `ping`               | Returns `pong=1`                                             |
| `bootloader`         | Reboots the board into the UF2 bootloader mode               |
| `select-design <id>` | Selects the active design on the Tiny Tapeout Mux controller |
| `get-clock`          | Returns the current clock frequency (on CLK pin)             |
| `set-clock <params>` | Configure the clock generator, see examples below            |

### `set-clock` Examples

| Frequency | Command                                |
| --------- | -------------------------------------- |
| 50 MHz    | `set-clock 1 1500000000 5 3 1 1`       |
| 48 MHz    | `set-clock 1 1536000000 4 4 1 1`       |
| 20 MHz    | `set-clock 1 1440000000 6 2 5 3`       |
| 12 MHz    | `set-clock 1 1440000000 6 2 9 5`       |
| 10 MHz    | `set-clock 1 1500000000 5 3 9 5`       |
| 1 MHz     | `set-clock 1 1500000000 5 3 99 50`     |
| 10 kHz    | `set-clock 1 1500000000 5 3 9999 5000` |

## License

Copyright 2023 Uri Shaked

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.