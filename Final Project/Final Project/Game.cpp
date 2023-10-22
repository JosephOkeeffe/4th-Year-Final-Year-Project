#include <iostream>
#include "Game.h"

Game::Game() :
    m_window{ sf::VideoMode{ Global::S_WIDTH, Global::S_HEIGHT, 32U }, "The Big One" },
    m_exitGame{ false },
    textures(),
    gameView(m_window),
    warrior(textures.textureMap.find("warrior")->second, m_window),
    archer(textures.textureMap.find("archer")->second, m_window)
    
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
            ProcessMouseDown(newEvent);
        }
        if (sf::Event::MouseButtonReleased == newEvent.type)
        {
            ProcessMouseUp(newEvent);
        }
    }
}
void Game::ProcessKeys(sf::Event t_event)
{
    if (sf::Keyboard::Escape == t_event.key.code){m_exitGame = true;}
   
}
void Game::ProcessMouseDown(sf::Event t_event)
{
   //gameView.handleInput(t_event);

    if (sf::Mouse::Right == t_event.key.code)
    {
        sf::Vector2i currentCell = Global::GetCurrentCell(m_window);
        std::cout << "X: " << currentCell.x << "\n";
        std::cout << "Y: " << currentCell.y<< "\n";
        tiles[currentCell.x][currentCell.y].tile.setFillColor(sf::Color::Red);
    }
}
void Game::ProcessMouseUp(sf::Event t_event)
{
    if (sf::Mouse::Left == t_event.key.code)
    {
        warrior.MouseUp(m_window);
    }
}
void Game::Init()
{
    InitTiles();
}

void Game::InitTiles()
{
    for (int row = 0; row < Global::ROWS_COLUMNS; row++)
    {
        for (int col = 0; col < Global::ROWS_COLUMNS; col++)
        {
            sf::Vector2f temp = { static_cast<float>(row * Global::CELL_SIZE), static_cast<float>(col * Global::CELL_SIZE) };
            tiles[row][col].Init(temp);
        }
    }
}


void Game::Render()
{
    m_window.clear(sf::Color::Black);
    for (int row = 0; row < Global::ROWS_COLUMNS; row++)
    {
        for (int col = 0; col < Global::ROWS_COLUMNS; col++)
        {
           tiles[row][col].Render(m_window);
        }
    }

    warrior.DrawWarrior(m_window);
    archer.DrawArcher(m_window);

    m_window.display();
}


void Game::Update(sf::Time t_deltaTime)
{
    if (m_exitGame){m_window.close();}
    gameView.MoveScreen();

    warrior.Update(m_window);
    archer.Update(m_window);
}

