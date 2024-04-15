#include <gpio/gpio.h>
#include <hardware/io_bank0.h>
#include <hardware/pads_bank0.h>
#include <hardware/resets.h>
#include <hardware/sio.h>

void gpio_init(unsigned int gpio) {
    RESETS->reset &= ~(RESETS_IO_BANK0_BITS | RESETS_PADS_BANK0_BITS);
    while ((RESETS->reset_done & RESETS_IO_BANK0_BITS) == 0 | (RESETS->reset_done & RESETS_PADS_BANK0_BITS) == 0) {
        ;
    }

    IO_BANK0->io[gpio].ctrl = GPIO_FUNC_SIO & IO_BANK0_GPIO_CTRL_FUNCSEL_BITS;
    PADS_BANK0->io[gpio] = ((1U << PADS_BANK0_GPIO_IE_LSB) & PADS_BANK0_GPIO_IE_BITS)
        | ((0U << PADS_BANK0_GPIO_OD_LSB) & PADS_BANK0_GPIO_OD_BITS);
    SIO->io_out_clr = (1U << gpio);
    SIO->io_oe = (1U << gpio);
}

void gpio_put(unsigned int gpio, int value) {
    if (value) {
        SIO->io_out_set = (1U << gpio);
    } else {
        SIO->io_out_clr = (1U << gpio);
    }
}
