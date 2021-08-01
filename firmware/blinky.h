#pragma once

#include "actor.h"
#include "pin.h"
#include "pinint.h"

struct blinky {
    struct actor actor;
    struct pinint *in_pinint;
    struct pin *in_pin;
    struct pin *out_pin;
};

void blinky_init(struct blinky *blinky, struct pinint *in_pinint, struct pin *in_pin, struct pin *out_pin);
void blinky_actor_dispatcher(struct actor *actor, actor_sig sig);
