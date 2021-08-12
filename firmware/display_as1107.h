#pragma once

#include "display.h"
#include "as1107.h"

struct display {
    struct as1107 *as1107;
    uint8_t glyphs_scratchpad[AS1107_GLYPH_COUNT];
};

void display_as1107_init(struct display *display, struct as1107 *as1107);
