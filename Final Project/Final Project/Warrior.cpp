#include "Warrior.h"
#include "Globals.h"

Warrior::Warrior(sf::RenderWindow& t_window, sf::View& view) : window(t_window), view(view)
{
	Init(Textures::GetInstance().GetTexture("warrior"),sprite, warriorRect);
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
	SelectCharacter(sprite, window, view);
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

void Warrior::SetPosition(sf::Vector2f pos)
{
	LoadSpriteData(sprite, pos);
}

sf::Sprite& Warrior::GetSprite()
{
	return sprite;
}

sf::Vector2f& Warrior::GetPos()
{
	sf::Vector2f pos = sprite.getPosition();
	return pos;
}
