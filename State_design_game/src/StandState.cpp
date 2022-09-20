#include <player.h>
#include <JumpState.h>
#include <StandState.h>



void setup()
{
    Serial.begin(9600);
}

StandState::StandState(Player* owner)
    : State(owner), CountDown(5 + (rand() % 6))
{
    Serial.print("STAND Constructor ... Countdown is ");
    Serial.println(CountDown);
}

void StandState::Step()
{
    Serial.print("STAND State... Countdown is ");
    Serial.print(CountDown-1);

    if (--CountDown <=0)
    {
        Owner->ChangeCurrentState<JumpState>();
    }
}
