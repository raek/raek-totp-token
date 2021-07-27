#include "inverter.h"
#include "pin.h"

void inverter_init(struct inverter *inverter, struct pin *in_pin, struct pin *out_pin)
{
    inverter->in_pin = in_pin;
    inverter->out_pin = out_pin;
    pin_set_dir(inverter->in_pin, PIN_DIR_INPUT);
    pin_set_dir(inverter->out_pin, PIN_DIR_OUTPUT);
    inverter_run(inverter);
}

void inverter_run(struct inverter *inverter)
{
    pin_write(inverter->out_pin, !pin_read(inverter->in_pin));
}
