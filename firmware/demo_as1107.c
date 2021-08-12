#include <avr/io.h>
#include <util/delay.h>

#include "as1107.h"
#include "spi_bitbang.h"
#include "pin.h"
#include "pin_avr.h"

#define T 20

int main(int argc, char **argv)
{
    struct pin din = PIN_AVR_MAKE(B, 2);
    struct pin clk = PIN_AVR_MAKE(B, 1);
    struct pin csn = PIN_AVR_MAKE(D, 2);
    struct pin button = PIN_AVR_MAKE(D, 1);
    struct pin led = PIN_AVR_MAKE(D, 0);
    struct spi spi;
    spi_bitbang_init(&spi, &din, &clk, &csn);
    _delay_ms(10);
    pin_set_dir(&button, PIN_DIR_INPUT);
    pin_set_dir(&led, PIN_DIR_OUTPUT);
    pin_write(&led, false);
    struct as1107 as1107;
    as1107_init(&as1107, &spi);
    pin_write(&led, true);
    as1107_set_test_mode(&as1107, true);
    _delay_ms(500);
    as1107_set_test_mode(&as1107, false);
    _delay_ms(500);
    pin_write(&led, false);
    uint8_t glyphs[AS1107_GLYPH_COUNT];
    for (int i = 0; i < AS1107_GLYPH_COUNT; i++) {
        glyphs[i] = 0xff;
    }
    as1107_set_intensity(&as1107, 0);
    as1107_show_glyphs(&as1107, glyphs);
    for (;;) {
        as1107_resume(&as1107);
        for (int i = 0; i <= AS1107_INTENSITY_MAX; i++) {
            as1107_set_intensity(&as1107, i);
            _delay_ms(T);
        }
        for (int i = AS1107_INTENSITY_MAX; i >= 0; i--) {
            as1107_set_intensity(&as1107, i);
            _delay_ms(T);
        }
        as1107_blank(&as1107);
        _delay_ms(T);
    }
    return 0;
}
