/*  Copyright 2024 José Marcelo Marques da Cruz
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0

 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef PADS_BANK0_H
#define PADS_BANK0_H

#include <types.h>

typedef struct {
    rw32_t voltage_select;
    rw32_t io[30];
    rw32_t swclk;
    rw32_t swd;
} pads_bank0_hw_t;

#define PADS_BANK0_GPIO_IE_LSB  (6)
#define PADS_BANK0_GPIO_IE_BITS (1U << PADS_BANK0_GPIO_IE_LSB)
#define PADS_BANK0_GPIO_OD_LSB  (7)
#define PADS_BANK0_GPIO_OD_BITS (1U << PADS_BANK0_GPIO_OD_LSB)

#define PADS_BANK0 ((pads_bank0_hw_t *)0x4001c000)

#endif
