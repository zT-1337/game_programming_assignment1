#include "movable_shape.h"

MovableShape::MovableShape(const struct CreateRect & rect_data)
  : m_speed_x(rect_data.init_speed_x)
  , m_speed_y(rect_data.init_speed_y)
{
  initRect(rect_data);
  initName(rect_data);
}

void MovableShape::initRect(const CreateRect & rect_data)
{
  m_shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(rect_data.width, rect_data.height));
  m_color = std::make_shared<sf::Color>(rect_data.red, rect_data.green, rect_data.blue);
  m_shape->setFillColor(*m_color);
  m_shape->setPosition(rect_data.init_pos_x, rect_data.init_pos_y);
}

void MovableShape::initName(const CreateRect & rect_data)
{
  m_text = std::make_shared<sf::Text>();
  m_text->setFont(rect_data.font);
  m_text->setFillColor(rect_data.font_color);
  m_text->setCharacterSize(rect_data.font_size);
  m_text->setString(rect_data.name);
  centerNameInsideShape();
}

void MovableShape::centerNameInsideShape()
{
  sf::FloatRect shape_bounding_box = m_shape->getGlobalBounds();
  sf::FloatRect text_bounding_box = m_text->getLocalBounds();
  sf::Vector2f text_pos
  (
    shape_bounding_box.left + shape_bounding_box.width / 2 - text_bounding_box.width / 2 - text_bounding_box.left,
    shape_bounding_box.top + shape_bounding_box.height / 2 - text_bounding_box.height / 2 - text_bounding_box.top
  );
  m_text->setPosition(text_pos);
}

void MovableShape::update(sf::RenderWindow & window)
{
  sf::FloatRect local_bounds = m_shape->getGlobalBounds();
  sf::Vector2u world_size = window.getSize();

  if(local_bounds.top < 0 || local_bounds.top + local_bounds.height > world_size.y)
  {
    m_speed_y *= -1;
  }

  if(local_bounds.left < 0 || local_bounds.left + local_bounds.width > world_size.x)
  {
    m_speed_x *= -1;
  }

  m_shape->move(m_speed_x, m_speed_y);
  m_text->move(m_speed_x, m_speed_y);

  window.draw(*m_shape);
  window.draw(*m_text);
}