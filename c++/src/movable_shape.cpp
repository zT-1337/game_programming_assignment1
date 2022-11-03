#include "movable_shape.h"
#include <SFML/Graphics.hpp>
#include <memory>

MovableShape::MovableShape(const struct CreateRect & rect_data)
{
  m_shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(rect_data.width, rect_data.height));
  m_color = std::make_shared<sf::Color>(rect_data.red, rect_data.green, rect_data.blue);
  m_shape->setFillColor(*m_color);
}

const sf::Shape & MovableShape::getShape()
{
  return *m_shape;
}