#include "Characters.h"

void Characters::Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect textureSize)
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