#include <util/delay.h>

#include "actor_avr.h"
#include "app.h"
#include "as1107.h"
#include "blinky.h"
#include "debug.h"
#include "display.h"
#include "display_as1107.h"
#include "i2c_avr.h"
#include "pin_avr.h"
#include "pinint_avr.h"
#include "spi_bitbang.h"
#include "timer_avr.h"

int main(int argc, char **argv)
{
    struct pinint button_pinint = PININT_AVR_MAKE(INT2);
    struct pin button_pin = PIN_AVR_MAKE(D, 2);
    struct pin led_pin = PIN_AVR_MAKE(C, 6);
    struct blinky blinky;

    struct pin din = PIN_AVR_MAKE(B, 2);
    struct pin clk = PIN_AVR_MAKE(B, 1);
    struct pin csn = PIN_AVR_MAKE(F, 0);
    struct spi spi;
    struct as1107 as1107;
    struct display display;
    struct app app;

    spi_bitbang_init(&spi, &din, &clk, &csn);
    _delay_ms(10);
    as1107_init(&as1107, &spi);
    display_as1107_init(&display, &as1107);

    as1107_set_test_mode(&as1107, true);
    _delay_ms(500);
    as1107_set_test_mode(&as1107, false);
    _delay_ms(500);

    debug_init();
    actor_system_init();
    timer_system_init();
    pinint_system_init();
    i2c_system_init();
    blinky_init(&blinky, &button_pinint, &button_pin, &led_pin);
    app_init(&app, &display);
    actor_system_loop();

    return 0;
}
