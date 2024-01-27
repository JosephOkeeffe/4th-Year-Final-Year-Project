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

	Warrior();
	void Update() override;


	void AnimateWarrior();
	void ChangeAnimation();
	void CheckAnimationState();

	sf::Sprite& GetSprite();
	sf::Vector2f& GetPos();

private:

	int currentAnimation = ANIMATION::IDLE;
	int currentFrameX = 32;
	int currentFrameY = 0;
	int textureWidth = 32;
	int textureHeight = 32;
	int amountOfSprites = 10;
	//sf::IntRect rect{ 0,0, textureWidth, textureHeight };

	// Moving
	sf::Vector2f targetPos;
};

