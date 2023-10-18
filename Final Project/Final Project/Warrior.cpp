#include "Warrior.h"

Warrior::Warrior(sf::Texture& warriorTexture)
{
	Init(warriorTexture, warriorSprite, warriorRect);
}

void Warrior::DrawWarrior(sf::RenderWindow& window)
{
	Render(window, warriorSprite);
}

void Warrior::Update(sf::RenderWindow& window)
{
	CheckAnimationState();
	ChangeAnimation();
	AnimateWarrior();
	MoveWarrior(window);
}

void Warrior::MoveWarrior(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		mousePosition = sf::Mouse::getPosition(window);
		worldMousePosition = window.mapPixelToCoords(mousePosition);
		direction = worldMousePosition - warriorSprite.getPosition();

		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		if (length != 0) 
		{
			direction /= length;
		}
		warriorSprite.move(direction * moveSpeed);
	}

	// Implement Arrive behaviour from oisins lab
}

void Warrior::AnimateWarrior()
{
	
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, warriorSprite, amountOfSprites, isDead);
	
}

void Warrior::ChangeAnimation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		currentAnimation = ANIMATION::IDLE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
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
