#include "Warrior.h"
#include "Globals.h"

Warrior::Warrior()
{
	textureRect = { 0, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("warrior"), body, textureRect);
}

void Warrior::Update()
{
	UpdateDetectionCircles();

	CheckAnimationState();
	ChangeAnimation();
	AnimateWarrior();
}

void Warrior::AnimateWarrior()
{
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, body, amountOfSprites, isDead);
}

void Warrior::ChangeAnimation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || !isMoving)
	{
		currentAnimation = ANIMATION::IDLE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)|| isMoving)
	{
		currentAnimation = ANIMATION::RUNNING;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		currentAnimation = ANIMATION::ATTACKING;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		currentAnimation = ANIMATION::DEAD;
	}
}

void Warrior::CheckAnimationState()
{
	if (currentAnimation == ANIMATION::IDLE)
	{
		currentFrameY = 0;
	}
	if (currentAnimation == ANIMATION::RUNNING)
	{
		currentFrameY = 2;
	}
	if (currentAnimation == ANIMATION::ATTACKING)
	{
		currentFrameY = 3;
	}
	if (currentAnimation == ANIMATION::DEAD)
	{
		isDead = true;
		currentFrameY = 4;
	}
	else
	{
		isDead = false;
	}
}

sf::Sprite& Warrior::GetSprite()
{
	return body;
}

sf::Vector2f& Warrior::GetPos()
{
	sf::Vector2f pos = body.getPosition();
	return pos;
}
