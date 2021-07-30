#pragma once

#include "actor.h"
#include "pin.h"
#include "pinint.h"

struct inverter {
    struct actor actor;
    struct pinint *in_pinint;
    struct pin *in_pin;
    struct pin *out_pin;
};

void inverter_init(struct inverter *inverter, struct pinint *in_pinint, struct pin *in_pin, struct pin *out_pin);
void inverter_actor_dispatcher(struct actor *actor, actor_sig sig);
