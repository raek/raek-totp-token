#include <avr/io.h>

#include "pin.h"
#include "pin_avr.h"

void pin_set_dir(Pin *pin, bool output)
{
    if (output) {
        *pin->ddr_reg |= pin->bit_pattern;
    } else {
        *pin->ddr_reg &= ~(pin->bit_pattern);
    }
}

void pin_write(Pin *pin, bool state)
{
    if (state) {
        *pin->port_reg |= pin->bit_pattern;
    } else {
        *pin->port_reg &= ~(pin->bit_pattern);
    }
}

bool pin_read(Pin *pin)
{
    return (*pin->pin_reg & pin->bit_pattern) != 0;
}
