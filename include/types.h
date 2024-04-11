#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef volatile uint32_t rw32_t;
typedef volatile uint32_t wo32_t; /* write-only can't actually be enforced by the type system */
typedef const volatile uint32_t ro32_t;

#endif
