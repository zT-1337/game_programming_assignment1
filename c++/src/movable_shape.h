#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

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

  unsigned int world_width;
  unsigned int world_height;
};

class MovableShape
{
  std::shared_ptr<sf::Shape> m_shape;
  std::string m_name;
  float m_speed_x;
  float m_speed_y;

  unsigned int m_world_width;
  unsigned int m_world_height;

  std::shared_ptr<sf::Color> m_color;

public:
  MovableShape(const CreateRect & rect_data);

  const sf::Shape & getShape() const;
  void update();
};
