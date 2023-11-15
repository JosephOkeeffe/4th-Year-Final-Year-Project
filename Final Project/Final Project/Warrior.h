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

	Warrior(sf::RenderWindow& t_window);
	void DrawWarrior(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void MouseUp(sf::RenderWindow& window);

	void MoveWarrior(sf::RenderWindow& window);

	void AnimateWarrior();
	void ChangeAnimation();
	void CheckAnimationState();

	void SetPosition(sf::Vector2f pos);

	sf::Sprite& GetSprite();
	sf::Vector2f& GetPos();

private:

	sf::RenderWindow& window;

	bool isDead = false;
	sf::Sprite sprite;

	int currentAnimation = ANIMATION::IDLE;
	int currentFrameX = 32;
	int currentFrameY = 0;
	int textureWidth = 32;
	int textureHeight = 32;
	int amountOfSprites = 10;
	sf::IntRect warriorRect{ 0,0, textureWidth, textureHeight };

	// Moving
	sf::Vector2f targetPos;
	float moveSpeed = 2.0f;
};

