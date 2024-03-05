#include "Archer.h"
#include "Globals.h"

Archer::Archer()
{
	textureRect = { 0,0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("archer"), body, textureRect);
	animationSpeed = 0.04;
	body.setScale(1.5, 1.5);
	characterType = ARCHER;
}

void Archer::Update()
{
	UpdateCharacters();
	CheckAnimationState();
	AnimateArcher();
}

void Archer::AnimateArcher()
{
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, body, amountOfSprites);
}

void Archer::CheckAnimationState()
{

	if (GetCurrentState(IDLE) && !isFormationMoving)
	{
		currentFrameY = 0;
		textureHeight = 50;
	}
	else if (GetCurrentState(MOVING) || isFormationMoving)
	{
		currentFrameY = 2;
		textureHeight = 52;
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

sf::Sprite& Archer::GetSprite()
{
	return body;
}
