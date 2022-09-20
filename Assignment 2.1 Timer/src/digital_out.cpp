#include "digital_out.h"
#include <avr/io.h>

Digital_out::Digital_out(uint8_t pin)
{
    pinMask = pin;
}

void Digital_out::init() // function to initialize the pin
{
    DDRB |= (1 << pinMask);
}

void Digital_out::set_hi() // turning pin to high
{
    PORTB |= (1 << pinMask);
}

void Digital_out::set_lo() // Turning pin to low
{
    PORTB &= ~(1 << pinMask);
}

void Digital_out::toggle() // toggle pins
{
    PORTB ^= (1 << pinMask);
}

