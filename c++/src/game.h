#include <SFML/Graphics.hpp>

class Game
{
  sf::RenderWindow * m_window;

public:

  Game(const std::string & config_path);
  ~Game();

  void loop();
};
