#pragma once
#include <SFML/Graphics.hpp>

class Characters
{
public:

	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect textureSize);
	void Render(sf::RenderWindow& window, sf::Sprite& sprite);

	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites, bool isDead);

	int animationCount = 0; // 89 * 0, 89 * 1, 89 * 2, 89 * 3
	int m_frameNo{ 0 };
	float m_frameValue{ 0.0f }; 
	float animationSpeed{ 0.2 };
	int playerAnimation = 0;
	bool isDeadAnimationPending = false;
};

