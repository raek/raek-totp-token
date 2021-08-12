#pragma once

#include <stddef.h>
#include <stdint.h>

#define FONT_BLANK_GLYPH 0x00

uint8_t font_lookup(char c);
void font_render(uint8_t *out_glyphs, size_t glyph_count, const char *string);
