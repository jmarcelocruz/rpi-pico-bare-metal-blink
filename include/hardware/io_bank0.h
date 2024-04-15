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

#ifndef IO_BANK0_H
#define IO_BANK0_H

#include <types.h>

typedef struct {
    ro32_t status;
    rw32_t ctrl;
} io_bank0_status_ctrl_hw_t;

#define IO_BANK0_GPIO_CTRL_FUNCSEL_BITS (0x1f)

typedef struct {
    rw32_t inte[4];
    rw32_t intf[4];
    ro32_t ints[4];
} io_bank0_irq_ctrl_hw_t;

typedef struct {
    io_bank0_status_ctrl_hw_t io[30];
    rw32_t intr[4];
    io_bank0_irq_ctrl_hw_t proc0_irq_ctrl;
    io_bank0_irq_ctrl_hw_t proc1_irq_ctrl;
    io_bank0_irq_ctrl_hw_t dormant_wake_irq_ctrl;
} io_bank0_hw_t;

#define IO_BANK0 ((io_bank0_hw_t *)0x40014000)

#endif
