#include "GoldMine.h"

GoldMine::GoldMine(sf::Vector2f pos)
{
	textureRect = { currentFrameX, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("mine"), body, textureRect, 1.8);
	body.setPosition(pos);
	SetBuildingType(GOLD_MINE_BUILDING);
}

void GoldMine::MouseRelease()
{
	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
	sf::Vector2i currentCell = Global::GetCurrentCell(*GameManager::GetWindow(), *GameManager::GetView());

	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		if (!GetPlacedStatus())
		{
			if (CheckIfCanBePlaced(currentCell))
			{
				PlaceBuilding();
				GameManager::tiles[currentCell.x][currentCell.y].SetTileType(TILE_USED_UP);
			}
		}
	}
}

void GoldMine::Update()
{
	UpdateBuildings();
	deltaTime = clock.restart();

	switch (status)
	{
	case EMPTY:
		assignedWorkers.clear();
		currentWidth = 0;
		break;
	case GENERATING:
		GenerateGold();
		break;
	case DEPOSITING:
		DepositGold();
		break;
	default:
		break;
	}

	for (Characters* temp : GameManager::units)
	{
		if (temp->characterType == temp->MINER)
		{
			if (temp->body.getGlobalBounds().intersects(body.getGlobalBounds()))
			{
				if ((temp->GetCurrentState(temp->SEARCH_FOR_RESOURCE) || temp->GetCurrentState(temp->MOVING)))
				{
					static_cast<Miner*>(temp)->workingPlace = this;
					assignedWorkers.push_back(static_cast<Miner*>(temp));
					temp->SetCurrentState(temp->GATHERING);

					if (status != DEPOSITING)
					{
						status = GENERATING;
					}
				}
			}

			if (assignedWorkers.size() > 0 && temp->GetSelected())
			{
				assignedWorkers.erase(std::remove(assignedWorkers.begin(), assignedWorkers.end(), static_cast<Miner*>(temp)), assignedWorkers.end());
			}
		}
	}

	if (assignedWorkers.size() == 0)
	{
		status = EMPTY;
	}
	else
	{
		AlignWorkersPosition(assignedWorkers, textureWidth, textureHeight);
	}

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

		float increaseAmount = fillSpeed * deltaTime.asSeconds() * assignedWorkers.size();
		currentWidth = std::min(currentWidth + increaseAmount, maxWidth);
		resource.setSize(sf::Vector2f(currentWidth, barSize.y));
	}

	if (currentWidth >= maxWidth)
	{
		resourceText.setPosition(background.getPosition().x, background.getPosition().y - 50);
		status = DEPOSITING;
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

		float decreaseAmount = fillSpeed * deltaTime.asSeconds() * assignedWorkers.size();
		currentWidth = std::max(currentWidth - decreaseAmount, 0.f);
		resource.setSize(sf::Vector2f(currentWidth, barSize.y));
	}

	if (currentWidth <= 0)
	{
		resourceText.setPosition(background.getPosition().x, background.getPosition().y - 50);
		status = EMPTY;
	}
}


