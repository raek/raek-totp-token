#include "actor.h"
#include "blinky.h"
#include "pin.h"
#include "pinint.h"
#include "result.h"
#include "timer.h"

enum blinky_sig {
    SIG_BUTTON_PRESS,
    SIG_BUTTON_RELEASE,
    SIG_FLASH_TIMER,
};

void blinky_init(struct blinky *blinky, struct pinint *button_pinint, struct pin *button_pin, struct pin *led_pin)
{
    actor_init(&blinky->actor, blinky_actor_dispatcher);
    timer_init(&blinky->flash_timer, &blinky->actor, SIG_FLASH_TIMER);
    pinint_acquire(button_pinint, &blinky->actor, SIG_BUTTON_RELEASE, SIG_BUTTON_PRESS);
    
    blinky->button_pinint = button_pinint;
    blinky->button_pin = button_pin;
    blinky->led_pin = led_pin;
    
    pin_set_dir(blinky->button_pin, PIN_DIR_INPUT);
    pin_set_dir(blinky->led_pin, PIN_DIR_OUTPUT);
    pin_write(blinky->led_pin, false);
}

enum result blinky_actor_dispatcher(struct actor *actor, actor_sig sig)
{
    struct blinky *blinky = (struct blinky *) actor;
    switch (sig) {
    case SIG_BUTTON_PRESS:
        blinky->led_state = true;
        pin_write(blinky->led_pin, blinky->led_state);
        timer_set_fixed_count(&blinky->flash_timer, BLINKY_FLASH_PERIOD_MS / 2, (BLINKY_FLASH_COUNT * 2) - 1);
        break;
    case SIG_BUTTON_RELEASE:
        break;
    case SIG_FLASH_TIMER:
        blinky->led_state = !blinky->led_state;
        pin_write(blinky->led_pin, blinky->led_state);
        break;
    default:
        return ERROR("invalid signal");
    }
    return RESULT_OK;
}
