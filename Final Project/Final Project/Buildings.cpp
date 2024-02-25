#include "Buildings.h"

void Buildings::Init(sf::Texture& _texture, sf::Sprite& sprite, sf::IntRect& textureSize, float scale)
{
	sprite.setTexture(_texture);
	sprite.setTextureRect(textureSize);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setScale(scale, scale);

	textureRect = textureSize;
	body.setTexture(_texture);

	InitDetectionCircle(400);

	background.setSize(barSize);
	background.setFillColor(sf::Color::Black);
	background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);

	resource.setSize({ 0, barSize.y });
	resource.setFillColor(sf::Color::Yellow);
	resource.setOrigin(background.getOrigin());

	resourceText.setFont(Global::font);
	resourceText.setCharacterSize(30);
	resourceText.setFillColor(sf::Color::Black);
	resourceText.setOutlineThickness(1);
	resourceText.setOutlineColor(sf::Color::White);
	resourceText.setOrigin(resourceText.getGlobalBounds().width / 2, resourceText.getGlobalBounds().height / 2);



	// Initialize original size
	 sf::Vector2f(sprite.getLocalBounds().width * scale, sprite.getLocalBounds().height * scale);
}

//void Buildings::Update()
//{
//}
//void Buildings::MouseRelease(){}

void Buildings::Draw()
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

void Buildings::InitDetectionCircle(int radius)
{
	detectionCircle.setRadius(radius);
	detectionCircle.setOrigin(radius, radius);
	detectionCircle.setPosition(body.getPosition());
	detectionCircle.setFillColor(sf::Color::Transparent);
	detectionCircle.setOutlineThickness(1);
	detectionCircle.setOutlineColor(sf::Color(255, 0, 0, 255));
}

void Buildings::UpdateBuildings()
{
	UpdateDetectionCircle();

	if (!GetPlacedStatus())
	{ 
		MoveBuilding();
	}
}

void Buildings::UpdateDetectionCircle()
{
	if (!GetPlacedStatus())
	{
		detectionCircle.setPosition(-1000,-1000);
	}
	else
	{
		detectionCircle.setPosition(body.getPosition());
	}
}

void Buildings::SelectBuilding()
{
	isSelected = true;
}

void Buildings::DeselectBuilding()
{
	isSelected = false;
}

bool Buildings::GetSelectedStatus()
{
	return isSelected;
}

void Buildings::PlaceBuilding()
{
	isPlaced = !isPlaced;
}

void Buildings::MoveBuilding()
{
	sf::Vector2i newCellPos = Global::GetCurrentCell(*GameManager::GetWindow(), *GameManager::GetView());
	sf::Vector2f newPos;
	newPos.x = (newCellPos.x * Global::CELL_SIZE) + Global::CELL_SIZE / 2;
	newPos.y = (newCellPos.y * Global::CELL_SIZE) + Global::CELL_SIZE * 0.3;
	SetPosition(newPos);
}

bool Buildings::GetPlacedStatus()
{
	return isPlaced;
}

bool Buildings::CheckIfCanBePlaced(sf::Vector2i cell)
{
	if (!GameManager::tiles[cell.x][cell.y].GetDiscoveredStatus()) return false;

	canBePlaced = false;

	if (buildingType == GOLD_MINE_BUILDING)
	{
		if (GameManager::tiles[cell.x][cell.y].GetResourceType() == GOLD_RESOURCE)
		{
			canBePlaced = true;
		}
	}

	if (buildingType == URANIUM_EXTRACTOR_BUILDING)
	{
		if (GameManager::tiles[cell.x][cell.y].GetResourceType() == URANIUM_RESOURCE)
		{
			canBePlaced = true;
		}
	}

	if (buildingType == OIL_EXTRACTOR_BUILDING)
	{
		if (GameManager::tiles[cell.x][cell.y].GetResourceType() == OIL_RESOURCE)
		{
			canBePlaced = true;
		}
	}
	return canBePlaced;
}

void Buildings::Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites)
{
	int playerAnimation = m_frameNo;
	m_frameValue += animationSpeed;
	m_frameNo = static_cast<int>(m_frameValue);

	m_frameNo = m_frameNo % amountOfSprites;

	if (playerAnimation != m_frameNo)
	{
		body.setTextureRect(sf::IntRect(m_frameNo * startX, startY, spriteWidth, spriteHeight));
	}
}

void Buildings::SetPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void Buildings::ChangeSelectedColour()
{
	if (GetSelectedStatus() && GetPlacedStatus())
	{
		body.setColor(sf::Color(128, 128, 128));
	}
	else
	{
		body.setColor(sf::Color::White);
	}
}

void Buildings::SetBuildingType(BuildingType type)
{
	buildingType = type;
}

Buildings::BuildingType Buildings::GetBuildingType()
{
	return buildingType;
}

void Buildings::AlignWorkersPosition(std::vector<Characters*> t_assignedWorkers, int texWidth, int texHeight)
{
	for (int i = 0; i < t_assignedWorkers.size(); i++)
	{
		float offsetX = 0.0f;
		float offsetY = 0.0f;
		sf::Vector2f workerPos;

		t_assignedWorkers[i]->isWorking = true;


		if (t_assignedWorkers.size() > 0)
		{
			if (i % 3 == 0)
			{
				offsetX = texWidth * 0.5f;
				workerPos.x = body.getPosition().x - offsetX;
			}
			else if (i % 3 == 1)
			{
				workerPos.x = body.getPosition().x;
			}
			else if (i % 3 == 2)
			{
				offsetX = texWidth * 0.5f;
				workerPos.x = body.getPosition().x + offsetX;

			}

			if (i / 3 == 0)
			{
				offsetY = texHeight * 0.5f;
				workerPos.y = body.getPosition().y - offsetY;
			}
			else if (i / 3 == 1)
			{
				workerPos.y = body.getPosition().y - offsetY;
			}
			else if (i / 3 == 2)
			{
				offsetY = texHeight * 0.5f;
				workerPos.y = body.getPosition().y + offsetY;
			}
		}

		t_assignedWorkers[i]->SetPosition(workerPos);
	}
}
