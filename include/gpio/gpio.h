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
