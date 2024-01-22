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
	UpdateDetectionCircles();

	CheckAnimationState();
	ChangeAnimation();
	AnimateArcher();
	MoveArcher();
}

void Archer::MoveArcher()
{
	float length = 0;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isSelected)
	{
		isMoving = true;
		targetPos = Global::GetMousePos(*GetWindow());
	}

	if (isMoving)
	{
		isSelected = false;
		CheckIfSelected();
		direction = behaviour->GetDirectionFacing(targetPos, body.getPosition());
		length = behaviour->VectorLength(direction);

		if (length != 0)
		{
			direction /= length;
		}

		FlipSprite(direction, body);

		if (length > 5)
		{
			body.move(direction * moveSpeed);
		}
		else
		{
			isMoving = false;
		}
	}
}

void Archer::AnimateArcher()
{
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, body, amountOfSprites, isDead);
}

void Archer::ChangeAnimation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || !isMoving)
	{
		currentAnimation = ANIMATION::IDLE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || isMoving)
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

void Archer::CheckAnimationState()
{
	if (currentAnimation == ANIMATION::IDLE)
	{
		currentFrameY = 0;
		textureHeight = 50;
	}
	if (currentAnimation == ANIMATION::RUNNING)
	{
		currentFrameY = 2;
		textureHeight = 52;

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

sf::Sprite& Archer::GetSprite()
{
	return body;
}
