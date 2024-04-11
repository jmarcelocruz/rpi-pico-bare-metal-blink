#ifndef PADS_BANK0_H
#define PADS_BANK0_H

#include <types.h>

typedef struct {
    rw32_t voltage_select;
    rw32_t io[30];
    rw32_t swclk;
    rw32_t swd;
} pads_bank0_hw_t;

#define PADS_BANK0_GPIO_IE_LSB  (6)
#define PADS_BANK0_GPIO_IE_BITS (1U << PADS_BANK0_GPIO_IE_LSB)
#define PADS_BANK0_GPIO_OD_LSB  (7)
#define PADS_BANK0_GPIO_OD_BITS (1U << PADS_BANK0_GPIO_OD_LSB)

#define PADS_BANK0 ((pads_bank0_hw_t *)0x4001c000)

#endif
