#include <Arduino.h>
#include <avr/delay.h>
#include "states.h"
#include "timer_msec.h"
#include "digital_out.h"

Context *context;
char input;
// timer_msec timer;
// Digital_out led(5);

void setup()
{
	Serial.begin(9600);
	context = new Context(new Initialization);

  // // wait for 5 seconds, autonomus transition
  // _delay_ms(5000);
  // Serial.println("BOOT UP");
  // context = new Context(new Pre_Operational);

  // Serial.println("Ready to recieve commands");
}

void loop()
{

  input = Serial.read();
  // --- set() ---
	if(input == 'g')
	{
		context->Trigger_state();
	}
  // --- pre_set() ---
	if(input == 'p')
	{
		context->Set_pre();
	}
  // --- stop ---
	if(input == 's')
	{
		context->Stop();
	}
  // --- reset() ---
  if(input == 'r')
	{
		context->Reset();
	}

	_delay_ms(500);
}

// ISR(TIMER1_COMPA_vect)
// {
//   led.set_hi();
// }

// ISR(TIMER1_COMPB_vect)
// {
//   led.set_lo();
// }