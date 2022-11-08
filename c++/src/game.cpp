#include "game.h"

Game::Game(const std::string & config_path)
{
  auto config_file = openConfigFile(config_path);
  createWindowFromConfigFile(config_file);
  createFontFromConfigFile(config_file);
  createShapeObjects(config_file);

  config_file.close();
}

std::ifstream Game::openConfigFile(const std::string & config_path)
{
  std::ifstream config_file(config_path);
  if(!config_file)
  {
    std::cerr << "Unable to load file" << std::endl;
    config_file.close();
    exit(-1);
  }

  return config_file;
}

void Game::createWindowFromConfigFile(std::ifstream & config_file)
{
  std::string object_type;
  config_file >> object_type;
  checkObjectTypeIsExpected(object_type, "Window", config_file);

  unsigned int window_width, window_height;
  config_file >> window_width >> window_height;
  m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(window_width, window_height), "SFML Works");
  m_window->setFramerateLimit(120);
}

void Game::createFontFromConfigFile(std::ifstream & config_file)
{
  std::string object_type; 
  config_file >> object_type;
  checkObjectTypeIsExpected(object_type, "Font", config_file);

  std::string font_filename;
  config_file >> font_filename;

  m_font = std::make_shared<sf::Font>();
  if(!m_font->loadFromFile(font_filename))
  {
    std::cerr << "Expected font file not found" << std::endl;
    config_file.close();
    exit(-1);
  }

  config_file >> m_font_size;

  int red, green, blue;
  config_file >> red >> green >> blue;
  m_font_color = std::make_shared<sf::Color>(red, green, blue);
}

void Game::checkObjectTypeIsExpected(const std::string & object_type, const std::string & expected_type, std::ifstream & config_file)
{
  if(object_type != expected_type)
  {
    std::cerr << "Expected " << expected_type  << " object type, but got " << object_type << std::endl;
    config_file.close();
    exit(-1);
  }
}

void Game::createShapeObjects(std::ifstream & config_file)
{
  std::string object_type;
  while(config_file >> object_type)
  {
    if(object_type == "Rectangle")
    {
      m_movable_shapes.push_back(createRectangle(config_file));
      continue;
    }

    if(object_type == "Circle")
    {
      m_movable_shapes.push_back(createCircle(config_file));
      continue;
    }

    std::cerr << "Unexpected object type " << object_type << std::endl;
  }
}

MovableShape Game::createRectangle(std::ifstream & config_file)
{
  std::string name;
  float init_pos_x, init_pos_y, init_speed_x, init_speed_y, width, height;
  int red, blue, green;

  config_file >> name 
              >> init_pos_x >> init_pos_y 
              >> init_speed_x >> init_speed_y 
              >> red >> green >> blue 
              >> width >> height;

  CreateRect rect = { .shape_data = 
                      {
                        name, 
                        init_pos_x, init_pos_y, 
                        init_speed_x, init_speed_y, 
                        red, green, blue,
                        .font = *m_font,
                        .font_color = *m_font_color,
                        .font_size = m_font_size
                      }, 
                      width, height,
                    };

  return MovableShape(rect);
}

MovableShape Game::createCircle(std::ifstream & config_file)
{
  std::string name;
  float init_pos_x, init_pos_y, init_speed_x, init_speed_y, radius;
  int red, blue, green;

  config_file >> name 
              >> init_pos_x >> init_pos_y 
              >> init_speed_x >> init_speed_y 
              >> red >> green >> blue 
              >> radius;

  CreateCircle circle = { .shape_data = 
                      {
                        name, 
                        init_pos_x, init_pos_y, 
                        init_speed_x, init_speed_y, 
                        red, green, blue,
                        .font = *m_font,
                        .font_color = *m_font_color,
                        .font_size = m_font_size
                      }, 
                      radius
                    };

  return MovableShape(circle);
}

Game::~Game()
{
}

void Game::loop()
{
  while(m_window->isOpen())
  {
    sf::Event event;
    while(m_window->pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
      {
        m_window->close();
      }
    }

    m_window->clear();

    for(size_t i=0; i<m_movable_shapes.size();++i)
    {
      m_movable_shapes[i].update(*m_window);
    }

    m_window->display();
  }
}