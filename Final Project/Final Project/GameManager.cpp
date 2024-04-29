#include "GameManager.h"

sf::RenderWindow* GameManager::window = nullptr;
sf::View* GameManager::gameView = nullptr;
Tile** GameManager::tiles = nullptr;
ItemManager GameManager::itemManager;
Inventory GameManager::inventory;
Headquarters* GameManager::headquarters;
std::vector<Buildings*> GameManager::buildings;
std::vector<Characters*> GameManager::units;
std::vector<Characters*> GameManager::aliveUnits;
std::vector<Formation*> GameManager::formations;
std::vector<Enemy*> GameManager::enemies;
std::vector<Enemy*> GameManager::aliveEnemies;
std::vector<Suckler*> GameManager::sucklers;
std::vector<Spaceship*> GameManager::spaceships;
std::vector<Egg*> GameManager::eggs;
std::vector<EnemyBase*> GameManager::enemyBases;


Buildings* GameManager::buildingToPlace;

sf::Clock GameManager::spaceShipTimer;

int GameManager::warriorPurchaseCost = 0;
int GameManager::archerPurchaseCost = 0;
int GameManager::healerPurchaseCost = 0;
int GameManager::minerPurchaseCost = 0;
int GameManager::oilManPurchaseCost = 0;
int GameManager::hazmatManPurchaseCost = 0;

int GameManager::enemyID = 0;
int GameManager::enemyBasesLeftAlive = 0;

int GameManager::currentLevel = 0;


