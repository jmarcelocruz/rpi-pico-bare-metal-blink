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

#include <hardware/clocks.h>
#include <gpio/gpio.h>
#include <hardware/io_bank0.h>
#include <hardware/uart.h>
#include <hardware/pads_bank0.h>
#include <hardware/resets.h>
#include <hardware/xosc.h>

void uart0_init(void) {
    /* deassert reset on uart0 */
    RESETS->reset &= ~(RESETS_UART0_BITS | RESETS_IO_BANK0_BITS);
    while ((RESETS->reset_done & RESETS_IO_BANK0_BITS) == 0 | (RESETS->reset_done & RESETS_UART0_BITS) == 0) {
        ;
    }
    IO_BANK0->io[0].ctrl = GPIO_FUNC_UART & IO_BANK0_GPIO_CTRL_FUNCSEL_BITS;
    IO_BANK0->io[1].ctrl = GPIO_FUNC_UART & IO_BANK0_GPIO_CTRL_FUNCSEL_BITS;
    /* set transmission format - 8 bit word, no parity, 1 stop bit */
    UART0->uartlcr_h |=
        (UART_UARTLCR_H_WLEN_8BIT << UART_UARTLCR_H_WLEN_LSB);
    /* configure baudrate for 115200 */
    UART0->uartibrd = 6U;
    UART0->uartfbrd = 33U;
    /* enable uart, rx & tx*/
    UART0->uartcr |=
        (1U << UART_UARTCR_UARTEN_LSB) |
        (1U << UART_UARTCR_RXE_LSB) |
        (1U << UART_UARTCR_TXE_LSB);
}

char uart0_read(void) {
    while ((UART0->uartfr & UART_UARTFR_RXFE_BITS) != 0) {
        ;
    }
    char c = UART0->uartdr;

    return c;
}

void uart0_write(char c) {
    while ((UART0->uartfr & UART_UARTFR_BUSY_BITS) != 0) {
        ;
    }
    UART0->uartdr = c;
}
