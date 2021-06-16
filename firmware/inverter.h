#pragma once

#include "pin.h"

typedef struct {
    Pin *in_pin;
    Pin *out_pin;
} Inverter;

void inverter_init(Inverter *inverter, Pin *in_pin, Pin *out_pin);
void inverter_run(Inverter *inverter);
