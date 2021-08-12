#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "actor.h"
#ifndef CFFI
#include "list.h"
#endif

#define TIMER_FREQUENCY_HZ 1000

// Time datatypes for points in time (instant) and a dinstances in time (duration)
// Unit: milliseconds
// Largest value (2^32): 49.7 days
// Smallest value   (1):  1.0 ms
typedef uint32_t timer_instant;
typedef uint32_t timer_duration;

struct timer {
#ifndef CFFI
    struct list_head list;
#endif
    struct actor *recipient;
    actor_sig sig;
    bool active;
    timer_instant target;
    bool repeating;
    timer_duration interval;
    bool fixed_count;
    int count;
};

void timer_init(struct timer *timer, struct actor *recipient, actor_sig sig);
void timer_set_oneshot(struct timer *timer, timer_duration delay);
void timer_set_repeating(struct timer *timer, timer_duration interval);
void timer_set_fixed_count(struct timer *timer, timer_duration interval, int count);
void timer_cancel(struct timer *timer);
