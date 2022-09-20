#include <player.h>
#include <StandState.h>

Player::Player()
    : CurrentState(new StandState(this))
{
    // nothing here
}

void Player::Step()
{
    CurrentState->Step();
}