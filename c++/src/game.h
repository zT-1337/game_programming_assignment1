#include <SFML/Graphics.hpp>
#include <memory>

class Game
{
  sf::RenderWindow * m_window;
  std::shared_ptr<sf::Font> m_font;
  unsigned int m_font_size;
  sf::Color * m_font_color;

public:

  Game(const std::string & config_path);
  ~Game();

  void loop();
};
