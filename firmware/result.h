#pragma once

#define ERROR(message) (result_set_error(__FILE__, __LINE__, (message)), RESULT_ERROR)

enum result {
    RESULT_ERROR = 0,
    RESULT_OK = 1,
};

struct result_error_info {
    const char *file;
    int line;
    const char *message;
};

void result_clear_error(void);
void result_set_error(const char *file, int line, const char *message);
const struct result_error_info *result_get_error(void);
