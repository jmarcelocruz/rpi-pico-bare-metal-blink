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
 *  limitations under the License. */

#ifndef HW_XOSC_H
#define HW_XOSC_H

#include <types.h>

typedef struct {
    rw32_t ctrl;
    rw32_t status;
    rw32_t dormant;
    rw32_t startup;
    uint32_t _pad0[3]; /* undefined in datasheet */
    rw32_t count;
} xosc_hw_t;

#define XOSC ((xosc_hw_t *)0x40024000)

#define XOSC_CTRL_ENABLE_LSB (12)
#define XOSC_CTRL_FREQ_RANGE_LSB (0)

#define XOSC_CTRL_ENABLE_DISABLE (0xd1e)
#define XOSC_CTRL_ENABLE_ENABLE (0xfab)

/* although datasheet says 0xaa0, I have observed the reset value on my board to
 * be the one 0xfa5 */
#define XOSC_CTRL_FREQ_RANGE_VALUE (0xfa5)

#define XOSC_STATUS_STABLE_LSB (31)
#define XOSC_STATUS_STABLE_BITS (1U << XOSC_STATUS_STABLE_LSB)

#define XOSC_STARTUP_DELAY_LSB (0)

/* value taken from datasheet - results in a wait time of just over 1ms for the
 * default 12 MHz crystal */
#define XOSC_STARTUP_DELAY_DEFAULT (47)

#define XOSC_MHZ (12)

#endif
