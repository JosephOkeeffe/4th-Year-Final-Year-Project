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

void Buildings::MouseRelease()
{

}

void Buildings::UpdateDetectionCircles()
{
	detectionCircle.setPosition(body.getPosition());
}

void Buildings::SelectBuilding()
{
	isSelected = !isSelected;
}

bool Buildings::GetSelected()
{
	return isSelected;
}
