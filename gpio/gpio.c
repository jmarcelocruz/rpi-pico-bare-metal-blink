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

#include <gpio/gpio.h>
#include <hardware/io_bank0.h>
#include <hardware/pads_bank0.h>
#include <hardware/resets.h>
#include <hardware/sio.h>

void gpio_init(unsigned int gpio) {
    RESETS->reset &= ~(RESETS_IO_BANK0_BITS | RESETS_PADS_BANK0_BITS);
    while ((RESETS->reset_done & RESETS_IO_BANK0_BITS) == 0 | (RESETS->reset_done & RESETS_PADS_BANK0_BITS) == 0) {
        ;
    }

    IO_BANK0->io[gpio].ctrl = GPIO_FUNC_SIO & IO_BANK0_GPIO_CTRL_FUNCSEL_BITS;
    PADS_BANK0->io[gpio] = ((1U << PADS_BANK0_GPIO_IE_LSB) & PADS_BANK0_GPIO_IE_BITS)
        | ((0U << PADS_BANK0_GPIO_OD_LSB) & PADS_BANK0_GPIO_OD_BITS);
    SIO->io_out_clr = (1U << gpio);
    SIO->io_oe_set = (1U << gpio);
}

unsigned int gpio_get(unsigned int gpio) {
    return (SIO->io_in & (1U << gpio)) ? 1U : 0U;
}

void gpio_put(unsigned int gpio, int value) {
    if (value) {
        SIO->io_out_set = (1U << gpio);
    } else {
        SIO->io_out_clr = (1U << gpio);
    }
}
