#include "game.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

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

  unsigned int width, height;
  config_file >> width >> height;

  m_window = new sf::RenderWindow(sf::VideoMode(width, height), "SFML Works");
}

Game::~Game()
{
  delete m_window;
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

    m_window->display();
  }
}