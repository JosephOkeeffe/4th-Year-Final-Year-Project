#pragma once
#include <SFML/Graphics.hpp>
#include "Behaviour.h"
#include "Textures.h"

class Characters
{
public:

	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize);
	void Render(sf::RenderWindow& window, sf::Sprite& sprite);

	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites, bool isDead);
	void SelectCharacter(sf::Sprite& sprite, sf::RenderWindow& window);
	void CheckIfSelected(sf::Sprite& sprite);
	void CalculateAngle(sf::Sprite& sprite, sf::Sprite& target);
	void FlipSprite(sf::Vector2f& direction, sf::Sprite& sprite);

	inline void SetBehaviour(Behaviour* newBehaviour)
	{
		behaviour = newBehaviour;
	}

	SteeringOutput SetWanderBehaviour(sf::Sprite& sprite);
	SteeringOutput SetSeekBehaviour(sf::Vector2f targetPos, sf::Sprite& sprite);

	sf::CircleShape detectionCircle;
	float detectionRadius = 100.0f;

	Behaviour* behaviour;

	sf::Vector2f m_velocity = { 0, 0 };
	sf::Vector2f direction;

	int animationCount = 0; // 89 * 0, 89 * 1, 89 * 2, 89 * 3
	int m_frameNo{ 0 };
	float m_frameValue{ 0.0f }; 
	float animationSpeed{ 0.2 };
	int playerAnimation = 0;
	bool isDeadAnimationPending = false;

	bool isSelected = false;
	bool isMoving = false;
	sf::Clock selectionCooldown;

};

