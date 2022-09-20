// #include <Arduino.h>
// #include <avr/delay.h>

// // Use a timer/delay to maintain the correct timing of the transition between the yellow and red states.
// // state = colors, 'r' = red, 'g'= green, 'y' = yellow
// // command go ='g', stop = 's'

// // ----- PART 2 -----
// char state = 'r';
// char command = 's'; // for incoming serial data go/stop
// int timer = 0;

// void setup()
// {
// 	Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
// }

// void loop()
// {
// 	// send data only when you receive data:
// 	if (Serial.available() > 0)
// 	{
// 		// read the incoming byte: read the go/start command
// 		command = Serial.read();

// 		// say what you got:
// 		Serial.print("I received: ");
// 		Serial.println(command);
// 	}
// 	switch (state)
// 	{
// 	case 'r':
// 		if (command == 's')
// 		{
// 			Serial.println("red light");
// 		}
// 		if (command == 'g')
// 		{
// 			Serial.println("green light ON");
// 			state = 'g';
// 		}
// 		break;
// 	case 'g':
// 		if (command == 'g')
// 		{
// 			Serial.println("green light");
// 		}
// 		if (command == 's')
// 		{
// 			// Yellow light on
// 			state = 'y';
// 			timer = 10;
// 		}
// 		break;
// 	case 'y':
// 		if (timer <= 10)
// 		{	
// 			Serial.println("Yellow light");
// 			timer--;
// 		}
// 		if (command == 's' || command == 'g')
// 		{
// 			Serial.println("Yellow light");
// 		}
// 		if (timer == 0)
// 		{
// 			state = 'r';
// 			command = 's';
// 			Serial.println("Time out");
// 		}
// 		break;
// 	default:
// 		Serial.println("ERROR");
// 	}

// 	_delay_ms(500);
// }

// -------- PART 3 -----------

#include <Arduino.h>
#include <avr/delay.h>
#include "states.h"

Context *context;
char input;

void setup()
{
	Serial.begin(9600);
	context = new Context(new Red);
}

void loop()
{
	input = Serial.read();
	if(input == 'g')
	{
		context->Go();
	}
	if(input == 's')
	{
		context->Stop();
	}

	_delay_ms(500);
}
