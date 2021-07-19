#pragma once

#include <stdbool.h>

#define PIN_DIR_INPUT false
#define PIN_DIR_OUTPUT true

struct Pin;
typedef struct Pin Pin;

void pin_set_dir(Pin *pin, bool output);
void pin_write(Pin *pin, bool state);
bool pin_read(Pin *pin);
