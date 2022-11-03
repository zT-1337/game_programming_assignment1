#include <SFML/Graphics.hpp>
#include <memory>

struct CreateRect
{
  std::string name;

  float init_pos_x;
  float init_pos_y;

  float init_speed_x;
  float init_speed_y;

  int red;
  int green;
  int blue;

  float width;
  float height;

  sf::Font & font;
  sf::Color & font_color;
  unsigned int font_size;
};

class MovableShape
{
  std::shared_ptr<sf::Shape> m_shape;

  float m_speed_x;
  float m_speed_y;

  std::shared_ptr<sf::Color> m_color;
  std::shared_ptr<sf::Text> m_text;

public:
  MovableShape(const CreateRect & rect_data);

  void update(sf::RenderWindow & window);
};
