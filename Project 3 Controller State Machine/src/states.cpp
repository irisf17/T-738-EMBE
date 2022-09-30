#include "states.h"
#include "timer_msec.h"
#include "timer2.h"
#include "timer0.h"
#include "digital_out.h"
#include "digital_in.h"
#include "encoder.h"

#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>

// class Context;
Digital_out led(5); // D13

// Controlling motor
Digital_out output_1(0);      // D8
Digital_out output_2(4);      // D12
Digital_out PWM_pin(1);       // D9
Digital_in encoder_input1(2); // D10
Digital_in encoder_input2(3); // D11

// motor sensor speed
encoder enc;
// P_controller controller;

// timer classes
Timer_msec timer1;   // timer1
Timer2 timer2_speed; // speed motor
Timer0 timer0;

// variables
volatile double speed = 0.0;
bool flag = 0;
int time_interval = 1000;

void Initialization::on_entry()
{
  // optionally do something on transition
  Serial.println("STATE: Initialization");
  led.init();
  // ------- H-bridge --------
  output_1.init();
  output_2.init();
  PWM_pin.init();
  // motor is stop
  output_1.set_lo();
  output_2.set_lo();
  PWM_pin.set_hi();

  // ----- For-encoder ----
  encoder_input1.init();
  encoder_input2.init();
  enc.init(encoder_input1.is_hi());

  // use if encoder is connected to interrupt pins
  enc.init_interrupt(); // nota ef thad a ad nota interrupts!! INT0 is activated

  _delay_ms(1000);

  // ---- for timer ----
  // timer0.init(4000); fyrir p_controller
  // timer2_speed.init(time_interval);
  // timer0.init(1000);
  // LED OFF
  timer1.init(10, 0.001);

  // for controller
  // controller.init(P);

  Serial.println("BOOT UP");
  sei();
  _delay_ms(1000);
  this->context_->transition_to(new Pre_Operational);
}

void Pre_Operational::on_entry()
{
  // optionally do something on transition
  Serial.println("STATE: Pre Operational");
  // stop motor
  output_1.set_lo();
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
  flag = 1;
  // optionally do something on transition
  Serial.println("STATE: Operational");
  Serial.println("Led continous");
  Serial.println("Start MOTOR");
  // Counter clockwise rotation
  output_1.set_hi();
  // output_2.set_lo();
  // PWM_pin.set_hi();

  // LED continous ON
  led.set_hi();
  // To find speed 
// time_interval above = 1000ms
  timer1.init(time_interval);
}

void Operational::set_pre()
{
  flag = 0;
  // optionally do something on transition
  this->context_->transition_to(new Pre_Operational);
}

void Operational::on_stop()
{
  flag = 0;
  // optionally do something on transition
  this->context_->transition_to(new Stop_state);
}

void Operational::on_reset()
{
  flag = 0;
  // optionally do something on transition
  Serial.println("Resetting...");
  this->context_->transition_to(new Initialization);
}

void Stop_state::on_entry()
{
  // optionally do something on transition
  Serial.println("STATE: Stop ");
  // stop motor
  output_1.set_lo();
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


// counting pulses
ISR(INT0_vect)
{
	enc.position(encoder_input1.is_hi(), encoder_input2.is_hi());
}


ISR(TIMER1_COMPA_vect)
{
  led.set_hi();
}

ISR(TIMER1_COMPB_vect)
{
  if (flag)
  {
    speed = (double)((enc.get_counter() / (time_interval * 1.0)) * 1000.0) / 1400.0 * 60.0;
    
    Serial.print("Speed of motor is: ");
    Serial.println(speed);
    enc.reset_counter();
  }
  else
  {
    led.set_lo();
  }
}

// interrupt for timer2 speed
ISR(TIMER2_COMPA_vect)
{

}
// PWM
ISR(TIMER2_COMPB_vect)
{
  // PWM_pin.set_lo();
}