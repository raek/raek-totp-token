#include <avr/interrupt.h>
#include <stdint.h>

#include "list.h"
#include "actor_avr.h"
#include "timer.h"
#include "timer_avr.h"

static timer_instant now;
static struct list_head active_timers;

static void deactivate(struct timer *timer);
static void activate(struct timer *timer, timer_instant target, bool repeating, timer_duration interval, bool fixed_count, int count);

void timer_system_init(void)
{
    // Initialize to 10 seconds before rollover to make sure that
    // rollover is excercised regurlarly
    now = UINT32_MAX - (10UL * TIMER_FREQUENCY_HZ);
    INIT_LIST_HEAD(&active_timers);

    // Configure CTC mode
    TCNT1 = 0;
    OCR1A = F_CPU / TIMER_FREQUENCY_HZ;
    TCCR1A = (0<<WGM11) | (0<<WGM10);
    TCCR1B = (0<<WGM13) | (1<<WGM12);
    // Clear and enable interrupt
    TIFR1 = (1<<OCF1A);
    TIMSK1 = (1<<OCIE1A);
    // Start Timer/Counter (prescaler = 1)
    TCCR1B |= (0<<CS12) | (0<<CS11) | (1<<CS10);
}

void timer_init(struct timer *timer, struct actor *recipient, actor_sig sig)
{
    timer->recipient = recipient;
    timer->sig = sig;
    timer->active = false;
}

void timer_set_oneshot(struct timer *timer, timer_duration delay)
{
    cli();
    timer_instant target = now + delay;
    deactivate(timer);
    activate(timer, target, false, 0, false, 0);
    sei();
}

void timer_set_repeating(struct timer *timer, timer_duration interval)
{
    cli();
    timer_instant target = now + interval;
    deactivate(timer);
    activate(timer, target, true, interval, false, 0);
    sei();
}


void timer_set_fixed_count(struct timer *timer, timer_duration interval, int count)
{
    cli();
    timer_instant target = now + interval;
    deactivate(timer);
    if (count > 0) {
        activate(timer, target, true, interval, true, count);
    }
    sei();
}

void timer_cancel(struct timer *timer)
{
    cli();
    deactivate(timer);
    sei();
}

ISR(TIMER1_COMPA_vect)
{
    now++;
    struct timer *timer;
    struct timer *next;
    list_for_each_entry_safe(timer, next, &active_timers, list) {
        if (timer->target == now) {
            actor_post_from_isr(timer->recipient, timer->sig);
            if (timer->repeating) {
                timer->target += timer->interval;
                if (timer->fixed_count) {
                    timer->count--;
                    if (timer->count == 0) {
                        deactivate(timer);
                    }
                }
            } else {
                deactivate(timer);
            }
        }
    }
}

static void deactivate(struct timer *timer)
{
    if (timer->active) {
        list_del(&timer->list);
        timer->active = false;
    }
}

static void activate(struct timer *timer, timer_instant target, bool repeating, timer_duration interval, bool fixed_count, int count)
{
    timer->active = true;
    timer->target = target;
    timer->repeating = repeating;
    timer->interval = interval;
    timer->fixed_count = fixed_count;
    timer->count = count;
    list_add_tail(&timer->list, &active_timers);
}
