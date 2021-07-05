#pragma once

// AS1107 driver
//
// Supported:
// * Shutdown mode
// * Display test mode
// * Direct control of all segments
// * Controlling 8 glyphs
//
// Not supported:
// * Code-B or HEX decoding (data in nibble form)
// * Scan limit (only display subset of glyphs)
// * External clock
// * Blinking
// * Cascading multiple display drivers

#include <stdbool.h>
#include <stdbool.h>

#include "spi.h"

#define AS1107_GLYPH_COUNT 8
#define AS1107_INTENSITY_MAX 15

typedef struct {
    Spi *spi;
} As1107;

void as1107_init(As1107 *as1107, Spi *spi);
void as1107_set_test_mode(As1107 *as1107, bool test_mode_on);
void as1107_set_intensity(As1107 *as1107, uint8_t intensity);
void as1107_display_glyphs(As1107 *as1107, const uint8_t *glyphs);
void as1107_clear(As1107 *as1107);