#include "as1107.h"
#include "debug.h"
#include "font.h"
#include "display.h"
#include "display_as1107.h"

void display_as1107_init(struct display *display, struct as1107 *as1107)
{
    display->as1107 = as1107;
}

void display_set_intensity(struct display *display, uint8_t intensity)
{
    as1107_set_intensity(display->as1107, intensity);
}

void display_show_text(struct display *display, const char *text)
{
    debug_put_string("display: [");
    for (int i = 0; i < DISPLAY_CHAR_COUNT; i++) {
        if (text[i] == '\0') {
            break;
        }
        debug_put_char(text[i]);
    }
    debug_put_string("]\r\n");
    font_render(display->glyphs_scratchpad, AS1107_GLYPH_COUNT, text);
    as1107_show_glyphs(display->as1107, display->glyphs_scratchpad);
}

void display_blank(struct display *display)
{
    debug_put_string("display: blank\r\n");
    as1107_blank(display->as1107);
}

void display_resume(struct display *display)
{
    debug_put_string("display: resume\r\n");
    as1107_resume(display->as1107);
}
