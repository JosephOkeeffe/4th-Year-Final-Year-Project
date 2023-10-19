#pragma once
#include "Characters.h"
#include "Globals.h"

class Warrior : public Characters 
{
public:
	enum ANIMATION
	{
		IDLE,
		RUNNING,
		ATTACKING,
		DEAD,

	};

	Warrior(sf::Texture& warriorTexture, sf::RenderWindow& t_window);
	void DrawWarrior(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);

	void MoveWarrior(sf::RenderWindow& window);

	void AnimateWarrior();
	void ChangeAnimation();
	void CheckAnimationState();

private:

	bool isDead = false;
	sf::Sprite warriorSprite;

	int currentAnimation = ANIMATION::IDLE;
	int currentFrameX = 32;
	int currentFrameY = 0;
	int textureWidth = 32;
	int textureHeight = 32;
	int amountOfSprites = 10;
	sf::IntRect warriorRect{ 0,0, textureWidth, textureHeight };

	// Moving
	sf::Vector2i mousePosition;
	sf::Vector2f worldMousePosition;
	sf::Vector2f direction;
	float moveSpeed = 2.0f;

	sf::RenderWindow& window;
};

