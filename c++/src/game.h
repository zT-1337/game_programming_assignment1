#include <SFML/Graphics.hpp>
#include <memory>

class Game
{
  std::shared_ptr<sf::RenderWindow> m_window;
  std::shared_ptr<sf::Font> m_font;
  unsigned int m_font_size;
  std::shared_ptr<sf::Color> m_font_color;

  void loadWindow(std::ifstream & config_file);
  void loadFont(std::ifstream & config_file);
  std::string & loadObjectType(std::ifstream & config_file);

public:

  Game(const std::string & config_path);
  ~Game();

  void loop();
};
