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

#ifndef RESETS_H
#define RESETS_H

#include <types.h>

typedef struct {
    rw32_t reset;
    rw32_t wdsel;
    ro32_t reset_done;
} resets_hw_t;

#define RESETS_IO_BANK0_BITS (1U << 5)
#define RESETS_PADS_BANK0_BITS (1U << 8)

#define RESETS ((resets_hw_t *)0x4000c000)

#endif
