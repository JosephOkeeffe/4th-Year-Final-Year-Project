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

void GoldMine::Draw()
{
	GameManager::GetWindow()->draw(detectionCircle);
	GameManager::GetWindow()->draw(body);

	if (GetPlacedStatus() && status != EMPTY)
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

	switch (status)
	{
	case GoldMine::EMPTY:
		assignedMiners.clear();
		currentWidth = 0;
		break;
	case GoldMine::GENERATE_GOLD:
		GenerateGold();
		break;
	case GoldMine::DEPOSIT_GOLD:
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
					static_cast<Worker*>(temp)->workingPlace = this;
					assignedMiners.push_back(static_cast<Worker*>(temp));
					temp->SetCurrentState(temp->GATHERING);

					if (status != DEPOSIT_GOLD)
					{
						status = GENERATE_GOLD;
					}
				}
			}

			if (assignedMiners.size() > 1 && temp->GetSelected())
			{
				assignedMiners.erase(std::remove(assignedMiners.begin(), assignedMiners.end(), static_cast<Worker*>(temp)), assignedMiners.end());
			}
		}
	}

	AlignMinersPosition();
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

		float increaseAmount = fillSpeed * deltaTime.asSeconds() * assignedMiners.size();
		currentWidth = std::min(currentWidth + increaseAmount, maxWidth);
		resource.setSize(sf::Vector2f(currentWidth, barSize.y));
	}

	if (currentWidth >= maxWidth)
	{
		resourceText.setPosition(background.getPosition().x, background.getPosition().y - 50);

		status = DEPOSIT_GOLD;

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

		float decreaseAmount = fillSpeed * deltaTime.asSeconds() * assignedMiners.size();
		currentWidth = std::max(currentWidth - decreaseAmount, 0.f);
		resource.setSize(sf::Vector2f(currentWidth, barSize.y));

	}

	if (currentWidth <= 0)
	{
		resourceText.setPosition(background.getPosition().x, background.getPosition().y - 50);
 
		//isEmpty = true;
		status = EMPTY;
	}
}

void GoldMine::AlignMinersPosition()
{
	for (int i = 0; i < assignedMiners.size(); i++)
	{
		float offsetX = 0.0f;
		float offsetY = 0.0f;
		sf::Vector2f minerPosition;

		assignedMiners[i]->body.setScale(0.8, 0.8);
		assignedMiners[i]->isWorking = true;


		if (assignedMiners.size() > 0)
		{
			if (i % 3 == 0)
			{
				offsetX = textureWidth * 0.5f;
				minerPosition.x = body.getPosition().x - offsetX;
			}
			else if (i % 3 == 1)
			{
				minerPosition.x = body.getPosition().x;
			}
			else if (i % 3 == 2)
			{
				offsetX = textureWidth * 0.5f;
				minerPosition.x = body.getPosition().x + offsetX;

			}

			if (i / 3 == 0)
			{
				offsetY = textureHeight * 0.5f;
				minerPosition.y = body.getPosition().y - offsetY;
			}
			else if (i / 3 == 1)
			{
				minerPosition.y = body.getPosition().y - offsetY;
			}
			else if (i / 3 == 2)
			{
				offsetY = textureHeight * 0.5f;
				minerPosition.y = body.getPosition().y + offsetY;
			}
		}

		assignedMiners[i]->SetPosition(minerPosition);
	}
}


