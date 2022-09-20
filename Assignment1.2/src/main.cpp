// ------- PART 1 ------

// #include <avr/io.h>
// #include <util/delay.h>

// int main() {
//   DDRB |= (1 << PB5); // turnin pin B5 to output

//   while(true) {
//     PORTB |= (1 << PB5); // turning pin B5 to high
//     _delay_ms(2000);
  
//     PORTB &= ~(1 << PB5); // Turning pin B5 to low
//     _delay_ms(2000);
//   }
//   return 0;
// }

// ------- PART 2 --------
// #include <util/delay.h>
// #include "digital_out.h"

// int main()
// {
//   Digital_out led(5);   // PB5 Arduino Nano built-in LED , 
//   // pin 5 in portB is the default led pin, and D13 on board 
  
//   led.init();

//   while (1)
//   {
//     _delay_ms(1000);
//     led.set_lo();
//   }

//   return 0;
// }

// ------- PART 3 --------
#include <util/delay.h>
#include "digital_in.h"
#include "digital_out.h"

int main()
{
  // initialize led
  Digital_out led(5);
  // initialize button
  Digital_in button(1);
  led.init();
  button.init();
  while(1)
  {
    _delay_ms(500);
    // if button is pressed led high
    if (button.is_hi()) {
      led.set_lo();
    }
    else {
      led.toggle();
    }
    
  }
  return 1;
}