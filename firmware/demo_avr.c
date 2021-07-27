#include <avr/io.h>
#include <util/delay.h>

#include "as1107.h"
#include "spi_bitbang.h"
#include "pin.h"
#include "pin_avr.h"

int main(int argc, char **argv)
{
    struct pin din = PIN_AVR_MAKE(B, 2);
    struct pin clk = PIN_AVR_MAKE(B, 1);
    struct pin csn = PIN_AVR_MAKE(D, 2);
    struct pin button = PIN_AVR_MAKE(D, 1);
    struct spi spi;
    spi_bitbang_init(&spi, &din, &clk, &csn);
    _delay_ms(10);
    pin_set_dir(&button, PIN_DIR_INPUT);
    struct as1107 as1107;
    as1107_init(&as1107, &spi);
    as1107_set_test_mode(&as1107, true);
    _delay_ms(500);
    as1107_set_test_mode(&as1107, false);
    _delay_ms(500);
    uint8_t glyphs[AS1107_GLYPH_COUNT];
    uint8_t glyph = 0;
    for (;;) {
        glyph <<= 1;
        if (glyph == 0) {
            glyph = 1;
        }
        for (int i = 0; i < AS1107_GLYPH_COUNT; i++) {
            glyphs[i] = glyph;
        }
        as1107_display_glyphs(&as1107, glyphs);
        _delay_ms(50);
    }
    return 0;
}
