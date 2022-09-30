#include <Arduino.h>
#include <avr/delay.h>
#include "states.h"
#include "timer_msec.h"
#include "timer0.h"
#include "timer2.h"

#include "digital_out.h"
#include "digital_in.h"
#include "encoder.h"

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
  // --- stop --- stop the motor
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
