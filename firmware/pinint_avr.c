#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "actor.h"
#include "actor_avr.h"
#include "pinint.h"
#include "pinint_avr.h"

static struct pinint *pinints[PININT_AVR_COUNT];

static inline void enable(enum pinint_avr_id id);
static inline void post_sig(struct pinint *pinint);

void pinint_system_init(void)
{
    for (int i = 0; i < (int) PININT_AVR_COUNT; i++) {
        pinints[i] = NULL;
    }
}

void pinint_acquire(struct pinint *pinint, struct actor *recipient, actor_sig rising_sig, actor_sig falling_sig)
{
    pinint->recipient = recipient;
    pinint->rising_sig = rising_sig;
    pinint->falling_sig = falling_sig;
    pinints[pinint->id] = pinint;
    enable(pinint->id);
}

ISR(INT0_vect) {
    post_sig(pinints[PININT_AVR_INT0]);
}

ISR(INT1_vect) {
    post_sig(pinints[PININT_AVR_INT1]);
}

ISR(INT2_vect) {
    post_sig(pinints[PININT_AVR_INT2]);
}

ISR(INT3_vect) {
    post_sig(pinints[PININT_AVR_INT3]);
}

ISR(INT6_vect) {
    post_sig(pinints[PININT_AVR_INT6]);
}

static inline void enable(enum pinint_avr_id id)
{
    switch (id) {
    case PININT_AVR_INT0:
        EICRA &= ~(1<<ISC01);
        EICRA |= 1<<ISC00;
        EIFR |= 1<<INTF0;
        EIMSK |= 1<<INT0;
        break;
    case PININT_AVR_INT1:
        EICRA &= ~(1<<ISC11);
        EICRA |= 1<<ISC10;
        EIFR |= 1<<INTF1;
        EIMSK |= 1<<INT1;
        break;
    case PININT_AVR_INT2:
        EICRA &= ~(1<<ISC21);
        EICRA |= 1<<ISC20;
        EIFR |= 1<<INTF2;
        EIMSK |= 1<<INT2;
        break;
    case PININT_AVR_INT3:
        EICRA &= ~(1<<ISC31);
        EICRA |= 1<<ISC30;
        EIFR |= 1<<INTF3;
        EIMSK |= 1<<INT3;
        break;
    case PININT_AVR_INT6:
        EICRB &= ~(1<<ISC61);
        EICRB |= 1<<ISC60;
        EIFR |= 1<<INTF6;
        EIMSK |= 1<<INT6;
        break;
    default:
        break;
    }
}

static inline void post_sig(struct pinint *pinint)
{
    bool state;
    switch (pinint->id) {
    case PININT_AVR_INT0:
        state = (PIND & (1<<0)) != 0;
        break;
    case PININT_AVR_INT1:
        state = (PIND & (1<<1)) != 0;
        break;
    case PININT_AVR_INT2:
        state = (PIND & (1<<2)) != 0;
        break;
    case PININT_AVR_INT3:
        state = (PIND & (1<<3)) != 0;
        break;
    case PININT_AVR_INT6:
        state = (PINE & (1<<6)) != 0;
        break;
    default:
        return;
    }
    actor_sig sig = state ? pinint->rising_sig : pinint->falling_sig;
    actor_post_from_isr(pinint->recipient, sig);
}
