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
	detectionCircle.setOrigin(detectionRadius / 2, detectionRadius /2);
	//detectionCircle.setPosition(sprite.getPosition().x * 0.5, sprite.getPosition().y * 0.5);
	detectionCircle.setFillColor(sf::Color(255, 0, 0, 50));

}

void Characters::Render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	window.draw(detectionCircle);
	detectionCircle.setPosition(sprite.getPosition().x - (sprite.getTextureRect().width), sprite.getPosition().y - (sprite.getTextureRect().height));

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

void Characters::SelectCharacter(sf::Sprite& sprite, sf::RenderWindow& window) 
{
    if (sprite.getGlobalBounds().contains(sf::Vector2f(Global::GetMousePos(window)))) 
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






