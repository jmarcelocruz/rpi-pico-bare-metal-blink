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


__attribute__((section(".boot"))) void _reset(void) {
    extern long _etext, _sdata, _edata, _sbss, _ebss;
    /* load data section from flash into sram */
    for (long *src = &_etext, *dst = &_sdata; dst < &_edata; src++, dst++) {
        *dst = *src;
    }
    /* zero out bss section */
    for (long *dst = &_sbss; dst < &_ebss; dst++) {
        *dst = 0;
    }

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
