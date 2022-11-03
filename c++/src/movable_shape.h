#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <cmath>

struct CreateMovableShape
{
  std::string name;

  float init_pos_x;
  float init_pos_y;

  float init_speed_x;
  float init_speed_y;

  int red;
  int green;
  int blue;

  sf::Font & font;
  sf::Color & font_color;
  unsigned int font_size;
};

struct CreateCircle
{
  CreateMovableShape shape_data;
  float radius;
};

struct CreateRect
{
  CreateMovableShape shape_data;
  float width;
  float height;
};

class MovableShape
{
  std::shared_ptr<sf::Shape> m_shape;

  float m_speed_x;
  float m_speed_y;

  std::shared_ptr<sf::Color> m_color;
  std::shared_ptr<sf::Text> m_text;

  void initColor(const CreateMovableShape & shape_data);
  void initRect(const CreateRect & rect_data);
  void initCircle(const CreateCircle & circle_data);
  void initName(const CreateMovableShape & shape_data);
  void centerNameInsideShape();

public:
  MovableShape(const CreateRect & rect_data);
  MovableShape(const CreateCircle & circle_data);

  void update(sf::RenderWindow & window);
};
