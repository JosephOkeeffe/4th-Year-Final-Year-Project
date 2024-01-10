#ifndef GAME_HPP
#define GAME_HPP
#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Globals.h"

#include "MainMenu.h"
#include "PauseMenu.h"
#include "Tile.h"
#include "View.h"
#include "Textures.h"
#include "Warrior.h"
#include "Archer.h"
#include "HUD.h"
#include "ResourceManagement.h"
#include "TileTypes.h"
#include "json.hpp"

#define Display_Text(x) std::cout << x << "\n";

extern std::string savePath;
extern std::string loadGameDataPath;
extern std::string loadTilesDataPath;
extern bool saveGame;
extern bool loadSave;

static enum GameState
{
    MENU,
    GAME,
    PAUSED
};

class Game
{
public:
    Game();
    ~Game();

    void run();

    static GameState currentState;

private:

    void ProcessEvents();
    void ProcessKeys(sf::Event t_event);
    void ProcessMouseDown(sf::Event t_event);
    void ProcessMouseUp(sf::Event t_event);
    void Update(sf::Time t_deltaTime);
    void Render();
    void Init();

    void SaveJSON();
    void LoadJSON();
    void LoadTilesJSON();
    void FixLoadedGrass(int type, int row, int col);
    void ChangeThingsDependingOnTileType();

    void InitTiles();

    void ManageTimer();


    sf::RenderWindow m_window;
    sf::Font m_font;
    bool m_exitGame;

    sf::View gameView;
    sf::View hudView;

    MainMenu mainMenu;
    PauseMenu pauseMenu;
    HUD hud;

    Tile** tiles;
    View view{ m_window, gameView, hudView };

    Warrior warrior;
    Archer archer;

    sf::Clock incomeTimer;
    sf::Time elapsedTime;

    bool loadGame = false;

    
};

#endif