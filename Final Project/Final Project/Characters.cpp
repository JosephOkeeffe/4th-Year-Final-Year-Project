#include "Characters.h"
#include <iostream>

void Characters::Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(textureSize);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setPosition(150, 150);
	
	sprite.setScale(2, 2);

}

void Characters::Render(sf::RenderWindow& window, sf::Sprite& sprite)
{
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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
        if (selectionCooldown.getElapsedTime().asSeconds() >= 1)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f localMousePos = window.mapPixelToCoords(mousePos);

            if (sprite.getGlobalBounds().contains(sf::Vector2f(localMousePos))) 
            {
                isSelected = !isSelected;

                if (isSelected) 
                {
                    sprite.setColor(sf::Color::Red);
                }
                else 
                {
                    sprite.setColor(sf::Color::White);
                }

                selectionCooldown.restart();
            }
        }
    }
}






