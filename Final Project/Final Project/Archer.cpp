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
	switch (currentState)
	{
	case Characters::IDLE:
		currentFrameY = 0;
		textureHeight = 50;
		break;
	case Characters::MOVING:
		currentFrameY = 2;
		textureHeight = 52;
		break;
	case Characters::ATTACKING:
		currentFrameY = 3;
		break;
	case Characters::DEAD:
		currentFrameY = 4;
		break;
	default:
		break;
	}
}

sf::Sprite& Archer::GetSprite()
{
	return body;
}
