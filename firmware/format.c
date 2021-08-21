#include <stddef.h>

#include "format.h"

void format_decimal(char *out_string, size_t width, uint32_t value, char padding)
{
    uint32_t x = value;
    int i = (int) width - 1;
    for (; i >= 0; i--) {
        out_string[i] = '0' + (x % 10);
        x /= 10;
        if (x == 0) {
            i--;
            break;
        }
    }
    for (; i >= 0; i--) {
        out_string[i] = padding;
    }
}
