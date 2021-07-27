#pragma once

#include <stdbool.h>
#include <stdint.h>

// Time instant as seconds since the Unix epoch.
// First valid value (0):     1970-01-01 00:00:00
// Last valid value (2^32-1): 2106-02-07 06:28:15
typedef uint32_t unix_time;

bool datetime_is_valid(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
bool datetime_to_unix_time(unix_time *out_unix_time, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
