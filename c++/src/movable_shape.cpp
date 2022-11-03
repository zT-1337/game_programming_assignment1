#include "movable_shape.h"

MovableShape::MovableShape(const struct CreateRect & rect_data)
  : m_name(rect_data.name)
  , m_speed_x(rect_data.init_speed_x)
  , m_speed_y(rect_data.init_speed_y)
  , m_world_width(rect_data.world_width)
  , m_world_height(rect_data.world_height)
{
  m_shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(rect_data.width, rect_data.height));
  m_color = std::make_shared<sf::Color>(rect_data.red, rect_data.green, rect_data.blue);
  m_shape->setFillColor(*m_color);

  m_shape->setPosition(rect_data.init_pos_x, rect_data.init_pos_y);
}

const sf::Shape & MovableShape::getShape() const
{
  return *m_shape;
}

void MovableShape::update()
{
  sf::FloatRect local_bounds = m_shape->getGlobalBounds();

  std::cout << local_bounds.top << " " << local_bounds.left << std::endl;

  if(local_bounds.top < 0 || local_bounds.top + local_bounds.height > m_world_height)
  {
    m_speed_y *= -1;
  }

  if(local_bounds.left < 0 || local_bounds.left + local_bounds.width > m_world_width)
  {
    m_speed_x *= -1;
  }

  m_shape->move(m_speed_x, m_speed_y);
}