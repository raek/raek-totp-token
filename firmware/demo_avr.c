#include <avr/io.h>

#include "inverter.h"
#include "pin_avr.h"

int main(int argc, char **argv)
{
    Pin in_pin = PIN_AVR_MAKE(D, 7);
    Pin out_pin = PIN_AVR_MAKE(C, 7);
    Inverter inverter;
    inverter_init(&inverter, &in_pin, &out_pin);
    for (;;) {
        inverter_run(&inverter);
    }
    return 0;
}
