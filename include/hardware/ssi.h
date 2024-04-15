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

#ifndef SSI_H
#define SSI_H

#include <types.h>

#define SSI_DFS_32_SIZE(x) (x - 1)

typedef struct {
    rw32_t ctrlr0;
    rw32_t ctrlr1;
    rw32_t ssienr;
    rw32_t mwcr;
    rw32_t ser;
    rw32_t baudr;
    rw32_t txftlr;
    rw32_t rxftlr;
    ro32_t txflr;
    ro32_t rxflr;
    ro32_t sr;
    rw32_t imr;
    ro32_t isr;
    ro32_t risr;
    ro32_t txoicr;
    ro32_t rxoicr;
    ro32_t rxuicr;
    ro32_t msticr;
    ro32_t icr;
    rw32_t dmacr;
    rw32_t dmatdlr;
    rw32_t dmardlr;
    ro32_t idr;
    ro32_t ssi_version_id;
    rw32_t dr[36];
    rw32_t rx_sample_dly;
    rw32_t spi_ctrlr0;
    rw32_t txd_drive_edge;
} ssi_hw_t;

#define SSI ((ssi_hw_t *)0x18000000)

#define SSI_CTRLR0_SPI_FRF_LSB (21)
#define SSI_CTRLR0_DFS_32_LSB (16)
#define SSI_CTRLR0_TMOD_LSB (8)

#define SSI_CTRLR1_NDF_LSB (0)

#define SSI_SPI_CTRLR0_XIP_CMD_LSB (24)
#define SSI_SPI_CTRLR0_INST_L_LSB (8)
#define SSI_SPI_CTRLR0_ADDR_L_LSB (2)
#define SSI_SPI_CTRLR0_TRANS_TYPE_LSB (0)

#define SSI_SPI_FRF_SPI (0x0)

#define SSI_TMOD_EEPROM_READ (0x3)

#endif
