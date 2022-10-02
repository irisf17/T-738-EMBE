#include "motor_driver.h"
#include "digital_out.h"
#include "timer2.h"

#include <Arduino.h>

extern float duty_cycle;
extern float speed;
extern float reference_speed;
extern Digital_out output_1;
extern Digital_out output_2;
extern Timer2 timer2_pwm;

void motor_driver(Controller& cont)
{
    duty_cycle = cont.update(reference_speed, speed);
    Serial.println("duty_cycle");
    Serial.println(duty_cycle);
    Serial.println("ref speed");
    Serial.println(reference_speed);
	// CW
	if (duty_cycle < 0)
	{
		output_1.set_hi();
		output_2.set_lo();
        duty_cycle = -duty_cycle;
	}
	else // CW
	{
		output_1.set_hi();
		output_2.set_lo();
	}
	//duty_cycle = abs(duty_cycle);
	// set the duty cycle
	timer2_pwm.set(duty_cycle);
}