#ifndef GAME_HPP
#define GAME_HPP
#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>

#include "Globals.h"
#include "BuildingUI.h"
#include "MainMenu.h"
#include "PauseMenu.h"
//#include "Tile.h"
#include "View.h"
#include "Textures.h"
#include "Characters.h"
#include "Warrior.h"
#include "Archer.h"
#include "Worker.h"

#include "Headquarters.h"
#include "GoldMine.h"
#include "HUD.h"
#include "ResourceManagement.h"
#include "TileTypes.h"
#include "json.hpp"
//#include "GameObject.h"

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
    void ProcessKeyPress(sf::Event t_event);
    void ProcessKeyRelease(sf::Event t_event);
    void ProcessMousePress(sf::Event t_event);
    void ProcessMouseRelease(sf::Event t_event);
    void Update(sf::Time t_deltaTime);
    void Render();
    void Init();

    void SaveJSON();
    void LoadJSON();
    void LoadTilesJSON();
    void FixLoadedGrass(int type, int row, int col);
   // void ChangeThingsDependingOnTileType();

    void ManageTimers();

    void CreateWorker(sf::Vector2f pos);
    void CreateWarrior(sf::Vector2f pos);
    void CreateArcher(sf::Vector2f pos);

    void CheckBuildingCollisions();

    void SelectUnits();
    void MakeFormation();
    void AlignFormationFacingDirection();
    bool isDragging = false;
    sf::Vector2f startDragPos;
    sf::Vector2f endDragPos;
    sf::RectangleShape dragRect;

    void CreateHeadquarters(sf::Vector2f pos);
    void CreateGoldMine(sf::Vector2f pos);

    void ClearFog(sf::CircleShape radius);

    sf::RenderWindow m_window;
    sf::Font m_font;
    bool m_exitGame;

    sf::View gameView;
    sf::View hudView;

    MainMenu mainMenu;
    PauseMenu pauseMenu;

    View view{ m_window, gameView, hudView };



    bool loadGame = false;

   std::vector<Characters*> selectedUnits;
   

    sf::Vector2f basePos = {200, 200};

    // Timers
    sf::Clock incomeTimer;
    sf::Time elapsedTime;
    
};

#endif