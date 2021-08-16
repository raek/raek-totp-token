#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "debug.h"
#include "halt.h"
#include "result.h"

void halt(void)
{
    const struct result_error_info *error_info = result_get_error();
    if (error_info == NULL) {
        debug_put_string("halted.\r\n");
    } else {
        debug_put_string("unhandled error: ");
        debug_put_string(error_info->file);
        // TODO: print line number
        debug_put_string(": ");
        debug_put_string(error_info->message);
        debug_put_string("\r\n");
    }
    cli();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    for (;;) {
    }
}
