#include "Archer.h"
#include "Globals.h"

Archer::Archer(sf::RenderWindow& t_window) : window(t_window)
{
	Init(Textures::GetInstance().GetTexture("archer"), sprite, rect);
	animationSpeed = 0.04;
	sprite.setScale(1.5, 1.5);
}

void Archer::DrawArcher(sf::RenderWindow& window)
{
	Render(window, sprite);
}

void Archer::Update(sf::RenderWindow& window)
{
	CheckAnimationState();
	ChangeAnimation();
	AnimateArcher();
	//m_velocity = SetWanderBehaviour(sprite).linear;
	m_velocity = SetSeekBehaviour(sf::Vector2f{ 500, 500 }, sprite).linear;
	sprite.move(m_velocity);
	//MoveArcher(window);
}

void Archer::MouseUp(sf::RenderWindow& window, sf::View& view)
{
	SelectCharacter(sprite, window, view);
}

void Archer::MoveArcher(sf::RenderWindow& window)
{
	float length = 0;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isSelected)
	{
		isMoving = true;
		//targetPos = Global::GetMousePos(window);
	}

	if (isMoving)
	{
		isSelected = false;
		CheckIfSelected(sprite);
		direction = behaviour->GetDirectionFacing(targetPos, sprite.getPosition());
		length = behaviour->VectorLength(direction);

		if (length != 0)
		{
			direction /= length;
		}

		FlipSprite(direction, sprite);

		if (length > 5)
		{
			sprite.move(direction * moveSpeed);
		}
		else
		{
			isMoving = false;
		}
	}
}

void Archer::AnimateArcher()
{
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, sprite, amountOfSprites, isDead);
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
	sf::Sprite& Archer::GetSprite()
	{
		return sprite;
	}
