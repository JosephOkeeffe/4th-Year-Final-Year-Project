#include "Mine.h"

Mine::Mine(sf::Vector2f pos)
{
	textureRect = { currentFrameX, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("mine"), body, textureRect, 1.8);
	body.setPosition(pos);
}

void Mine::MouseRelease()
{
	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
	sf::Vector2i currentCell = Global::GetCurrentCell(*GameManager::GetWindow(), *GameManager::GetView());

	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		DoIfSelected();
		CheckIfSelected();

		if (!CheckIfPlaced() && canBePlaced && GameManager::tiles[currentCell.x][currentCell.y].GetTileType() == RESOURCE)
		{
			PlaceBuilding();
		}
	}
}

void Mine::Update()
{
	DoIfSelected();
	UpdateDetectionCircles();
}

void Mine::DoIfSelected()
{
	if (CheckIfSelected())
	{
		body.setColor(sf::Color(128, 128, 128));
	}
	else
	{
		body.setColor(sf::Color::White);
	}
}
