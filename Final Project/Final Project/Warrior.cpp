#include "Warrior.h"
#include "Globals.h"

Warrior::Warrior()
{
	textureRect = { 0, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("warrior"), body, textureRect);
	characterType = WARRIOR;
}

void Warrior::Update()
{
	Characters::Update();
	CheckAnimationState();
	AnimateWarrior();
}

void Warrior::AnimateWarrior()
{
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, body, amountOfSprites);
}

void Warrior::CheckAnimationState()
{
	if (GetCurrentState(IDLE) && !isMovingIntoFormation)
	{
		currentFrameY = 0;
	}
	else if (GetCurrentState(MOVING) || isMovingIntoFormation)
	{
		currentFrameY = 2;
	}
	else if (GetCurrentState(ATTACKING))
	{
		currentFrameY = 3;
	}
	else if (GetCurrentState(DEAD))
	{
		currentFrameY = 4;
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
