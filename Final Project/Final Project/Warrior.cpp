#include "Warrior.h"
#include "Globals.h"

Warrior::Warrior(sf::Texture& warriorTexture, sf::RenderWindow& t_window) : window(t_window)
{
	Init(warriorTexture, sprite, warriorRect);
}

void Warrior::DrawWarrior(sf::RenderWindow& window)
{
	Render(window, sprite);
}

void Warrior::Update(sf::RenderWindow& window)
{
	CheckAnimationState();
	ChangeAnimation();
	AnimateWarrior();
	
	MoveWarrior(window);
}

void Warrior::MouseUp(sf::RenderWindow& window)
{
	SelectCharacter(sprite, window);
}

void Warrior::MoveWarrior(sf::RenderWindow& window)
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
	

	// Implement Arrive behaviour from oisins lab
}

void Warrior::AnimateWarrior()
{
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, sprite, amountOfSprites, isDead);
}

void Warrior::ChangeAnimation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || !isMoving)
	{
		currentAnimation = ANIMATION::IDLE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)|| isMoving)
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

void Warrior::CheckAnimationState()
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

sf::Sprite& Warrior::GetSprite()
{
	return sprite;
}