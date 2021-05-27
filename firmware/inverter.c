#include "inverter.h"
#include "pin.h"

void inverter_init(Inverter *inverter, Pin *in_pin, Pin *out_pin)
{
    inverter->in_pin = in_pin;
    inverter->out_pin = out_pin;
    pin_set_dir(inverter->in_pin, PIN_DIR_INPUT);
    pin_set_dir(inverter->out_pin, PIN_DIR_OUTPUT);
    inverter_run(inverter);
}

void inverter_run(Inverter *inverter)
{
    pin_write(inverter->out_pin, !pin_read(inverter->in_pin));
}
