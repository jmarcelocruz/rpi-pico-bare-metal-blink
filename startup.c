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
#include <hardware/resets.h>
#include <hardware/rosc.h>
#include <hardware/pll.h>
#include <hardware/scb.h>
#include <hardware/ssi.h>
#include <hardware/xosc.h>

static void clocks(void) {
    /* enable XOSC */
    XOSC->ctrl =
        (XOSC_CTRL_ENABLE_ENABLE << XOSC_CTRL_ENABLE_LSB) |
        (XOSC_CTRL_FREQ_RANGE_VALUE << XOSC_CTRL_FREQ_RANGE_LSB);
    while ((XOSC->status & XOSC_STATUS_STABLE_BITS) == 0) {
        ;
    }
    /* switch clk_ref from ROSC to XOSC */
    CLOCKS->ref.ctrl = (CLOCKS_REF_CTRL_SRC_XOSC << CLOCKS_CTRL_SRC_LSB);
    /* disable ROSC */
    ROSC->ctrl = (ROSC_CTRL_ENABLE_DISABLE << ROSC_CTRL_ENABLE_LSB);
    /* configure system PLL */
    RESETS->reset &= ~(RESETS_PLL_SYS_BITS);
    while ((RESETS->reset_done & RESETS_PLL_SYS_BITS) == 0) {
        ;
    }
    PLL_SYS->fbdiv_int = PLL_125MHZ_FBDIV;
    PLL_SYS->pwr &= ~(PLL_PWR_PD_BITS | PLL_PWR_VCOPD_BITS);
    while ((PLL_SYS->cs & PLL_CS_LOCK_BITS) == 0) {
        ;
    }
    PLL_SYS->prim =
        (PLL_125MHZ_POSTDIV1 << PLL_PRIM_POSTDIV1_LSB) |
        (PLL_125MHZ_POSTDIV2 << PLL_PRIM_POSTDIV2_LSB);
    PLL_SYS->pwr &= ~(PLL_PWR_POSTDIVPD_BITS);
    while ((PLL_SYS->cs & PLL_CS_LOCK_BITS) == 0) {
        ;
    }
    /* switch clk_sys from clk_ref to system PLL */
    CLOCKS->sys.ctrl =
        (CLOCKS_SYS_CTRL_SRC_REF << CLOCKS_CTRL_SRC_LSB) |
        (CLOCKS_SYS_CTRL_AUXSRC_PLL_SYS << CLOCKS_CTRL_AUXSRC_LSB);
    while (CLOCKS->sys.selected == 0) {
        ;
    }
    CLOCKS->sys.ctrl =
        (CLOCKS_SYS_CTRL_SRC_AUX << CLOCKS_CTRL_SRC_LSB) |
        (CLOCKS_SYS_CTRL_AUXSRC_PLL_SYS << CLOCKS_CTRL_AUXSRC_LSB);
    while (CLOCKS->sys.selected == 0) {
        ;
    }
    /* start peripheral clock and run it off of XOSC (@12MHz) */
    CLOCKS->peri.ctrl =
        (1U << CLOCKS_CTRL_ENABLE_LSB) |
        (CLOCKS_PERI_AUXSRC_XOSC << CLOCKS_CTRL_AUXSRC_LSB);
}

__attribute__((section(".boot"))) void _reset(void) {
    SSI->ssienr = 0;
    SSI->baudr = 2;
    SSI->ctrlr0 =
        (SSI_SPI_FRF_SPI << SSI_CTRLR0_SPI_FRF_LSB) |
        (SSI_TMOD_EEPROM_READ << SSI_CTRLR0_TMOD_LSB) |
        (SSI_DFS_32_SIZE(32) << SSI_CTRLR0_DFS_32_LSB);
    SSI->ctrlr1 = (0 << 0);
    SSI->spi_ctrlr0 =
        (3U << SSI_SPI_CTRLR0_XIP_CMD_LSB) |
        (6U << SSI_SPI_CTRLR0_ADDR_L_LSB) |
        (2U << SSI_SPI_CTRLR0_INST_L_LSB) |
        (0U << SSI_SPI_CTRLR0_TRANS_TYPE_LSB);
    SSI->ssienr = 1;

    clocks();

    extern long _erodata, _sdata, _edata, _sbss, _ebss;
    /* load data section from flash into sram */
    for (long *src = &_erodata, *dst = &_sdata; dst < &_edata; src++, dst++) {
        *dst = *src;
    }
    /* zero out bss section */
    for (long *dst = &_sbss; dst < &_ebss; dst++) {
        *dst = 0;
    }

    extern void (*vectors[])(void);
    SCB->vtor = (uint32_t)vectors;

    extern int main(void);
    main();

    for (;;) { ; }
}

void Default_IRQ_Handler(void) {
    for (;;) { ; }
}

__attribute__((weak, alias("Default_IRQ_Handler"))) void NMI_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void HardFault_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void SVCall_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void PendSV_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void SysTick_Handler(void);

__attribute__((weak, alias("Default_IRQ_Handler"))) void Timer0_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void Timer1_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void Timer2_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void Timer3_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void PWM_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void USBCTRL_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void XIP_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void PIO0_0_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void PIO0_1_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void PIO1_0_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void PIO1_1_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void DMA0_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void DMA1_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void IO_Bank0_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void IO_QSPI_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void SIO_Proc0_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void SIO_Proc1_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void Clocks_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void SPI0_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void SPI1_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void UART0_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void UART1_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void ADC_FIFO_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void I2C0_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void I2C1_IRQ_Handler(void);
__attribute__((weak, alias("Default_IRQ_Handler"))) void RTC_IRQ_Handler(void);

extern void _estack(void);
/* ARMv6-M Architecture Reference Manual, section B1.5.3 */
__attribute__((section(".vectors"))) void (*vectors[])(void) = {
    _estack, _reset, NMI_Handler, HardFault_Handler, 0, 0, 0, 0, 0, 0, 0,
    SVCall_Handler, 0, 0, PendSV_Handler, SysTick_Handler, Timer0_IRQ_Handler,
    Timer1_IRQ_Handler, Timer2_IRQ_Handler, Timer3_IRQ_Handler, PWM_IRQ_Handler,
    USBCTRL_Handler, XIP_IRQ_Handler, PIO0_0_IRQ_Handler, PIO0_1_IRQ_Handler,
    PIO1_0_IRQ_Handler, PIO1_1_IRQ_Handler, DMA0_IRQ_Handler, DMA1_IRQ_Handler,
    IO_Bank0_IRQ_Handler, IO_QSPI_IRQ_Handler, SIO_Proc0_IRQ_Handler,
    SIO_Proc1_IRQ_Handler, Clocks_IRQ_Handler, SPI0_IRQ_Handler, SPI1_IRQ_Handler,
    UART0_IRQ_Handler, UART1_IRQ_Handler, ADC_FIFO_IRQ_Handler, I2C0_IRQ_Handler,
    I2C1_IRQ_Handler, RTC_IRQ_Handler,
};
