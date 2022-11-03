#include <SFML/Graphics.hpp>
#include <memory>

class Game
{
  std::shared_ptr<sf::RenderWindow> m_window;

  std::shared_ptr<sf::Font> m_font;
  unsigned int m_font_size;
  std::shared_ptr<sf::Color> m_font_color;

  std::ifstream openConfigFile(const std::string & config_path);

  void createWindowFromConfigFile(std::ifstream & config_file);
  void createFontFromConfigFile(std::ifstream & config_file);
  void checkObjectTypeIsExpected(const std::string & object_type, const std::string & expected_type);

  void createShapeObjects(std::ifstream & config_file);

public:

  Game(const std::string & config_path);
  ~Game();

  void loop();
};
