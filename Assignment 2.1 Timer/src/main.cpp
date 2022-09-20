#include <avr/io.h> //library for pin functions
#include <avr/interrupt.h>
#include <digital_out.h> //import class
#include "timer_msec.h" //import class

Digital_out led(5);
Timer_msec timer; // =Timer_msec(); núllar klasa minnið

float duty = 0.2;

int main()
{
  led.init();
  // PART 1
  //timer.init(1000);

  // PART 2 and 3
  timer.init(10, 0.2);
  sei(); // enable interrupts

  while(1)
  {

  }
}


// --- PART 1 ---
// ISR(TIMER1_COMPA_vect)
// {
//   led.toggle();
// }

// --- PART 2 and 3 --- , 2 interupts
ISR(TIMER1_COMPA_vect)
{
  // --- PART 3 ---
  if (duty < 1.0)
  {
    duty += 0.1;
  }
  else
  {
    duty = 0.1;
  }
  timer.set(duty);
  // -------------------
  led.set_hi();
}

ISR(TIMER1_COMPB_vect)
{
  led.set_lo();
}