#include "Buildings.h"

void Buildings::Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize, float scale)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(textureSize);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setScale(scale, scale);

	SetTexture(texture);
	SetTextureRect(textureSize);
	InitDetectionCircle(400);
}

void Buildings::Draw()
{
	GetWindow()->draw(detectionCircle);
	GetWindow()->draw(body);
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

void Buildings::PlaceBuilding()
{
	sf::Vector2i cellPos = Global::GetCurrentCell(*GetWindow(), *GetView());
	// if(tile[cellPos.x][cellPos.y].resourceType == GOLD)
	isPlaced = !isPlaced;
}

bool Buildings::CheckIfPlaced()
{
	return isPlaced;
}

void Buildings::SetPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void Buildings::MoveBuilding()
{
	sf::Vector2i newCellPos = Global::GetCurrentCell(*GetWindow(), *GetView());
	sf::Vector2f newPos;
	newPos.x = (newCellPos.x * Global::CELL_SIZE) + Global::CELL_SIZE / 2;
	newPos.y = (newCellPos.y * Global::CELL_SIZE) + Global::CELL_SIZE * 0.4;
	SetPosition(newPos);
}

bool Buildings::CheckIfSelected()
{
	return isSelected;
}
