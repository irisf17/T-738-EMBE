#include "states.h"
#include <avr/delay.h>
#include "timer_msec.h"
#include "digital_out.h"

// class Context;
Digital_out led(5);
Timer_msec timer;


void Initialization::on_entry()
{
  // optionally do something on transition
  Serial.println("STATE: Initialization");
  led.init();
//   sei();
  _delay_ms(2000);
  timer.init(10, 0.001);
//   led.set_lo();
  Serial.println("BOOT UP");
  _delay_ms(5000);
  this->context_->transition_to(new Pre_Operational);
}


void Pre_Operational::on_entry()
{
  // optionally do something on transition
	Serial.println("STATE: Pre Operational");
	Serial.println("Led blinks at 1 Hz");
    timer.init(1000, 0.5);
    Serial.println("Ready to recieve commands");
	
}

void Pre_Operational::set()
{
  // optionally do something on transition
  this->context_->transition_to(new Operational);
}

void Pre_Operational::on_stop()
{
  // optionally do something on transition
  this->context_->transition_to(new Stop_state);
}

void Pre_Operational::on_reset()
{
  // optionally do something on transition
  Serial.println("Resetting...");
  this->context_->transition_to(new Initialization);
}

void Operational::on_entry()
{
  // optionally do something on transition
  Serial.println("STATE: Operational");
  Serial.println("Led continous");
//   led.set_hi();
  timer.init(20, 0.9);
}

void Operational::set_pre()
{
  // optionally do something on transition
  this->context_->transition_to(new Pre_Operational);
}

void Operational::on_stop()
{
  // optionally do something on transition
  this->context_->transition_to(new Stop_state);
}

void Operational::on_reset()
{
  // optionally do something on transition
  Serial.println("Resetting...");
  this->context_->transition_to(new Initialization);
}

void Stop_state::on_entry()
{
  // optionally do something on transition
  Serial.println("STATE: Stop ");
  Serial.println("LED blinks at 2 Hz");
  timer.init(500, 0.5);
}

void Stop_state::set()
{
  // optionally do something on transition
  this->context_->transition_to(new Operational);
}

void Stop_state::set_pre()
{
  // optionally do something on transition
  this->context_->transition_to(new Pre_Operational);
}
void Stop_state::on_stop()
{
  // optionally do something on transition
  Serial.println("Still in Stop State");
}

void Stop_state::on_reset()
{
  // optionally do something on transition
  Serial.println("Resetting...");
  this->context_->transition_to(new Initialization);
}

ISR(TIMER1_COMPA_vect)
{
  led.set_hi();

}

ISR(TIMER1_COMPB_vect)
{
  led.set_lo();
}