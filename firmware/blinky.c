#include "actor.h"
#include "blinky.h"
#include "pin.h"
#include "pinint.h"

enum blinky_sig {
    SIG_BUTTON_PRESS,
    SIG_BUTTON_RELEASE,
};

void blinky_init(struct blinky *blinky, struct pinint *button_pinint, struct pin *button_pin, struct pin *led_pin)
{
    actor_init(&blinky->actor, blinky_actor_dispatcher);
    blinky->button_pinint = button_pinint;
    blinky->button_pin = button_pin;
    blinky->led_pin = led_pin;
    pinint_acquire(blinky->button_pinint, &blinky->actor, SIG_BUTTON_RELEASE, SIG_BUTTON_PRESS);
    pin_set_dir(blinky->button_pin, PIN_DIR_INPUT);
    pin_set_dir(blinky->led_pin, PIN_DIR_OUTPUT);
    pin_write(blinky->led_pin, !pin_read(blinky->button_pin));
}

void blinky_actor_dispatcher(struct actor *actor, actor_sig sig)
{
    struct blinky *blinky = (struct blinky *) actor;
    switch (sig) {
    case SIG_BUTTON_PRESS:
        pin_write(blinky->led_pin, true);
        break;
    case SIG_BUTTON_RELEASE:
        pin_write(blinky->led_pin, false);
        break;
    default:
        break;
    }
}
