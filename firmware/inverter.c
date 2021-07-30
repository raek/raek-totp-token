#include "actor.h"
#include "inverter.h"
#include "pin.h"
#include "pinint.h"

enum inverter_sig {
    INVERTER_RISING,
    INVERTER_FALLING,
};

void inverter_init(struct inverter *inverter, struct pinint *in_pinint, struct pin *in_pin, struct pin *out_pin)
{
    actor_init(&inverter->actor, inverter_actor_dispatcher);
    inverter->in_pinint = in_pinint;
    inverter->in_pin = in_pin;
    inverter->out_pin = out_pin;
    pinint_acquire(inverter->in_pinint, &inverter->actor, INVERTER_RISING, INVERTER_FALLING);
    pin_set_dir(inverter->in_pin, PIN_DIR_INPUT);
    pin_set_dir(inverter->out_pin, PIN_DIR_OUTPUT);
    pin_write(inverter->out_pin, !pin_read(inverter->in_pin));
}

void inverter_actor_dispatcher(struct actor *actor, actor_sig sig)
{
    struct inverter *inverter = (struct inverter *) actor;
    if (sig == INVERTER_RISING) {
        pin_write(inverter->out_pin, false);
    } else if (sig == INVERTER_FALLING) {
        pin_write(inverter->out_pin, true);
    }
}
