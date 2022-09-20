#include "digital_in.h"
#include <avr/io.h>

Digital_in::Digital_in(uint8_t pin)
{
    pinMask = pin;
}

void Digital_in::init() // function to initialize the pin
{
    DDRB |= (1 << pinMask);
}

bool Digital_in::is_hi() // turning pin to high
{
    return PINB & 1<<pinMask;
}

bool Digital_in::is_lo() // Turning pin to low
{
    return !(PINB & 1<<pinMask);
}
