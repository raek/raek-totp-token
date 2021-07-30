#include <avr/io.h>
#include <avr/interrupt.h>

#include "actor.h"
#include "pinint.h"
#include "pinint_avr.h"

void pinint_acquire(struct pinint *pinint, struct actor *recipient, actor_sig rising_sig, actor_sig falling_sig)
{
    pinint->recipient = recipient;
    pinint->rising_sig = rising_sig;
    pinint->falling_sig = falling_sig;
    switch (pinint->id) {
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
    }
}
