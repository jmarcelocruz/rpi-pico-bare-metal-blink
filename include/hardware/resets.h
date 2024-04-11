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
