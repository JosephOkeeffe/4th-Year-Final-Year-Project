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
#include "Miner.h"
#include "OilMan.h"
#include "HazmatMan.h"
#include "Enemy.h"
#include "Suckler.h"
#include "Spaceship.h"

#include "Headquarters.h"
#include "GoldMine.h"
#include "OilExtractor.h"
#include "UraniumExtractor.h"
#include "HUD.h"
#include "TileTypes.h"
#include "json.hpp"
#include "Formation.h"
#include "EnemyBase.h"
#include "TutorialScreen.h"
#include "GameUI.h"
#include "WinScreen.h"
#include "LoseScreen.h"


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
    PAUSED,
    WIN,
    LOSE
};

class Game
{
public:
    Game();
    ~Game();

    void run();

    static GameState currentState;
    static bool isInstructionsOpen;
    static bool isControlsOpen;
    static bool isInventoryOpen;


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
    void SaveTilesJSON(nlohmann::json& data);
    void LoadJSON();
    void LoadTilesJSON();
    void FixLoadedGrass(int type, int row, int col);
   // void ChangeThingsDependingOnTileType();

    void ManageTimers();

    void CreateCharactersForLoading(sf::Vector2f pos, int type);
    void CreateEnemiesForLoading(sf::Vector2f pos, int type);
    void CreateBuildingsForLoading(sf::Vector2f pos, int type);

    void CreateWarrior(sf::Vector2f pos);
    void CreateArcher(sf::Vector2f pos);
    void CreateMiner(sf::Vector2f pos);
    void CreateOilMan(sf::Vector2f pos);
    void CreateHazmatMan(sf::Vector2f pos);

    void CreateSuckler(sf::Vector2f pos);
    void CreateBigSuckler(sf::Vector2f pos);
    void CreateSpaceship();


    void CreateHeadquarters(sf::Vector2f pos);
    void CreateGoldMine();
    void CreateGoldMineWithPos(sf::Vector2f pos);
    void CreateOilExtractor();
    void CreateOilExtractorWithPos(sf::Vector2f pos);
    void CreateUraniumExtractor();
    void CreateUraniumExtractorWithPos(sf::Vector2f pos);

    void CreateEnemyBase(sf::Vector2f pos, Item item);

    void SpawnEnemyBases();
    void SpawnSpaceships();
    void MergeEnemies();

    void UnlockEnemyBase();


    void SelectUnits();
    void MakeFormation();
    void MoveFormationWithLeader();
    void AlignFormationFacingDirection();

    void HatchEggs();

    void ClearFog(sf::CircleShape radius);

    void SetupClouds();

    void SetupTutorialPages();


    bool isDragging = false;
    sf::Vector2f startDragPos;
    sf::Vector2f endDragPos;
    sf::RectangleShape dragRect;

    sf::RectangleShape** fogTiles;

    sf::RectangleShape cloudBackground[28];
    int divider = 6;
    int totalAmountOfClouds = divider * 4 + 4;

    sf::RenderWindow m_window;
    bool m_exitGame;

    sf::View gameView;
    sf::View hudView;

    MainMenu mainMenu;
    PauseMenu pauseMenu;

    View view{ m_window, gameView, hudView };


    bool loadGame = false;

   std::vector<Characters*> selectedUnits;
   
   int spaceShipSpawnDelay = 60;

    sf::Vector2f basePos = {200, 200};

    // Timers
    sf::Clock incomeTimer;
    sf::Time elapsedTime;

    TutorialScreen tutorialScreen;    
    GameUI gameUI;
    WinScreen winScreen;
    LoseScreen loseScreen;
};

#endif