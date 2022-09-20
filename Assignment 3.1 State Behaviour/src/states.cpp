#include "states.h"

// class Context;

void Red::on_entry()
{
  // optionally do something on transition
  Serial.println("Red");
}

void Red::on_go()
{
  // optionally do something on transition
  this->context_->transition_to(new Green);
}

void Red::on_stop()
{
  // optionally do something on transition
  this->context_->transition_to(new Red);
}

// void Yellow::on_go()
// {
//   // optionally do something on transition
// }

// void Yellow::on_stop()
// {
//   // optionally do something on transition
// }

void Yellow::on_entry()
{
  // optionally do something on transition
	Serial.println("Yellow");
	delay(5000);
	this->context_->transition_to(new Red);
}

void Green::on_go()
{
  // optionally do something on transition
  this->context_->transition_to(new Green);
}

void Green::on_stop()
{
  // optionally do something on transition
  this->context_->transition_to(new Yellow);
}

void Green::on_entry()
{
  // optionally do something on transition
  Serial.println("Green");
}