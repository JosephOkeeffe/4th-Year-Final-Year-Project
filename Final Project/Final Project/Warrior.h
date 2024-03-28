#pragma once
#include "Characters.h"
#include "Globals.h"

class Warrior : public Characters 
{
public:
	Warrior();
	void Update() override;
	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites) override;
	void AnimateWarrior();
	void CheckAnimationState();
	void Attack(Enemy* target);

	sf::Sprite& GetSprite();
	sf::Vector2f& GetPos();



private:


	int currentFrameX = 32;
	int currentFrameY = 0;
	int textureWidth = 32;
	int textureHeight = 32;
	int amountOfSprites = 10;
	//sf::IntRect rect{ 0,0, textureWidth, textureHeight };

	// Moving
	sf::Vector2f targetPos;
};

