#include "OilExtractor.h"

OilExtractor::OilExtractor(sf::Vector2f pos)
{
	textureRect = { 1, currentFrameY, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("oil"), body, textureRect, 1.8);
	body.setPosition(pos);
	body.setScale(body.getScale().x, 1.8);
	SetBuildingType(OIL_EXTRACTOR_BUILDING);
	animationSpeed = 0.05;
}

void OilExtractor::MouseRelease()
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

void OilExtractor::Update()
{
	UpdateBuildings();
	deltaTime = clock.restart();

	if (GetPlacedStatus())
	{
		Animate(currentFrameX, currentFrameY, textureWidth, textureHeight, body, amountOfSprites);
	}

	switch (status)
	{
	case EMPTY:
		assignedWorkers.clear();
		currentWidth = 0;
		break;
	case GENERATING:
		GenerateOil();
		break;
	case DEPOSITING:
		DepositOil();
		break;
	default:
		break;
	}

	for (Characters* temp : GameManager::units)
	{
		if (temp->characterType == temp->OIL_MAN)
		{
			if (temp->body.getGlobalBounds().intersects(body.getGlobalBounds()))
			{
				if ((temp->GetCurrentState(temp->SEARCH_FOR_RESOURCE) || temp->GetCurrentState(temp->MOVING)))
				{
					static_cast<OilMan*>(temp)->workingPlace = this;
					assignedWorkers.push_back(static_cast<OilMan*>(temp));
					temp->SetCurrentState(temp->GATHERING);

					if (status != DEPOSITING)
					{
						status = GENERATING;
					}
				}
			}

			if (assignedWorkers.size() > 1 && temp->GetSelected())
			{
				assignedWorkers.erase(std::remove(assignedWorkers.begin(), assignedWorkers.end(), static_cast<OilMan*>(temp)), assignedWorkers.end());
			}
		}
	}

	AlignWorkersPosition(assignedWorkers, textureWidth, textureHeight);
}

void OilExtractor::GenerateOil()
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
	}

	if (currentWidth >= maxWidth)
	{
		resourceText.setPosition(background.getPosition().x, background.getPosition().y - 50);
		status = DEPOSITING;
	}
}

void OilExtractor::DepositOil()
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
	}

	if (currentWidth <= 0)
	{
		resourceText.setPosition(background.getPosition().x, background.getPosition().y - 50);
		status = EMPTY;
	}
}

