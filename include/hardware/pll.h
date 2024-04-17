#ifndef HW_PLL_H
#define HW_PLL_H

#include <types.h>

typedef struct {
    rw32_t cs;
    rw32_t pwr;
    rw32_t fbdiv_int;
    rw32_t prim;
} pll_hw_t;

#define PLL_SYS ((pll_hw_t *)0x40028000)

#define PLL_CS_LOCK_LSB (31)
#define PLL_CS_LOCK_BITS (1U << PLL_CS_LOCK_LSB)

#define PLL_PWR_VCOPD_LSB (5)
#define PLL_PWR_VCOPD_BITS (1U << PLL_PWR_VCOPD_LSB)
#define PLL_PWR_POSTDIVPD_LSB (3)
#define PLL_PWR_POSTDIVPD_BITS (1U << PLL_PWR_POSTDIVPD_LSB)
#define PLL_PWR_PD_LSB (0)
#define PLL_PWR_PD_BITS (1U << PLL_PWR_PD_LSB)

#define PLL_PRIM_POSTDIV1_LSB (16)
#define PLL_PRIM_POSTDIV2_LSB (12)

/* values taken from example in datasheet */
#define PLL_125MHZ_FBDIV (63)
#define PLL_125MHZ_POSTDIV1 (6)
#define PLL_125MHZ_POSTDIV2 (2)

#endif
