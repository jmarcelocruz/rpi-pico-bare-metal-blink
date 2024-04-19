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

#include <stdio.h>

#include <gpio/gpio.h>
#include <uart/uart.h>

#define LED_PIN 25 /* onboard LED on Pico */
#define BUTTON_PIN 18

int main(void) {
    uart0_init();
    gpio_init(LED_PIN);
    gpio_init(BUTTON_PIN);

    printf("*** rpi-bare-metal-blink ***\r\n");

    while (1) {
        if (gpio_get(BUTTON_PIN)) {
            gpio_put(LED_PIN, 1);
        } else {
            gpio_put(LED_PIN, 0);
        }
    }

    return 0;
}
