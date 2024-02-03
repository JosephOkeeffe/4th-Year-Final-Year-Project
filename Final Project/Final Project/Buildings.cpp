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
}

void Buildings::Update()
{
	CheckForCollisions();
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

void Buildings::UpdateDetectionCircles()
{
	if (!CheckIfPlaced())
	{
		MoveBuilding();
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
	sf::Vector2i cellPos = Global::GetCurrentCell(*GameManager::GetWindow(), *GameManager::GetView());
	// if(tile[cellPos.x][cellPos.y].resourceType == GOLD)
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

bool Buildings::CheckIfPlaced()
{
	return isPlaced;
}

void Buildings::SetPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void Buildings::CheckForCollisions()
{
	for (Buildings* building : GameManager::buildings)
	{
		if (building == this) return;

		if (building->body.getLocalBounds().intersects(this->body.getLocalBounds()))
		{
			Display_Text("CANT PLACE");
		}
	}
}


