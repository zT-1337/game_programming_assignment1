#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
  Game game("config.txt");
  game.loop();
  /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works");
  sf::CircleShape shape(100.0f);
  shape.setFillColor(sf::Color::Green);

  while(window.isOpen())
  {
    sf::Event event;
    while(window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();
    window.draw(shape);
    window.display();
  }*/

  return 0;
}