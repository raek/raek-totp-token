#pragma once

#include <stdbool.h>

#define PIN_DIR_INPUT false
#define PIN_DIR_OUTPUT true

struct pin;

void pin_set_dir(struct pin *pin, bool output);
void pin_write(struct pin *pin, bool state);
bool pin_read(struct pin *pin);
