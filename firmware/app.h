#pragma once

#include <stdint.h>

#include "actor.h"
#include "display.h"
#include "hotp.h"
#include "result.h"
#include "timer.h"

struct app {
    struct actor actor;
    struct display *display;
    struct timer animation_timer;
    struct hotp hotp_scratchpad;
    char text[DISPLAY_CHAR_COUNT];
    uint64_t counter;
    int state;
    uint8_t intensity;
};

void app_init(struct app *app, struct display *display);
enum result app_dispatch(struct actor *actor, actor_sig sig);
