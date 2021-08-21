#pragma once

#include "actor.h"
#include "pin.h"
#include "pinint.h"
#include "result.h"
#include "timer.h"

#define BLINKY_FLASH_PERIOD_MS 200
#define BLINKY_FLASH_COUNT 3

struct blinky {
    struct actor actor;
    struct pinint *button_pinint;
    struct pin *button_pin;
    struct pin *led_pin;
    struct timer flash_timer;
    bool led_state;
};

void blinky_init(struct blinky *blinky, struct pinint *button_pinint, struct pin *button_pin, struct pin *led_pin);
enum result blinky_dispatch(struct actor *actor, actor_sig sig);
