#include "Worker.h"
#include "Globals.h"

Worker::Worker()
{
	textureRect = { 0, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("worker"), body, textureRect);
}

void Worker::Update()
{
	UpdateCharacters();
	CheckAnimationState();
	ChangeAnimation();
	//AnimateWorker();
}

void Worker::AnimateWorker()
{
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, body, amountOfSprites);
}

void Worker::CheckAnimationState()
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

sf::Sprite& Worker::GetSprite()
{
	return body;
}

sf::Vector2f& Worker::GetPos()
{
	sf::Vector2f pos = body.getPosition();
	return pos;
}
