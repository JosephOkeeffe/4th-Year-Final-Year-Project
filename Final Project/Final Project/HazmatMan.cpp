#include "HazmatMan.h"
#include "Globals.h"
#include "Buildings.h"

HazmatMan::HazmatMan()
{

	textureRect = { 0, 0, textureWidth, textureHeight };
	animationSpeed = 0.1 ;

	Init(Textures::GetInstance().GetTexture("hazmat-man"), body, textureRect);

	body.setScale(1.8, 1.8);
}

void HazmatMan::Update()
{
	UpdateCharacters();
	CheckAnimationState();
	AnimateWorker();

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
			workingPlace->GenerateUranium();
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
			workingPlace->DepositUranium();
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

void HazmatMan::MouseRelease()
{
	if (isSelected)
	{
		SetCurrentState(MOVING);
		targetPosition = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());

		for (Buildings* object : GameManager::buildings)
		{
			if (object->GetBuildingType() == object->URANIUM_EXTRACTOR_BUILDING)
			{
				if (object->body.getGlobalBounds().contains(targetPosition))
				{
					Display_Text("WHO'S RANIUM?");
					workingPlace = static_cast<UraniumExtractor*>(object);
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

void HazmatMan::MoveSpriteToTarget(sf::Vector2f targetPosition)
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

void HazmatMan::AnimateWorker()
{
	Animate(currentFrameX, currentFrameY, textureWidth, textureHeight, body, amountOfSprites);
}

void HazmatMan::CheckAnimationState()
{
	if (GetCurrentState(IDLE) && !GetSelected())
	{
		// 267 / 10 = 24
		currentFrameX = 28;
		currentFrameY = 100;
		textureWidth = 28;
		textureHeight = 44;
		amountOfSprites = 16;
	}
	else if (GetCurrentState(MOVING) || GetCurrentState(SEARCH_FOR_RESOURCE))
	{
		currentFrameX = 28;    
		currentFrameY = 0;
		textureWidth = 28 ; 
		textureHeight = 45; 
		amountOfSprites = 12;

	} 
	else if (GetCurrentState(GATHERING))
	{
		// 222 / 5 = 44
		currentFrameX = 44;
		currentFrameY = 47;
		textureWidth = 44;
		textureHeight = 51;   
		amountOfSprites = 5;
	}
	else if (GetCurrentState(RETURN_TO_BASE))
	{
		currentFrameX = 44;
		currentFrameY = 147;
		textureWidth = 44;
		textureHeight = 43;
		amountOfSprites = 7;    
	} 
	else if (GetCurrentState(UNLOADING) || GetSelected() || GetCurrentState(INVENTORY_FULL))
	{
		currentFrameX = 36;
		currentFrameY = 193;
		textureWidth = 36;
		textureHeight = 43;
		amountOfSprites = 4;
	}
	else if (GetCurrentState(DEAD))
	{

	}
}

sf::Sprite& HazmatMan::GetSprite()
{
	return body;
}

sf::Vector2f& HazmatMan::GetPos()
{
	sf::Vector2f pos = body.getPosition();
	return pos;
}

