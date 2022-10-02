#include "PI_controller.h"
#include "digital_out.h"
#include "Arduino.h"


extern Digital_out led;
extern Digital_out output_1;
extern Digital_out output_2;
extern Digital_out PWM_pin;

PI_Controller::PI_Controller(float Kp, float Ti, float integration_T, float max_output)
{
    this->Kp = Kp;
    this->Ti = Ti;
    this->integration_T = integration_T;
    this->max_output = max_output;
    sum_error = 0;
}

void PI_Controller::init(float Kp, float Ti, float integration_T, float max_output)
{
    this->Kp = Kp;
    this->Ti = Ti;
    this->integration_T = integration_T;
    this->max_output = max_output;
    sum_error = 0;
}

float PI_Controller::update(float ref, float actual)
{
    Serial.println("ref speed");
    Serial.println(ref);
    Serial.println("actual");
    Serial.println(actual);
    error = ref - actual;
    Serial.println("error");
    Serial.println(error);
    sum_error += error * integration_T;
    Serial.println("sum error");
    Serial.println(sum_error);
    Serial.println("Kp");
    Serial.println(Kp);
    Serial.println("Ti");
    Serial.println(Ti);
    output =  (Kp * (error + (sum_error/Ti)))/10;
    Serial.println("output");
    Serial.println(output);
    // if output is saturated, do not integrate
    // output is saturated if it is smaller than -1 or larger than 1
    if (output >= max_output)
    {
        output = max_output;
        sum_error -= error * integration_T;
    }
    if (output <= -max_output)
    {
        output = -max_output;
        sum_error -= error * integration_T;
    }
    return output;
}

void PI_Controller::brake()
{
    output_1.set_hi();
	output_2.set_hi();
}