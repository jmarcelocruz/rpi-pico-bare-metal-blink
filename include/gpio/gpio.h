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

#ifndef GPIO_H
#define GPIO_H

typedef enum {
    GPIO_FUNC_XIP,
    GPIO_FUNC_SPI,
    GPIO_FUNC_UART,
    GPIO_FUNC_I2C,
    GPIO_FUNC_PWM,
    GPIO_FUNC_SIO,
    GPIO_FUNC_PIO0,
    GPIO_FUNC_PIO1,
    GPIO_FUNC_CLOCK,
    GPIO_FUNC_USB,
    GPIO_FUNC_NULL = 0x1f,
} gpio_function_t;

void gpio_init(unsigned int gpio);
void gpio_put(unsigned int gpio, int value);

#endif
