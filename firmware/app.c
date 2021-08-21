#include <string.h>

#include "actor.h"
#include "app.h"
#include "display.h"
#include "timer.h"

#define ANIMATION_TICK_PERIOD 50

enum app_sig {
    SIG_ANIMATION_TICK,
};

enum app_state {
    STATE_BLANK,
    STATE_INCREASING,
    STATE_DECREASING,
};

static const uint8_t secret[20] = "12345678901234567890";

void app_init(struct app *app, struct display *display)
{
    actor_init(&app->actor, app_dispatch);
    timer_init(&app->animation_timer, &app->actor, SIG_ANIMATION_TICK);

    app->display = display;

    app->counter = 0;
    memset(app->text, ' ', DISPLAY_CHAR_COUNT);
    app->state = STATE_BLANK;
    display_blank(app->display);
    timer_set_repeating(&app->animation_timer, ANIMATION_TICK_PERIOD);
}

enum result app_dispatch(struct actor *actor, actor_sig sig)
{
    struct app *app = (struct app *) actor;
    switch (sig) {
    case SIG_ANIMATION_TICK:
        switch (app->state) {
        case STATE_BLANK:
            hotp(&app->hotp_scratchpad, secret, 20, app->counter, &app->text[1]);
            app->counter++;
            app->intensity = 0;
            display_set_intensity(app->display, app->intensity);
            display_show_text(app->display, app->text);
            app->state = STATE_INCREASING;
            break;
        case STATE_INCREASING:
            if (app->intensity == DISPLAY_INTENSITY_MAX) {
                app->state = STATE_DECREASING;
            } else {
                app->intensity++;
                display_set_intensity(app->display, app->intensity);
            }
            break;
        case STATE_DECREASING:
            if (app->intensity == 0) {
                display_blank(app->display);
                app->state = STATE_BLANK;
            } else {
                app->intensity--;
                display_set_intensity(app->display, app->intensity);
            }
            break;
        default:
            return ERROR("invalid state");
        }
        break;
    default:
        return ERROR("invalid signal");
    }
    return RESULT_OK;
}
