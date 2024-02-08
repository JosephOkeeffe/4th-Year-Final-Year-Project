#include "GoldMine.h"

GoldMine::GoldMine(sf::Vector2f pos)
{
	textureRect = { currentFrameX, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("mine"), body, textureRect, 1.8);
	body.setPosition(pos);
	buildingType = GOLD_MINE;
}

void GoldMine::MouseRelease()
{
	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
	sf::Vector2i currentCell = Global::GetCurrentCell(*GameManager::GetWindow(), *GameManager::GetView());

	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		if (CheckIfSelected())
		{
			DeselectBuilding();
		}
		else
		{
			SelectBuilding();
		}
		ChangeSelectedColour();
		
		if (!CheckIfPlaced())
		{
			if (CheckIfCanBePlaced(mousePos, currentCell))
			{
				PlaceBuilding();
				GameManager::tiles[currentCell.x][currentCell.y].SetTileType(TILE_USED_UP);
			}
		}
	}
}

//bool GoldMine::CheckIfCanBePlaced()
//{
//	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
//	sf::Vector2i currentCell = Global::GetCurrentCell(*GameManager::GetWindow(), *GameManager::GetView());
//
//	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
//	{
//		if (!CheckIfPlaced() && GameManager::tiles[currentCell.x][currentCell.y].GetTileType() == RESOURCE)
//		{
//			return true;
//		}
//	}
//
//	return false;
//}

void GoldMine::Update()
{
	UpdateBuildings();


}
