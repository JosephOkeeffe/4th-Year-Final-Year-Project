#ifndef GAME_HPP
#define GAME_HPP
#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Globals.h"
#include "Tile.h"
#include "View.h"
#include "Textures.h"
#include "Warrior.h"
#include "Archer.h"
#include "HUD.h"
#include "ResourceManagement.h"
#include "TileTypes.h"

class Game
{
public:
    Game();
    ~Game();

    void run();

private:

    void ProcessEvents();
    void ProcessKeys(sf::Event t_event);
    void ProcessMouseDown(sf::Event t_event);
    void ProcessMouseUp(sf::Event t_event);
    void Update(sf::Time t_deltaTime);
    void Render();
    void Init();
    void Save();
    // text file
    // seperate by commas or spaces
    void Load();

    void InitTiles();

    void ManageTimer();

    sf::RenderWindow m_window;
    sf::Font m_font;
    bool m_exitGame;

    sf::View gameView;
    sf::View hudView;

    HUD hud;

    Tile** tiles;
    View view{ m_window, gameView, hudView };

    Warrior warrior;
    Archer archer;

    sf::Clock incomeTimer;
    sf::Time elapsedTime;
};

#endif