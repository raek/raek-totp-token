#include "actor.h"
#include "actor_avr.h"
#include "blinky.h"
#include "pin_avr.h"
#include "pinint_avr.h"

int main(int argc, char **argv)
{
    struct pinint button_pinint = PININT_AVR_MAKE(INT1);
    struct pin button_pin = PIN_AVR_MAKE(D, 1);
    struct pin led_pin = PIN_AVR_MAKE(D, 0);
    struct blinky blinky;

    pinint_system_init();
    actor_system_init();
    blinky_init(&blinky, &button_pinint, &button_pin, &led_pin);
    actor_system_loop();

    return 0;
}
