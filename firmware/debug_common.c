#include "debug.h"

static char debug_hex_digits[16] = "0123456789abcdef";

static void debug_to_hex(char *out_buffer, const uint8_t *data, size_t length);

void debug_put_string(const char *string)
{
    for (const char *p = string; *p != '\0'; p++) {
        debug_put_char(*p);
    }
}

void debug_dump_hex(const char *title, const uint8_t *data, size_t length)
{
    debug_put_string(title);
    debug_put_string("\r\n");
    static char row_hex[16 * 3];
    for (uint32_t row_offset = 0; row_offset < length; row_offset += 16) {
        uint8_t row_length = (length - row_offset) >= 16 ? 16 : length - row_offset;
        debug_to_hex(row_hex, &data[row_offset], row_length);
        row_hex[(row_length * 3) - 1] = '\0';
        debug_put_string(row_hex);
        debug_put_string("\r\n");
    }
}

static void debug_to_hex(char *out_buffer, const uint8_t *data, size_t length)
{
    char *p = out_buffer;
    for (size_t i = 0; i < length; i++) {
        *p++ = debug_hex_digits[(data[i] >> 4) & 0x0f];
        *p++ = debug_hex_digits[data[i] & 0x0f];
        *p++ = ' ';
    }
}
