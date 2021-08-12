#pragma once

#define DISPLAY_CHAR_COUNT 8
#define DISPLAY_INTENSITY_MAX 15

struct display;

void display_set_intensity(struct display *display, uint8_t intensity);
void display_show_text(struct display *display, const char *text);
void display_blank(struct display *display);
void display_resume(struct display *display);
