#ifndef SCB_H
#define SCB_H

#include <types.h>

typedef struct {
    ro32_t cpuid;
    rw32_t icsr;
    rw32_t vtor;
    rw32_t aircr;
    rw32_t scr;
    ro32_t ccr;
} scb_hw_t;

#define SCB ((scb_hw_t *)0xe000ed00)

#endif
