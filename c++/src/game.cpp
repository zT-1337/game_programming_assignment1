#include "game.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <memory>

Game::Game(const std::string & config_path)
{
  std::ifstream config_file(config_path);
  if(!config_file)
  {
    std::cerr << "Unable to load file" << std::endl;
    exit(-1);
  }

  std::string object_type;
  config_file >> object_type;
  if(object_type != "Window")
  {
    std::cerr << "Expected Window object type at the beginning" << std::endl;
    exit(-1);
  }

  unsigned int window_width, window_height;
  config_file >> window_width >> window_height;
  m_window = new sf::RenderWindow(sf::VideoMode(window_width, window_height), "SFML Works");

  config_file >> object_type;
  if(object_type != "Font")
  {
    std::cerr << "Expected Font object type at the beginning" << std::endl;
    exit(-1);
  }

  std::string font_filename;
  config_file >> font_filename;
  sf::Font font;
  m_font = std::make_shared<sf::Font>(font);
  if(!m_font->loadFromFile(font_filename))
  {
    std::cerr << "Failed to load font" << std::endl;
    exit(-1);
  }

  config_file >> m_font_size;
  uint8_t red, blue, green;
  config_file >> red >> blue >> green;
  m_font_color = new sf::Color(red, blue, green);
}

Game::~Game()
{
  delete m_window;
  //delete m_font;
  delete m_font_color;
}

void Game::loop()
{
  sf::Text text;
  //text.setFont(*m_font);
  std::cout << m_font;
  text.setString("Sample Text");
  text.setCharacterSize(m_font_size);
  text.setFillColor(*m_font_color);

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
    m_window->draw(text);
    m_window->display();
  }
}