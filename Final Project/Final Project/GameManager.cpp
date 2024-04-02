#include "GameManager.h"

sf::RenderWindow* GameManager::window = nullptr;
sf::View* GameManager::gameView = nullptr;
Tile** GameManager::tiles = nullptr;

Headquarters* GameManager::headquarters;
std::vector<Buildings*> GameManager::buildings;
std::vector<Characters*> GameManager::units;
std::vector<Characters*> GameManager::aliveUnits;
std::vector<Formation*> GameManager::formations;
std::vector<Enemy*> GameManager::enemies;
std::vector<Enemy*> GameManager::aliveEnemies;
std::vector<Suckler*> GameManager::sucklers;
Buildings* GameManager::buildingToPlace;

int GameManager::enemyID = 0;
