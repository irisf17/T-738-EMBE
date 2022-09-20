#include <Arduino.h>
#include <player.h>

void setup()
{
  Serial.begin(9600);
}

int main()
{
  Player* player = new Player();

  for(int i=1; i<=50; i++)
  {
    player->Step();
  }
  delete player;
  return 0;
}