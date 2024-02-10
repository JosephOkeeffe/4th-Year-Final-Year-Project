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
}

void Buildings::Update()
{
	
}

void Buildings::MouseRelease()
{
}

void Buildings::Draw()
{
	GameManager::GetWindow()->draw(detectionCircle);
	GameManager::GetWindow()->draw(body);
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

bool Buildings::CheckIfSelected()
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
	newPos.y = (newCellPos.y * Global::CELL_SIZE) + Global::CELL_SIZE * 0.4;
	SetPosition(newPos);
}

bool Buildings::GetPlacedStatus()
{
	return isPlaced;
}

bool Buildings::CheckIfCanBePlaced(sf::Vector2f mousePos, sf::Vector2i cell)
{
	if (GameManager::tiles[cell.x][cell.y].GetTileType() == RESOURCE &&
		GameManager::tiles[cell.x][cell.y].GetDiscoveredStatus())
	{
		return true;
	}

	return false;
}

void Buildings::SetPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void Buildings::ChangeSelectedColour()
{
	if (CheckIfSelected() && GetPlacedStatus())
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


