#include "Archer.h"
#include "Globals.h"

Archer::Archer()
{
	Init(Textures::GetInstance().GetTexture("archer"), body, rect);
	animationSpeed = 0.04;
	body.setScale(1.5, 1.5);

}

void Archer::Update()
{
	UpdateArcher();

	CheckAnimationState();
	ChangeAnimation();
	AnimateArcher();
	//m_velocity = SetWanderBehaviour(sprite).linear;
	//m_velocity = SetSeekBehaviour(sf::Vector2f{ 500, 500 }, sprite).linear;
	//sprite.move(m_velocity);
	MoveArcher(*GetWindow());
}

void Archer::MouseUp(sf::RenderWindow& window)
{
	//SelectCharacter(sprite, window, view);
}

void Archer::MoveArcher(sf::RenderWindow& window)
{
	float length = 0;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isSelected)
	{
		isMoving = true;
		targetPos = Global::GetMousePos(window);
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
