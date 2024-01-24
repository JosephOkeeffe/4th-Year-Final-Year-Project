#include "Characters.h"
#include "Globals.h"
#include <iostream>

void Characters::Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(textureSize);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setScale(2, 2);

	/*detectionCircle.setRadius(detectionRadius);
	detectionCircle.setOrigin(detectionRadius, detectionRadius);
	detectionCircle.setPosition(sprite.getPosition());
	detectionCircle.setFillColor(sf::Color(255, 0, 0, 50));*/

	tileDetectionCircle.setRadius(tileDetectionRadius);
	tileDetectionCircle.setOrigin(tileDetectionRadius, tileDetectionRadius);
	tileDetectionCircle.setFillColor(sf::Color(255, 0, 0, 50));

	SetTexture(texture);
	SetTextureRect(textureSize);

	InitDetectionCircle();
}

void Characters::Draw()
{
	GetWindow()->draw(detectionCircle);
	GetWindow()->draw(body);
}

void Characters::MouseUp()
{
	SelectCharacter();
}

void Characters::UpdateDetectionCircles()
{
	detectionCircle.setPosition(body.getPosition());
	tileDetectionCircle.setPosition(body.getPosition().x, body.getPosition().y + 30);
}

void Characters::SelectCharacter()
{
	sf::Vector2f mousePos = Global::GetWindowMousePos(*GetWindow(), *GetView());
	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		isSelected = !isSelected;
		CheckIfSelected();
		selectionCooldown.restart();
	}
}

void Characters::Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites, bool isDead)
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

void Characters::CheckIfSelected()
{
    if (isSelected)
    {
		body.setColor(sf::Color::Red);
    }
    else
    {
		body.setColor(sf::Color::White);
    }
}

void Characters::CalculateAngle(sf::Sprite& target)
{
	float dx = body.getPosition().x - target.getPosition().x;
	float dy = body.getPosition().y - target.getPosition().y;
	float angle = atan2(dy, dx) * 180 / Global::PI;

	float distance = std::hypot(dx, dy);

	if (distance <= detectionRadius)
	{
		detectionCircle.setFillColor(sf::Color(255, 0, 0, 100)); 

	}
	else
	{
		detectionCircle.setFillColor(sf::Color(255, 255, 255, 100));

	}
}

void Characters::FlipSprite(sf::Vector2f& direction, sf::Sprite& sprite)
{
	if (direction.x < 0)
	{
		sprite.setScale(-std::abs(sprite.getScale().x), sprite.getScale().y);
	}
	else
	{
		sprite.setScale(std::abs(sprite.getScale().x), sprite.getScale().y);
	}
}

void Characters::SetPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}


//SteeringOutput Characters::SetWanderBehaviour(sf::Sprite& sprite)
//{
//	SteeringOutput steeringOutput = behaviour->WanderBehaviour(sprite);
//	return steeringOutput;
//}
//
//SteeringOutput Characters::SetSeekBehaviour(sf::Vector2f targetPos, sf::Sprite& sprite)
//{
//	SteeringOutput steeringOutput = behaviour->SeekBehaviour(targetPos, sprite);
//	return steeringOutput;
//}






