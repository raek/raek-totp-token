#pragma once

#include <stdint.h>

#include "pin.h"

struct Pin {
    volatile uint8_t *pin_reg;
    volatile uint8_t *port_reg;
    volatile uint8_t *ddr_reg;
    uint8_t bit_pattern;
};
