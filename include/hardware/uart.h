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

#ifndef HW_UART_H
#define HW_UART_H

#include <types.h>

typedef struct {
    rw32_t uartdr;
    rw32_t uartrsr;
    uint32_t _pad0[4]; /* undefined in datasheet */
    ro32_t uartfr;
    uint32_t _pad1; /* undefined in datasheet */
    rw32_t uartilpr;
    rw32_t uartibrd;
    rw32_t uartfbrd;
    rw32_t uartlcr_h;
    rw32_t uartcr;
    rw32_t uartifls;
    rw32_t uartimsc;
    rw32_t uartris;
    ro32_t uartmis;
    rw32_t uarticr;
    rw32_t uartdmacr;
    uint32_t _pad2[997]; /* undefined in datasheet */
    ro32_t uartperiphid[4];
    ro32_t uartpcellid[4];
} uart_hw_t;

#define UART_UARTFR_TXFF_LSB (5)
#define UART_UARTFR_TXFF_BITS (1U << UART_UARTFR_TXFF_LSB)
#define UART_UARTFR_RXFE_LSB (4)
#define UART_UARTFR_RXFE_BITS (1U << UART_UARTFR_RXFE_LSB)
#define UART_UARTFR_BUSY_LSB (3)
#define UART_UARTFR_BUSY_BITS (1U << UART_UARTFR_BUSY_LSB)

#define UART_UARTLCR_H_WLEN_LSB (5)
#define UART_UARTLCR_H_WLEN_BITS (3U << UART_UARTLCR_H_WLEN_LSB)

#define UART_UARTLCR_H_WLEN_8BIT (0x3)

#define UART_UARTCR_RXE_LSB (9)
#define UART_UARTCR_TXE_LSB (8)
#define UART_UARTCR_UARTEN_LSB (0)

#define UART0 ((uart_hw_t *)0x40034000)

#endif
