#include "OilMan.h"
#include "Globals.h"
#include "Buildings.h"

OilMan::OilMan()
{
	srand(time(nullptr));

	textureRect = { 0, 0, textureWidth, textureHeight };
	animationSpeed = 0.08;

	Init(Textures::GetInstance().GetTexture("oil-man"), body, textureRect);

	body.setScale(1, 1);
}

void OilMan::Update()
{
	UpdateCharacters();
	CheckAnimationState();
	AnimateWorker();
	CheckCurretnState();

	
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

void OilMan::CheckCurretnState()
{
	if (GetSelected())
	{
		currentState = IDLE;

		if (workingPlace != nullptr)
		{
			if (body.getGlobalBounds().intersects(workingPlace->body.getGlobalBounds()))
			{
				body.setPosition(workingPlace->body.getPosition().x, workingPlace->body.getPosition().y + 130);
			}
			workingPlace->isBeingUsed = false;
			workingPlace->currentWidth = 0;
			workingPlace = nullptr;
		}

	}

	if (GetCurrentState(MOVING) || GetCurrentState(SEARCH_FOR_RESOURCE))
	{
		if (workingPlace != nullptr)
		{
			if (body.getGlobalBounds().intersects(workingPlace->body.getGlobalBounds()))
			{
				SetCurrentState(GATHERING);
				body.setPosition(workingPlace->body.getPosition());
				workingPlace->isBeingUsed = true;
			}
		}
	}

	if (GetCurrentState(SEARCH_FOR_RESOURCE))
	{
		if (!workingPlace->isBeingUsed)
		{
			MoveSpriteToTarget(workingPlace->body.getPosition());
		}
	}
	if (GetCurrentState(GATHERING))
	{
		if (workingPlace->isFull)
		{
			SetCurrentState(UNLOADING);
		}
		else
		{
			workingPlace->GenerateOil();
		}
	}
	if (GetCurrentState(UNLOADING))
	{
		if (workingPlace->isEmpty)
		{
			SetCurrentState(RETURN_TO_BASE);
		}
		else
		{
			workingPlace->DepositOil();
		}
	}
	if (GetCurrentState(RETURN_TO_BASE))
	{
		workingPlace->isBeingUsed = false;
		MoveSpriteToTarget(GameManager::headquarters->body.getPosition());

		if (body.getGlobalBounds().intersects(GameManager::headquarters->body.getGlobalBounds()))
		{
			SetCurrentState(SEARCH_FOR_RESOURCE);
		}

	}
	//if (GetCurrentState(INVENTORY_FULL))
	//{
	//	if (!workingPlace->isFull)
	//	{
	//		body.setPosition(workingPlace->body.getPosition().x, workingPlace->body.getPosition().y + 60);
	//		workingPlace->isBeingUsed = false;
	//		DeselectCharacter();
	//	}
	//}
	/*else
	{
		if (workingPlace != nullptr)
		{
			workingPlace->isBeingUsed = false;
		}
	}*/
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