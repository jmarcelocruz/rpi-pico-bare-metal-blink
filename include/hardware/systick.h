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

#ifndef HW_SYSTICK_H
#define HW_SYSTICK_H

#include <types.h>

typedef struct {
    rw32_t csr;
    rw32_t rvr;
    rw32_t cvr;
    ro32_t calib;
} systick_hw_t;

#define SYSTICK_CSR_ENABLE_LSB (0)
#define SYSTICK_CSR_TICKINT_LSB (1)
#define SYSTICK_CSR_CLKSOURCE_LSB (2)

#define SYSTICK ((systick_hw_t *)0xe000e010)

#endif
