#include <player.h>
#include <JumpState.h>
#include <StandState.h>

JumpState::JumpState(Player* owner)
    : State(owner), CountDown(2 + (rand() % 3))
{
    Serial.print("JUMP Constructor ... Countdown is ");
    Serial.println(CountDown);
}

void JumpState::Step()
{
    Serial.print("JUMP State... Countdown is ");
    Serial.println(CountDown-1);

    if (--CountDown <=0)
    {
        Owner->ChangeCurrentState<StandState>();
    }
}