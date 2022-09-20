#include <Arduino.h>
#include <avr/delay.h>
#include "digital_out.h"
#include "timer_msec.h"
#include "fifo.h"

 // ----- PART 2 -----

// initialize classes
Digital_out led(5);
Timer_msec timer;
Fifo f;

// variables
int input;

void setup()
{
	Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  led.init();
  timer.init(1000);
}

void loop()
{
	// send data only when you receive data:
	if (Serial.available() > 0)
	{
		// read the incoming byte: read the go/start command
		input = Serial.read();
    Serial.println(input-48,DEC);

    f.put(input);
  }
    if (f.is_full() == true){
      led.set_hi();
    }
    else{
      led.set_lo();
    }	
}

ISR(TIMER1_COMPA_vect)
{
  f.get();
}