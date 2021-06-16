#include <avr/io.h>

#include "inverter.h"
#include "pin_avr.h"

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    Pin in_pin = {
        .pin_reg     = &PIND,
        .port_reg    = &PORTD,
        .ddr_reg     = &DDRD,
        .bit_pattern = 1<<7,
    };
    Pin out_pin = {
        .pin_reg     = &PINC,
        .port_reg    = &PORTC,
        .ddr_reg     = &DDRC,
        .bit_pattern = 1<<7,
    };
    Inverter inverter;
    inverter_init(&inverter, &in_pin, &out_pin);
    for (;;) {
        inverter_run(&inverter);
    }
    return 0;
}
