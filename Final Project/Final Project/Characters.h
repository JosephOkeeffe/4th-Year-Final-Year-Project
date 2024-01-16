#pragma once
#include <SFML/Graphics.hpp>
#include "Behaviour.h"
#include "Textures.h"
#include "exampleParent.h"

class Characters : public GameObject
{
public:

	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize);
	//void Render(sf::RenderWindow& window, sf::Sprite& sprite);
	void Draw() override;
	//void Update() override;
	void MouseUp() override;

	void UpdateArcher();

	void SelectCharacter();

	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites, bool isDead);
	void CheckIfSelected();
	void CalculateAngle(sf::Sprite& target);
	void FlipSprite(sf::Vector2f& direction, sf::Sprite& sprite);

	void LoadSpriteData(sf::Vector2f& pos);

	//inline void SetBehaviour(Behaviour* newBehaviour)
	//{
	//	behaviour = newBehaviour;
	//}

	//SteeringOutput SetWanderBehaviour(sf::Sprite& sprite);
	//SteeringOutput SetSeekBehaviour(sf::Vector2f targetPos, sf::Sprite& sprite);

	bool isDead = false;
	sf::CircleShape detectionCircle;
	float detectionRadius = 100.0f;

	sf::CircleShape tileDetectionCircle;
	float tileDetectionRadius = 10;

	Behaviour* behaviour;

	sf::Vector2f m_velocity = { 0, 0 };
	sf::Vector2f direction;

	int animationCount = 0;
	int m_frameNo{ 0 };
	float m_frameValue{ 0.0f }; 
	float animationSpeed{ 0.2 };
	int playerAnimation = 0;
	bool isDeadAnimationPending = false;

	bool isSelected = false;
	bool isMoving = false;
	sf::Clock selectionCooldown;
	float defaultMoveSpeed = 2.0f;
	float currentMoveSpeed = defaultMoveSpeed;

};

