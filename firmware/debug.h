#pragma once

#include <stddef.h>
#include <stdint.h>

void debug_init(void);
void debug_put_char(char c);
void debug_put_string(const char *string);
void debug_dump_hex(const char *title, const uint8_t *data, size_t length);
