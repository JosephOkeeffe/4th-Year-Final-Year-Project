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
	AnimateWarrior();
}

void Warrior::AnimateWarrior()
{
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, body, amountOfSprites);
}

void Warrior::CheckAnimationState()
{



	switch (currentState)
	{
	case Characters::IDLE:
		currentFrameY = 0;
		break;
	case Characters::MOVING:
		currentFrameY = 2;
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

sf::Sprite& Warrior::GetSprite()
{
	return body;
}

sf::Vector2f& Warrior::GetPos()
{
	sf::Vector2f pos = body.getPosition();
	return pos;
}
