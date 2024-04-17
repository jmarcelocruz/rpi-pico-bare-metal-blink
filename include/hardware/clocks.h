#ifndef HW_CLOCKS_H
#define HW_CLOCKS_H

#include <types.h>

typedef struct {
    rw32_t ctrl;
    rw32_t div;
    ro32_t selected;
} clocks_clk_hw_t;

typedef struct {
    rw32_t ref_khz;
    rw32_t min_khz;
    rw32_t max_khz;
    rw32_t delay;
    rw32_t interval;
    rw32_t src;
    ro32_t status;
    ro32_t result;
} clocks_fc_hw_t;

typedef struct {
    clocks_clk_hw_t gpout[4];
    clocks_clk_hw_t ref;
    clocks_clk_hw_t sys;
    clocks_clk_hw_t peri;
    clocks_clk_hw_t usb;
    clocks_clk_hw_t adc;
    clocks_clk_hw_t rtc;
    rw32_t sys_resus_ctrl;
    ro32_t sys_resus_status;
    clocks_fc_hw_t fc0;
    rw32_t wake_enable[2];
    rw32_t sleep_enable[2];
    ro32_t enabled[2];
    ro32_t intr;
    rw32_t inte;
    rw32_t intf;
    ro32_t ints;
} clocks_hw_t;

#define CLOCKS_CTRL_AUXSRC_LSB (5)
#define CLOCKS_CTRL_SRC_LSB (0)

#define CLOCKS_REF_CTRL_SRC_XOSC (0x2)

#define CLOCKS_SYS_CTRL_AUXSRC_PLL_SYS (0x0)
#define CLOCKS_SYS_CTRL_SRC_REF (0x0)
#define CLOCKS_SYS_CTRL_SRC_AUX (0x1)

#define CLOCKS ((clocks_hw_t *)0x40008000)

#endif
