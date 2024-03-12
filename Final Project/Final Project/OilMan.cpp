#include "OilMan.h"

OilMan::OilMan()
{
	srand(time(nullptr));

	textureRect = { 0, 0, textureWidth, textureHeight };
	animationSpeed = 0.08;
	Init(Textures::GetInstance().GetTexture("oil-man"), body, textureRect);
	body.setScale(defaulScale, defaulScale);
	characterType = OIL_MAN;
}

void OilMan::MouseRelease()
{
	if (isSelected)
	{
		SetCurrentState(MOVING);
		targetPosition = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());

		for (Buildings* object : GameManager::buildings)
		{
			if (object->GetBuildingType() == object->OIL_EXTRACTOR_BUILDING)
			{
				if (object->body.getGlobalBounds().contains(targetPosition))
				{
					Display_Text("OIL TIME");
					workingPlace = static_cast<OilExtractor*>(object);
				}

			}
		}
	}

	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		SelectCharacter();
	}
}

void OilMan::Update()
{
	Characters::Update();
	CheckAnimationState();
	AnimateWorker();
	RemoveFromWorkPlace();
	UpdateWorkingStates();
}

void OilMan::RemoveFromWorkPlace()
{
	if (GetSelected())
	{
		SetCurrentState(IDLE);
	}
}

void OilMan::UpdateWorkingStates()
{
	if (workingPlace != nullptr)
	{
		if (body.getGlobalBounds().intersects(workingPlace->body.getGlobalBounds()) && isWorking)
		{
			if (workingPlace->status == workingPlace->GENERATING)
			{
				body.setScale(0.8, 0.8);
				SetCurrentState(GATHERING);
			}
			else if (workingPlace->status == workingPlace->DEPOSITING)
			{
				SetCurrentState(UNLOADING);
			}
			else if (workingPlace->status == workingPlace->EMPTY && GetCurrentState(UNLOADING))
			{
				body.setScale(defaulScale, defaulScale);
				SetCurrentState(RETURN_TO_BASE);
			}
		}
	}

	if (GetCurrentState(IDLE))
	{
		body.setScale(1, 1);

		if (workingPlace != nullptr)
		{
			if (body.getGlobalBounds().intersects(workingPlace->body.getGlobalBounds()))
			{
				body.setPosition(workingPlace->body.getPosition().x, body.getPosition().y + 130);
			}
			isWorking = false;
		}
		workingPlace = nullptr;
	}

	if (GetCurrentState(SEARCH_FOR_RESOURCE))
	{
		MoveSpriteToTarget(workingPlace->body.getPosition());
	}

	if (GetCurrentState(RETURN_TO_BASE))
	{
		MoveSpriteToTarget(GameManager::headquarters->body.getPosition());
		isWorking = false;
	}

	if (body.getGlobalBounds().intersects(GameManager::headquarters->body.getGlobalBounds()))
	{
		SetCurrentState(SEARCH_FOR_RESOURCE);
	}
}


void OilMan::MoveSpriteToTarget(sf::Vector2f targetPosition)
{
	sf::Vector2f direction = targetPosition - body.getPosition();
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance > 1.0f)
	{
		direction /= distance;

		sf::Vector2f temp = direction * currentMoveSpeed;
		body.move(temp);
		FlipSpriteWithDirection(direction, body);
	}
	else
	{
		body.setPosition(targetPosition);
	}
}

void OilMan::AnimateWorker()
{
	Animate(currentFrameX, currentFrameY, textureWidth, textureHeight, body, amountOfSprites);
}

void OilMan::CheckAnimationState()
{
	if (GetCurrentState(IDLE) && !GetSelected())
	{
		currentFrameY = 0;
		amountOfSprites = 6;
	}
	else if (GetCurrentState(MOVING) || GetCurrentState(SEARCH_FOR_RESOURCE))
	{
		currentFrameY = 206;
		amountOfSprites = 7;
	}
	else if (GetCurrentState(GATHERING))
	{
		currentFrameY = 276;
		amountOfSprites = 7;
	}
	else if (GetCurrentState(RETURN_TO_BASE))
	{
		currentFrameY = 68;
		amountOfSprites = 7;
	}
	else if (GetCurrentState(UNLOADING) || GetSelected() || GetCurrentState(INVENTORY_FULL))
	{
		currentFrameY = 138;
		amountOfSprites = 2;
	}
	else if (GetCurrentState(DEAD))
	{

	}
}

sf::Sprite& OilMan::GetSprite()
{
	return body;
}

sf::Vector2f& OilMan::GetPos()
{
	sf::Vector2f pos = body.getPosition();
	return pos;
}