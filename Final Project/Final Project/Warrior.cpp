#include "Warrior.h"
#include "Globals.h"

Warrior::Warrior()
{
	textureRect = { 0, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("warrior"), body, textureRect);
}

void Warrior::Update()
{
	UpdateCharacters();
	CheckAnimationState();
	ChangeAnimation();
	AnimateWarrior();
}

void Warrior::AnimateWarrior()
{
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, body, amountOfSprites);
}

void Warrior::CheckAnimationState()
{
	if (animationState == IDLE_ANIM)
	{
		currentFrameY = 0;
	}
	if (animationState == RUNNING_ANIM)
	{
		currentFrameY = 2;
	}
	if (animationState == ATTACKING_ANIM)
	{
		currentFrameY = 3;
	}
	if (animationState == DEAD_ANIM)
	{
		SetCurrentState(DEAD);
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
