#include <stdbool.h>
#include <stddef.h>

#include "result.h"

static bool error_is_set;
static struct result_error_info error_info;

void result_clear_error(void)
{
    error_is_set = false;
}

void result_set_error(const char *file, int line, const char *message)
{
    error_info.file = file;
    error_info.line = line;
    error_info.message = message;
    error_is_set = true;
}

const struct result_error_info *result_get_error(void)
{
    if (error_is_set) {
        return &error_info;
    } else {
        return NULL;
    }
}
