#include "GoldMine.h"

GoldMine::GoldMine(sf::Vector2f pos)
{
	textureRect = { currentFrameX, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("mine"), body, textureRect, 1.8);
	body.setPosition(pos);
	SetBuildingType(GOLD_MINE);
}

void GoldMine::MouseRelease()
{
	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
	sf::Vector2i currentCell = Global::GetCurrentCell(*GameManager::GetWindow(), *GameManager::GetView());

	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		//if (CheckIfSelected())
		//{
		//	DeselectBuilding();
		//}
		//else
		//{
		//	SelectBuilding();
		//}
		//ChangeSelectedColour();

		/*if (isFull)
		{
			currentWidth = 0;
			isFull = false;
		}*/
		
		if (!GetPlacedStatus())
		{
			if (CheckIfCanBePlaced(mousePos, currentCell))
			{
				PlaceBuilding();
				GameManager::tiles[currentCell.x][currentCell.y].SetTileType(TILE_USED_UP);
			}
		}
	}
}

void GoldMine::Draw()
{
	GameManager::GetWindow()->draw(detectionCircle);
	GameManager::GetWindow()->draw(body);

	if (GetPlacedStatus() && isBeingUsed)
	{
		GameManager::GetWindow()->draw(resourceText);
		GameManager::GetWindow()->draw(background);
		GameManager::GetWindow()->draw(resource);
	}
}

void GoldMine::Update()
{
	UpdateBuildings();
	deltaTime = clock.restart();
}

void GoldMine::GenerateGold()
{
	background.setPosition(body.getPosition().x, body.getPosition().y - 65);
	resource.setPosition(background.getPosition());
	resource.setFillColor(sf::Color::Yellow);


	if (currentWidth < maxWidth)
	{
		resourceText.setPosition(background.getPosition().x + background.getSize().x * 0.6, background.getPosition().y - 15);
		resourceText.setString(std::to_string(static_cast<int>(currentWidth)));

		float increaseAmount = fillSpeed * deltaTime.asSeconds();
		currentWidth = std::min(currentWidth + increaseAmount, maxWidth);
		resource.setSize(sf::Vector2f(currentWidth, barSize.y));
		isEmpty = false;
	}

	if (currentWidth >= maxWidth)
	{
		resourceText.setPosition(background.getPosition().x, background.getPosition().y - 50);

		isFull = true;

	}
}

void GoldMine::DepositGold()
{
	background.setPosition(body.getPosition().x, body.getPosition().y - 65);
	resource.setPosition(background.getPosition());
	resource.setFillColor(sf::Color::Red);

	if (currentWidth > 0)
	{
		resourceText.setPosition(background.getPosition().x + background.getSize().x * 0.6, background.getPosition().y - 15);
		resourceText.setString(std::to_string(static_cast<int>(currentWidth)));

		float decreaseAmount = fillSpeed * deltaTime.asSeconds(); 
		currentWidth = std::max(currentWidth - decreaseAmount, 0.f);
		resource.setSize(sf::Vector2f(currentWidth, barSize.y));
		isFull = false;
	}

	if (currentWidth <= 0)
	{
		resourceText.setPosition(background.getPosition().x, background.getPosition().y - 50);

		isEmpty = true;
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

