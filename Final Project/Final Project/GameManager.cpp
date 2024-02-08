#include "GameManager.h"

sf::RenderWindow* GameManager::window = nullptr;
sf::View* GameManager::gameView = nullptr;
Tile** GameManager::tiles = nullptr;

std::vector<Buildings*> GameManager::buildings;
std::vector<Characters*> GameManager::units;
Buildings* GameManager::buildingToPlace;