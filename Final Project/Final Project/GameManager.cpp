#include "GameManager.h"

sf::RenderWindow* GameManager::window = nullptr;
sf::View* GameManager::gameView = nullptr;
Tile** GameManager::tiles = nullptr;

Headquarters* GameManager::headquarters;
std::vector<Buildings*> GameManager::buildings;
std::vector<Characters*> GameManager::units;
std::vector<Formation*> GameManager::formations;
std::vector<Enemy*> GameManager::enemies;
Buildings* GameManager::buildingToPlace;