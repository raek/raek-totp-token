#pragma once

#include "pin.h"

struct inverter {
    struct pin *in_pin;
    struct pin *out_pin;
};

void inverter_init(struct inverter *inverter, struct pin *in_pin, struct pin *out_pin);
void inverter_run(struct inverter *inverter);
