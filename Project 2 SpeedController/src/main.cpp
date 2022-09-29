#include <Arduino.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <digital_out.h>
#include <digital_in.h>
#include <encoder.h>
#include <timer1.h>
#include <timer2.h>
#include <timer0.h>
#include <p_controller.h>


Digital_out output_1(5); //D13
Digital_out output_2(4); //D12
Digital_out PWM_pin(1); //D9
Digital_in encoder_input1(2); //D10
Digital_in encoder_input2(3); // DD11

encoder enc;
P_controller controller;

// timer classes
Timer1 timer1;
Timer2 timer2_pwm;
Timer0 timer0;


volatile int old_counter = 0;
volatile double time_interval = 100;
volatile double speed = 0;
volatile double max_speed = 110;

double time_constant = 100.0; // need to find this value ms
double update_rate = 10.0/time_constant;

volatile int timer1_iterate = 0;
volatile float duty_cycle = 0.0;

volatile int tau = 0;

bool check = true;
bool GO = false;

volatile double control_rate = (10.0/(time_constant/1000.0))*2.0;
volatile double set_speed = 110.0;
volatile double error = 0.0;
volatile double P = 2.0/max_speed;
volatile double control_signal = 0.0;
volatile double speed_array[100];


int main()
{
	// -------- Serial monitor -----------
	Serial.begin(9600);
	output_1.init();

	// ------- H-bridge --------
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

	// ---- for timer ----
	timer0.init(4000);
	timer1.init(time_interval);
	timer2_pwm.init(1500, duty_cycle);

	// for controller
	controller.init(P);

	sei(); // enable interrupts

	while (1)
	{
		// if(timer1_iterate % 1000 == 0)
		// {
		// 	timer1_iterate = 20;			
		Serial.print("Reference value: ");
		Serial.print(set_speed);
		Serial.println(" RPM");
		Serial.print("Speed: ");			
		Serial.print(speed);
		Serial.println(" RPM");
		Serial.print("duty cycle: ");
		Serial.print(duty_cycle);
			// Serial.print("Error: ");
			// Serial.println(error);
		// }

		// Part 2 measure maximum motor speed
		/* if (speed >= max_speed)
		{
			speed = max_speed;
			Serial.println("Maximum speed: ");
			Serial.println(speed);
		} */

		// Part 2 measure time constant
		// measure time it takes to reach 63% of max speed
		// the max speed needs to  be measured first !!!!
		/* if (speed >= 0.63*max_speed && check)
		{
			check = false;
			Serial.println("Time constant: ");
			Serial.println(timer1_count);
		} */

		//   ----- Part 3 P control -----
		// control output should be updated at a mininum rate
		// set speed to x pulses per second
		// calculate error
		// error = set_speed - speed;
		// duty_cycle = P*error;
		// timer1.set(duty_cycle);

	}
}

ISR(INT0_vect)
{
	enc.position(encoder_input1.is_hi(), encoder_input2.is_hi());
	if (enc.get_counter() > old_counter)
	{
		output_1.set_hi();
	}
	else
	{
		output_1.set_lo();
	}
	old_counter = enc.get_counter();
}

ISR(TIMER0_COMPA_vect)
{
	// Part 3 P control
	// control output should be updated at a mininum rate
	// set speed to x pulses per second
	// calculate error
	duty_cycle = controller.update(set_speed, speed);
	//duty_cycle = control_signal/max_speed;
	if (duty_cycle >= 1.0)
	{
		duty_cycle = 0.99;
	}
	else if (duty_cycle <= 0.0)
	{
		duty_cycle = 0.0;
	}
	timer2_pwm.set(duty_cycle);
}




// hinn interrupt pinninn
ISR(TIMER1_COMPA_vect)
{
	timer1_iterate++;
	// rev per min
	speed = (double)((enc.get_counter() / (time_interval * 1.0)) * 1000.0) / 1400.0 * 60.0;
	// ----- finding max speed -----
	// if (speed > max_speed)
	// {
	// 	max_speed = speed;
	// }
	// ------- finding time constant tau ------
	// if (speed_count > (0.63 * max_speed))
	// {
	// 	tau = (double)timer1_iterate * (time_interval / 1.0);
	// 	timer1_iterate = 0;
	// }
	enc.reset_counter();
	// if(tau>0)
	// {
	// 	Serial.print("tau is: ");
	// 	Serial.println(tau);
	// }
	// Serial.print("MAX speed: ");
	// Serial.print(max_speed);
	// Serial.print('\n');
}

// interrupt for timer2 pwm
ISR(TIMER2_COMPA_vect)
{
	// for PWM
	PWM_pin.set_hi();
}
// PWM
ISR(TIMER2_COMPB_vect)
{
	PWM_pin.set_lo();
}