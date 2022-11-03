#include "game.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <memory>

Game::Game(const std::string & config_path)
{
  auto config_file = openConfigFile(config_path);
  createWindowFromConfigFile(config_file);
  createFontFromConfigFile(config_file);
}

std::ifstream Game::openConfigFile(const std::string & config_path)
{
  std::ifstream config_file(config_path);
  if(!config_file)
  {
    std::cerr << "Unable to load file" << std::endl;
    exit(-1);
  }

  return config_file;
}

void Game::createWindowFromConfigFile(std::ifstream & config_file)
{
  std::string object_type;
  config_file >> object_type;
  checkObjectTypeIsExpected(object_type, "Window");

  unsigned int window_width, window_height;
  config_file >> window_width >> window_height;
  m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(window_width, window_height), "SFML Works");
}

void Game::createFontFromConfigFile(std::ifstream & config_file)
{
  std::string object_type; 
  config_file >> object_type;
  checkObjectTypeIsExpected(object_type, "Font");

  std::string font_filename;
  config_file >> font_filename;

  m_font = std::make_shared<sf::Font>();
  if(!m_font->loadFromFile(font_filename))
  {
    std::cerr << "Expected font file not found" << std::endl;
    exit(-1);
  }

  config_file >> m_font_size;

  uint8_t red, green, blue;
  config_file >> red >> green >> blue;
  m_font_color = std::make_shared<sf::Color>(red, green, blue);
}

void Game::checkObjectTypeIsExpected(const std::string & object_type, const std::string & expected_type)
{
  if(object_type != expected_type)
  {
    std::cerr << "Expected " << expected_type  << " object type, but got " << object_type << std::endl;
    exit(-1);
  }
}

Game::~Game()
{
}

void Game::loop()
{
  
  sf::Text text;
  text.setFont(*m_font);
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