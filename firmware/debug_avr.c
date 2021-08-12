#include <avr/io.h>

#include "debug.h"

#define BAUD_RATE 38400UL

void debug_init(void)
{
    UBRR1 = F_CPU / 16UL / BAUD_RATE - 1;
    UCSR1A = 0;
    UCSR1B = (0<<RXEN1) | (1<<TXEN1) | (0<<UCSZ12);
    UCSR1C = ((0<<UMSEL11) | (0<<UMSEL10) |
              (0<<UPM11) | (0<<UPM10) |
              (0<<USBS1) |
              (1<<UCSZ11) | (1<<UCSZ10) |
              (0<<UCPOL1));
}

void debug_put_char(char c)
{
    UDR1 = c;
    while (!(UCSR1A & (1<<TXC1))) {
    }
    UCSR1A |= (1<<TXC1);
}
