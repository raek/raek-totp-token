#pragma once

#include <stddef.h>
#include <stdint.h>

#include "result.h"

enum result i2c_read(uint8_t addr, uint8_t *data, size_t length);
enum result i2c_write(uint8_t addr, uint8_t *data, size_t length);
