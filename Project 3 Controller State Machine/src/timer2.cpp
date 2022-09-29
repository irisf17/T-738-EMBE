#include "timer2.h"
#include <avr/io.h>
#include <avr/interrupt.h>
// TIMER 2 - 8bita, max counts = 256
// timer2: 8 bit, used for pwm
 // assign target count to compare register A (must be less than 256)
//  
Timer2::Timer2()
{
}

// First initializing timer
void Timer2::init(int period_ms)
{
    // this code sets up timer1 for a 1s @ 16Mhz Clock (mode 4)
    // counting 16000000/1024 cycles of a clock prescaled by 1024
    // Time period for one cycle = 1024/16000000 = 64microsec
    // to find the number of counts to reach 1000ms we calculate 1000ms/64*10-3 = 15625. The counter
    // needs to reach 15625-1 in order to get 1000ms.
    // therefor register OCR1A is interrupted for every period_ms with this equation = 
    // period_ms*10^-3 * 16*10^6 /1024 -1 = period_ms * 16000 / 1024 -1
    TCCR2A = 0; // set timer0 to normal operation (all bits in control registers A and B set to zero)
    TCCR2B = 0; //
    TCNT2 = 0; // initialize counter value to 0

    OCR2A = static_cast<uint8_t>(period_ms * 16000.0 / 1024 - 1); // if * 2 þá blinks on 1/2 sek on off PRESCALING timer 1A
    // assign target count to compare register A (must be less than 65536)
    TCCR2B |= (1 << WGM12); // clear the timer on compare match A
    TIMSK2 |= (1 << OCIE2A); // set interrupt on compare match A
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // set prescaler to 1024 and start the timer
}

// PART 2
void Timer2::init(int period_ms, float duty_cycle)
{
    // this code sets up timer1 for a 1s @ 16Mhz Clock (mode 4)
    // counting 16000000/1024 cycles of a clock prescaled by 1024
    TCCR2A = 0; // set timer1 to normal operation (all bits in control registers A and B set to zero)
    TCCR2B = 0; //
    TCNT2 = 0; // initialize counter value to 0 (resetting the timer value)
    OCR2A = static_cast<uint8_t>(period_ms * 16000.0/1024 - 1); 
    OCR2B = static_cast<uint8_t>(OCR2A * duty_cycle); 
    // assign target count to compare register A (must be less than 65536)
    TCCR2B |= (1 << WGM12); // clear the timer on compare match A
    TIMSK2 |= (1 << OCIE2A); // set interrupt on compare match A 
    TIMSK2|= (1 << OCIE2B); // interrupt on compare match B
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // set prescaler to 1024 and start the timer
}


// PART 3
void Timer2::set(float duty_cycle)
{
    OCR2B = static_cast<uint8_t>(duty_cycle*OCR2A);
}