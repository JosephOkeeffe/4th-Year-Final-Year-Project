#pragma once
#include <SFML/Graphics.hpp>
#include "Characters.h"

//#include "Projectile.h"
class Archer : public Characters
{
public:

	Archer();
	void Update() override;
	void Draw() override;
	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites) override;
	void AnimateArcher();
	void CheckAnimationState();
	void Attack();

	sf::Sprite& GetSprite();	

private:

	int currentFrameX = 35;
	int currentFrameY = 0;
	int textureWidth = 35;
	int textureHeight = 50;
	int amountOfSprites = 2;
	// Moving
	sf::Vector2f targetPos;
	float moveSpeed = 2.0f;



	//std::vector<Projectile> projectiles;
};

 