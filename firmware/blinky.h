#pragma once

#include "actor.h"
#include "pin.h"
#include "pinint.h"

struct blinky {
    struct actor actor;
    struct pinint *button_pinint;
    struct pin *button_pin;
    struct pin *led_pin;
};

void blinky_init(struct blinky *blinky, struct pinint *button_pinint, struct pin *button_pin, struct pin *led_pin);
void blinky_actor_dispatcher(struct actor *actor, actor_sig sig);
