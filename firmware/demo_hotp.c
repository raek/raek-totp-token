#include <stddef.h>
#include <string.h>

#include <avr/io.h>
#include <util/delay.h>

#include "as1107.h"
#include "display.h"
#include "display_as1107.h"
#include "spi_bitbang.h"
#include "pin.h"
#include "pin_avr.h"
#include "hotp.h"

#define T 50

int main(int argc, char **argv)
{
    struct pin din = PIN_AVR_MAKE(B, 2);
    struct pin clk = PIN_AVR_MAKE(B, 1);
    struct pin csn = PIN_AVR_MAKE(D, 2);
    struct pin button = PIN_AVR_MAKE(D, 1);
    struct pin led = PIN_AVR_MAKE(D, 0);
    struct spi spi;
    struct as1107 as1107;
    struct display display;
    struct hotp hotp_scratchpad;
    char text[DISPLAY_CHAR_COUNT];
    uint64_t counter = 0;
    const uint8_t secret[20] = "12345678901234567890";

    pin_set_dir(&button, PIN_DIR_INPUT);
    pin_set_dir(&led, PIN_DIR_OUTPUT);
    pin_write(&led, false);
    
    spi_bitbang_init(&spi, &din, &clk, &csn);
    _delay_ms(10);
    as1107_init(&as1107, &spi);
    display_as1107_init(&display, &as1107);
    display_set_intensity(&display, 0);

    memset(text, ' ', DISPLAY_CHAR_COUNT);
    
    pin_write(&led, true);
    as1107_set_test_mode(&as1107, true);
    _delay_ms(500);
    as1107_set_test_mode(&as1107, false);
    _delay_ms(500);
    pin_write(&led, false);

    for (;;) {
        hotp(&hotp_scratchpad, secret, 20, counter, &text[1]);
        counter++;
        display_show_text(&display, text);
        for (int i = 0; i <= DISPLAY_INTENSITY_MAX; i++) {
            display_set_intensity(&display, i);
            _delay_ms(T);
        }
        for (int i = DISPLAY_INTENSITY_MAX; i >= 0; i--) {
            display_set_intensity(&display, i);
            _delay_ms(T);
        }
        display_blank(&display);
        _delay_ms(T);
    }
    return 0;
}
