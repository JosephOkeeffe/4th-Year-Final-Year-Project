#include "Characters.h"
#include "Globals.h"
#include <iostream>

void Characters::Init(sf::Texture& _texture, sf::Sprite& sprite, sf::IntRect& textureSize)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(textureSize);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setScale(2, 2);

	textureRect = textureSize;
	body.setTexture(_texture);

	InitDetectionCircle(150);
}

void Characters::Update()
{

}

void Characters::MouseRelease()
{
	if (isSelected)
	{
		currentState = MOVING;
		targetPosition = Global::GetMousePos(*GameManager::GetWindow());
	}

	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		SelectCharacter();
	}
}

void Characters::Draw()
{
	GameManager::GetWindow()->draw(detectionCircle);
	GameManager::GetWindow()->draw(body);
}

void Characters::InitDetectionCircle(int radius)
{
	detectionCircle.setRadius(radius);
	detectionCircle.setOrigin(radius, radius);
	detectionCircle.setPosition(body.getPosition());
	detectionCircle.setFillColor(sf::Color::Transparent);
	detectionCircle.setOutlineThickness(1);
	detectionCircle.setOutlineColor(sf::Color(255, 0, 0, 255));

	tileDetectionCircle.setRadius(tileDetectionRadius);
	tileDetectionCircle.setOrigin(tileDetectionRadius, tileDetectionRadius);
	tileDetectionCircle.setFillColor(sf::Color(255, 0, 0, 50));
}

void Characters::UpdateDetectionCircle()
{
	detectionCircle.setPosition(body.getPosition());
	tileDetectionCircle.setPosition(body.getPosition().x, body.getPosition().y + 30);
}
void Characters::UpdateCharacters()
{
	MoveCharacter();
	ChangeSelectedColour();
	UpdateDetectionCircle();
}
void Characters::MoveCharacter()
{
	float length = 0;
	
	if (CheckCurrentState(MOVING))
	{
		DeselectCharacter();

		direction = behaviour->GetDirectionFacing(targetPosition, body.getPosition());
		length = behaviour->VectorLength(direction);

		if (length != 0)
		{
			direction /= length;
		}

		FlipSpriteWithDirection(direction, body);

		if (length > 5)
		{
			body.move(direction * currentMoveSpeed);
		}
		else
		{
			currentState = IDLE;
		}
	}
}

void Characters::SelectCharacter()
{
	if (HUD::currentState == HUD::NONE)
	{
		isSelected = true;
	}
}

void Characters::DeselectCharacter()
{
	isSelected = false;
}

void Characters::Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites)
{
	int playerAnimation = m_frameNo;
	m_frameValue += animationSpeed;
	m_frameNo = static_cast<int>(m_frameValue);
	
	m_frameNo = m_frameNo % amountOfSprites;

	if (playerAnimation != m_frameNo)
	{
		body.setTextureRect(sf::IntRect(m_frameNo * startX, startY, spriteWidth, spriteHeight));
	}
}

void Characters::ChangeAnimation()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || currentState != MOVING)
	{
		animationState = IDLE_ANIM;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || CheckCurrentState(MOVING) || isFormationMoving)
	{
		animationState = RUNNING_ANIM;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		animationState = ATTACKING_ANIM;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		animationState = DEAD_ANIM;
	}

}

bool Characters::GetSelected()
{
	return isSelected;
}

void Characters::ChangeSelectedColour()
{
	if (GetSelected())
	{
		body.setColor(sf::Color::Red);
	}
	else
	{
		body.setColor(sf::Color::White);
	}
}

void Characters::CalculateAngle(sf::Sprite& target)
{
	float dx = body.getPosition().x - target.getPosition().x;
	float dy = body.getPosition().y - target.getPosition().y;
	float angle = atan2(dy, dx) * 180 / Global::PI;

	float distance = std::hypot(dx, dy);

	if (distance <= detectionRadius)
	{
		detectionCircle.setFillColor(sf::Color(255, 0, 0, 100)); 

	}
	else
	{
		detectionCircle.setFillColor(sf::Color(255, 255, 255, 100));
	}
}

void Characters::FlipSpriteWithDirection(sf::Vector2f& direction, sf::Sprite& sprite)
{
	if (direction.x < 0)
	{
		sprite.setScale(-std::abs(sprite.getScale().x), sprite.getScale().y);
	}
	else
	{
		sprite.setScale(std::abs(sprite.getScale().x), sprite.getScale().y);
	}
}

void Characters::FlipSprite()
{
	sf::Vector2f currentScale = body.getScale();

	body.setScale(currentScale.x * -1, currentScale.y);
}

bool Characters::CheckCurrentState(State stateToCheck)
{
	return currentState == stateToCheck;
}

void Characters::SetCurrentState(State stateToChange)
{
	currentState = stateToChange;
}

void Characters::SetPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}

//SteeringOutput Characters::SetWanderBehaviour(sf::Sprite& sprite)
//{
//	SteeringOutput steeringOutput = behaviour->WanderBehaviour(sprite);
//	return steeringOutput;
//}
//
//SteeringOutput Characters::SetSeekBehaviour(sf::Vector2f targetPos, sf::Sprite& sprite)
//{
//	SteeringOutput steeringOutput = behaviour->SeekBehaviour(targetPos, sprite);
//	return steeringOutput;
//}






