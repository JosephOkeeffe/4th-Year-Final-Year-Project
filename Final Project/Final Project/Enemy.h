#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "Globals.h"
#include "GameManager.h"
#include "Characters.h"

class Enemy
{
public:

	enum CurrentState
	{
		IDLE, // 35 ,  68 
		WALKING, // 58, 69, 72 
		THINKING, // 26, 144,  68 
		ATTACKING, // 67, 214 , 89 
		DEAD //  50, 304 , 68
	};

	Enemy();
	void Draw();
	void Update();
	void Animate(); 
	void SetPosition(sf::Vector2f pos);
	void CheckState();

	bool IsCharacterWithinRadius(const sf::Sprite& target);

	CurrentState state = IDLE;

	sf::Sprite body;
	sf::IntRect textureRect = { 0, 0, 35, 68 };
	sf::CircleShape detectionCircle;

	float detectionRadius = 100.0f;

	int currentFrameX = 36;
	int currentFrameY = 0;
	int textureWidth = 35;
	int textureHeight = 68;
	int amountOfSprites = 7;

	int animationCount = 0;
	int m_frameNo{ 0 };
	float m_frameValue{ 0.0f };
	float animationSpeed{ 0.05 };
	int playerAnimation = 0;           
private:
};

