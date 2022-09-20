#include <Arduino.h>
extern void someFunction();

/*
  Simple Blink sketch
  simple-blink.cpp
  Use for PlatformIO demo
 
  From original Arduino Blink Sketch
  https://www.arduino.cc/en/Tutorial/Blink
  
  DroneBot Workshop 2021
  https://dronebotworkshop.com
*/
 
// Set LED_BUILTIN if undefined or not pin 13
#define LED_BUILTIN 13
  // void setup functions to run once
void setup()
{
  // Initialize LED pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

 // main to run repeatedly 
void loop()
{
  // Set the LED HIGH
  digitalWrite(LED_BUILTIN, HIGH);
 
  // Wait for a second
  delay(2000);
 
  // Set the LED LOW
  digitalWrite(LED_BUILTIN, LOW);
 
   // Wait for a second
  delay(2000);
  Serial.println("");
  Serial.println("New loop");
  someFunction();
}