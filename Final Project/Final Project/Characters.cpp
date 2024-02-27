#include "Characters.h"
#include "Globals.h"
#include <iostream>

void Characters::Init(sf::Texture& _texture, sf::Sprite& sprite, sf::IntRect& textureSize)
{
	srand(time(nullptr));

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
	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
	sf::Vector2i cellPos = Global::GetCurrentCell(*GameManager::GetWindow(), *GameManager::GetView());
	if (isSelected)
	{
		SetCurrentState(MOVING);
		//targetPosition = mousePos;
		goalTile = &GameManager::tiles[cellPos.x][cellPos.y];

		if (characterType == ARCHER || characterType == WARRIOR)
		{
			path = GameManager::FindPath(startTile, goalTile, false);
		}
		else
		{
			path = GameManager::FindPath(startTile, goalTile, true);
		}
	}


	
	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		SelectCharacter();
	}
}

void Characters::Draw()
{
	particleSystem.draw(*GameManager::GetWindow());
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

	if(!isWorking )
	{
		if (GetSelected())
		{

			sf::Vector2f randomVelocity((rand() % 5 - 2) * 2.0f, (rand() % 5 - 2) * 2.0f);

			// ADD A TRAIL CLASS, SO WHEN PEOPLE WALK LEAVE A TRAIL
			// ADD A PARTICLE FOR WORKING
			particleSystem.addParticle(tileDetectionCircle.getPosition(), randomVelocity, sf::Color::Yellow, 3, 1);
			particleSystem.update();

			int x = body.getPosition().x / Global::CELL_SIZE;
			int y = body.getPosition().y / Global::CELL_SIZE;

			startTile = &GameManager::tiles[x][y];
		}
		else
		{
			if (!GetCurrentState(MOVING))
			{
				particleSystem.clearParticles();
			}
		}
	}
}
void Characters::MoveCharacter()
{
	float length = 0;

	if (GetCurrentState(MOVING) && !path.empty())
	{
		DeselectCharacter();
		particleSystem.addParticle(body.getPosition(), { 0,0 }, sf::Color::Black, 3, 2);
		particleSystem.update();

		// Set the target position to the next tile in the path
		targetPosition = path.front()->tile.getPosition();
		targetPosition.x += 50;
		targetPosition.y += 50;

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
			path.erase(path.begin());

			if (!path.empty())
			{
				targetPosition = path.front()->tile.getPosition();
				//particleSystem.update();
				targetPosition.x += 50;
				targetPosition.y += 50;
			}
			else
			{
				currentState = IDLE; 
			}
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

void Characters::ChangeSpeedDependingOnTiles()
{
	sf::Vector2i tempPos;

	tempPos.x = static_cast<int>(tileDetectionCircle.getPosition().x / Global::CELL_SIZE);
	tempPos.y = static_cast<int>(tileDetectionCircle.getPosition().y / Global::CELL_SIZE);

	if (GameManager::tiles[tempPos.x][tempPos.y].GetTileType() == NONE)
	{
		currentMoveSpeed = defaultMoveSpeed;
	}
	else if (GameManager::tiles[tempPos.x][tempPos.y].GetTileType() == PATH)
	{
		currentMoveSpeed = defaultMoveSpeed * 1.5;
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
		body.setColor(sf::Color(200, 50, 50));
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

bool Characters::GetCurrentState(State stateToCheck)
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






