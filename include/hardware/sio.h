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

#ifndef SIO_H
#define SIO_H

#include <types.h>

typedef struct {
    rw32_t udividend;
    rw32_t udivisor;
    rw32_t sdividend;
    rw32_t sdivisor;
    rw32_t quotient;
    rw32_t remainder;
    ro32_t csr;
} sio_div_hw_t;

typedef struct {
    rw32_t accum[2];
    rw32_t base[3];
    ro32_t pop[3];
    ro32_t peek[3];
    rw32_t ctrl[2];
    rw32_t add[2];
    wo32_t base_1and0;
} sio_interp_hw_t;

typedef struct {
    ro32_t cpuid;
    ro32_t io_in;
    ro32_t io_hi_in;
    uint32_t _pad0; /* undefined in datasheet */
    rw32_t io_out;
    wo32_t io_out_set;
    wo32_t io_out_clr;
    wo32_t io_out_xor;
    rw32_t io_oe;
    wo32_t io_oe_set;
    wo32_t io_oe_clr;
    wo32_t io_oe_xor;
    rw32_t io_hi_out;
    wo32_t io_hi_out_set;
    wo32_t io_hi_out_clr;
    wo32_t io_hi_out_xor;
    rw32_t io_hi_oe;
    wo32_t io_hi_oe_set;
    wo32_t io_hi_oe_clr;
    wo32_t io_hi_oe_xor;
    rw32_t fifo_st;
    wo32_t fifo_wr;
    ro32_t fifo_rd;
    ro32_t spinlock_st;
    sio_div_hw_t div;
    uint32_t _pad1; /* undefined in datasheet */
    sio_interp_hw_t interp[2];
    rw32_t spinlock[32];
} sio_hw_t;

#define SIO ((sio_hw_t *)0xd0000000)

#endif
