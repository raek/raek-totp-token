#include "actor.h"
#include "blinky.h"
#include "pin.h"
#include "pinint.h"

enum blinky_sig {
    BLINKY_RISING,
    BLINKY_FALLING,
};

void blinky_init(struct blinky *blinky, struct pinint *in_pinint, struct pin *in_pin, struct pin *out_pin)
{
    actor_init(&blinky->actor, blinky_actor_dispatcher);
    blinky->in_pinint = in_pinint;
    blinky->in_pin = in_pin;
    blinky->out_pin = out_pin;
    pinint_acquire(blinky->in_pinint, &blinky->actor, BLINKY_RISING, BLINKY_FALLING);
    pin_set_dir(blinky->in_pin, PIN_DIR_INPUT);
    pin_set_dir(blinky->out_pin, PIN_DIR_OUTPUT);
    pin_write(blinky->out_pin, !pin_read(blinky->in_pin));
}

void blinky_actor_dispatcher(struct actor *actor, actor_sig sig)
{
    struct blinky *blinky = (struct blinky *) actor;
    if (sig == BLINKY_RISING) {
        pin_write(blinky->out_pin, false);
    } else if (sig == BLINKY_FALLING) {
        pin_write(blinky->out_pin, true);
    }
}
