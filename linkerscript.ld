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

ENTRY(_reset)

MEMORY {
    /* from RP2040 datasheet, section 2.8.1 - first 256 bytes of flash are loaded
     * and checksum'd before continuing boot */
    boot    (rx)  : ORIGIN = 0x10000000, LENGTH = 256
    /* Official Pi Pico board has 2MB of flash */
    flash   (rx)  : ORIGIN = 0x10000100, LENGTH = 2048k - LENGTH(boot)
    sram    (rwx) : ORIGIN = 0x20000000, LENGTH = 264k
}

_sflash = ORIGIN(flash);
_estack = ORIGIN(sram) + LENGTH(sram);

SECTIONS {
    .boot : ALIGN(4) {
        *(.boot)
        /* from RP2040 datasheet, section 2.8.1.3.1 - last 4 bytes of the 256 loaded
         * are a CRC32 checksum of the first 252 */
        . = 256 - 4;        /* set location counter at start of CRC32 checksum */
        LONG(0xbeefbeef)    /* insert placeholder value for checksum */
    } > boot
    .text : ALIGN(4) {
        _stext = .;
        *(.vectors)
        *(.text)
        . = ALIGN(4);
        _etext = .;
    } > flash
    .data : ALIGN(4) {
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    } > sram AT > flash
    .bss : ALIGN(4) {
        _sbss = .;
        *(.bss)
        . = ALIGN(4);
        _ebss = .;
    } > sram
}
