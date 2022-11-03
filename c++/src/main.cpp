#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
  Game game("config.txt");
  game.loop();

  return 0;
}