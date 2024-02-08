#include "Archer.h"
#include "Globals.h"

Archer::Archer()
{
	textureRect = { 0,0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("archer"), body, textureRect);
	animationSpeed = 0.04;
	body.setScale(1.5, 1.5);

}

void Archer::Update()
{
	UpdateCharacters();
	CheckAnimationState();
	ChangeAnimation();
	AnimateArcher();
}

void Archer::AnimateArcher()
{
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, body, amountOfSprites);
}

void Archer::CheckAnimationState()
{
	if (animationState == IDLE_ANIM)
	{
		currentFrameY = 0;
		textureHeight = 50;
	}
	if (animationState == RUNNING_ANIM)
	{
		currentFrameY = 2;
		textureHeight = 52;

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

sf::Sprite& Archer::GetSprite()
{
	return body;
}
