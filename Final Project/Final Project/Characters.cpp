#include "Characters.h"
#include "Globals.h"
#include <iostream>

void Characters::Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(textureSize);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setPosition(150, 150);
	sprite.setScale(2, 2);

	detectionCircle.setRadius(detectionRadius);
	detectionCircle.setOrigin(detectionRadius, detectionRadius);
	detectionCircle.setPosition(sprite.getPosition()); // Set the position of the circle to the sprite's position
	detectionCircle.setFillColor(sf::Color(255, 0, 0, 50));

}

void Characters::Render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	window.draw(detectionCircle);
	detectionCircle.setPosition(sprite.getPosition()); // Set the position of the circle to the sprite's position

	window.draw(sprite);
}


void Characters::Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites, bool isDead)
{

	int playerAnimation = m_frameNo;
	m_frameValue += animationSpeed;
	m_frameNo = static_cast<int>(m_frameValue);
	
	m_frameNo = m_frameNo % amountOfSprites;

	if (playerAnimation != m_frameNo)
	{
		sprite.setTextureRect(sf::IntRect(m_frameNo * startX, startY, spriteWidth, spriteHeight));
	}
}

void Characters::SelectCharacter(sf::Sprite& sprite, sf::RenderWindow& window, sf::View& view) 
{
	sf::Vector2f mousePos = Global::GetWindowMousePos(window, view);
    if (sprite.getGlobalBounds().contains(sf::Vector2f(mousePos)))
    {
        isSelected = !isSelected;
        CheckIfSelected(sprite);
        selectionCooldown.restart();
    }
}

void Characters::CheckIfSelected(sf::Sprite& sprite)
{
    if (isSelected)
    {
        sprite.setColor(sf::Color::Red);
    }
    else
    {
        sprite.setColor(sf::Color::White);
    }
}

void Characters::CalculateAngle(sf::Sprite& sprite, sf::Sprite& target)
{
	float dx = sprite.getPosition().x - target.getPosition().x;
	float dy = sprite.getPosition().y - target.getPosition().y;
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

void Characters::LoadSpriteData(sf::Sprite& sprite, sf::Vector2f& pos)
{
	sprite.setPosition(pos);
}

SteeringOutput Characters::SetWanderBehaviour(sf::Sprite& sprite)
{
	SteeringOutput steeringOutput = behaviour->WanderBehaviour(sprite);
	return steeringOutput;
}

SteeringOutput Characters::SetSeekBehaviour(sf::Vector2f targetPos, sf::Sprite& sprite)
{
	SteeringOutput steeringOutput = behaviour->SeekBehaviour(targetPos, sprite);
	return steeringOutput;
}






