#pragma once

#include <stdint.h>
#include <avr/io.h>

#define PIN_AVR_MAKE(letter, bit)                 \
    {                                             \
        .pin_reg     = &PIN ## letter,            \
        .port_reg    = &PORT ## letter,           \
        .ddr_reg     = &DDR ## letter,            \
        .bit_pattern = 1<<(bit),                  \
    }

struct pin {
    volatile uint8_t *pin_reg;
    volatile uint8_t *port_reg;
    volatile uint8_t *ddr_reg;
    uint8_t bit_pattern;
};
