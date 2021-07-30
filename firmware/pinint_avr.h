#pragma once

#include <avr/io.h>

#include "actor.h"

enum pinint_avr_id {
    PININT_AVR_INT0,
    PININT_AVR_INT1,
    PININT_AVR_INT2,
    PININT_AVR_INT3,
    PININT_AVR_INT6,
};

#define PININT_AVR_MAKE(pinint_id)                       \
    {                                                    \
        .id = PININT_AVR_ ## pinint_id,                  \
        .recipient = NULL,                               \
        .rising_sig = ACTOR_INVALID_SIG,                 \
        .falling_sig = ACTOR_INVALID_SIG,                \
    }

struct pinint {
    enum pinint_avr_id id;
    struct actor *recipient;
    actor_sig rising_sig;
    actor_sig falling_sig;
};
