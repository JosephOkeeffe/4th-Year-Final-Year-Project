#include "Buildings.h"

void Buildings::Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize, float scale)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(textureSize);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setScale(scale, scale);

	//mainRectangle.setSize(sf::Vector2f(180, 120));
	//mainRectangle.setFillColor(sf::Color::Blue);
	//mainRectangle.setOrigin(mainRectangle.getLocalBounds().width / 2, 0);
	//

	SetTexture(texture);
	SetTextureRect(textureSize);
	InitDetectionCircle();
}

void Buildings::Draw()
{
	GetWindow()->draw(detectionCircle);
	GetWindow()->draw(body);

	//if (isSelected)
	//{
	//	GetWindow()->draw(mainRectangle);
	//}
}

//void Buildings::CheckIfSelected()
//{
//	if (GetSelected())
//	{
//		//BuildingUI::Activate({ body.getPosition().x, body.getPosition().y + 80 });
//		mainRectangle.setPosition(body.getPosition().x, body.getPosition().y + 80);
//		body.setColor(sf::Color(128, 128, 128));
//	}
//	else
//	{
//		//BuildingUI::Deactivate();
//		body.setColor(sf::Color::White);
//	}
//}

void Buildings::Update()
{
	detectionCircle.setPosition(body.getPosition());
}

void Buildings::MouseUp()
{

}

void Buildings::SelectBuilding()
{
	isSelected = !isSelected;
}

bool Buildings::GetSelected()
{
	return isSelected;
}
