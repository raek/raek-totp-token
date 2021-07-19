#pragma once

#include <stdbool.h>

// TODO: avoid having this header file know about this
#ifdef CFFI
#define API_FN extern "Python+C"
#else
#define API_FN
#endif

#define PIN_DIR_INPUT false
#define PIN_DIR_OUTPUT true

struct Pin;
typedef struct Pin Pin;

API_FN void pin_set_dir(Pin *pin, bool output);
API_FN void pin_write(Pin *pin, bool state);
API_FN bool pin_read(Pin *pin);
