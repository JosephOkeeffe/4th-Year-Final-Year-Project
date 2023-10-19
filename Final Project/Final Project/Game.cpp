#include <iostream>
#include "Game.h"

Game::Game() :
    m_window{ sf::VideoMode{ Global::S_WIDTH, Global::S_HEIGHT, 32U }, "The Big One" },
    m_exitGame{ false },
    textures(),
    grid(m_window),
    gameView(m_window),
    warrior(textures.textureMap.find("warrior")->second, m_window)
    
{
    Init();
}
Game::~Game()
{}
void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const float fps{ 60.0f };
    sf::Time timePerFrame = sf::seconds(1.0f / fps);
    while (m_window.isOpen())
    {
        ProcessEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            ProcessEvents(); // at least 60 fps
            Update(timePerFrame); //60 fps
        }
        Render();
    }
}

void Game::ProcessEvents()
{
    sf::Event newEvent;
    while (m_window.pollEvent(newEvent))
    {
        if (sf::Event::Closed == newEvent.type)
        {
            m_exitGame = true;
        }
        if (sf::Event::KeyPressed == newEvent.type)
        {
            ProcessKeys(newEvent);
        }
        if (sf::Event::MouseButtonPressed == newEvent.type || sf::Event::MouseWheelScrolled == newEvent.type)
        {
            ProcessMouse(newEvent);
        }
    }
}
void Game::ProcessKeys(sf::Event t_event)
{
    if (sf::Keyboard::Escape == t_event.key.code){m_exitGame = true;}
   
}
void Game::ProcessMouse(sf::Event t_event)
{
   //gameView.handleInput(t_event);
}
void Game::Init()
{
    grid.Init();
}

void Game::Render()
{
    m_window.clear(sf::Color::Black);
    grid.Render();

    warrior.DrawWarrior(m_window);

    m_window.display();
}


void Game::Update(sf::Time t_deltaTime)
{
    if (m_exitGame){m_window.close();}
    gameView.MoveScreen();

    grid.Update();
    warrior.Update(m_window);
}

