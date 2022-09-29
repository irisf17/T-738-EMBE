#include "states.h"
#include <avr/delay.h>
#include "timer_msec.h"
#include "digital_out.h"

// class Context;
Digital_out led(5); //D13


// Controlling motor
Digital_out output_1(0); //D8
Digital_out output_2(4); //D12
Digital_out PWM_pin(1); //D9
Digital_in encoder_input1(2); //D10
Digital_in encoder_input2(3); // DD11

encoder enc;
// P_controller controller;

// timer classes
Timer_msec timer1; //timer1 for led
Timer2 timer2_pwm;
// Timer0 timer0;


void Initialization::on_entry()
{
  // optionally do something on transition
  Serial.println("STATE: Initialization");
  led.init();
  	// ------- H-bridge --------
  output_1.init();
	output_2.init();
	output_1.set_hi();
	output_2.set_lo();
	enc.init(encoder_input1.is_hi());

  // ----- For-encoder ----
	encoder_input1.init();
	encoder_input2.init();
	enc.init(encoder_input1.is_hi());
	// use if encoder is connected to interrupt pins
	enc.init_interrupt(); // nota ef thad a ad nota interrupts!!

    _delay_ms(2000);

  // ---- for timer ----
	timer0.init(4000);
	timer2_pwm.init(1500, duty_cycle);

	// for controller
	// controller.init(P);

  timer1.init(10, 0.001);
  Serial.println("BOOT UP");
  _delay_ms(3000);
  this->context_->transition_to(new Pre_Operational);

}


void Pre_Operational::on_entry()
{
  // optionally do something on transition
	Serial.println("STATE: Pre Operational");
	Serial.println("Led blinks at 1 Hz");
  timer1.init(1000, 0.5);
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
  timer1.init(20, 0.9);
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
  timer1.init(500, 0.5);
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