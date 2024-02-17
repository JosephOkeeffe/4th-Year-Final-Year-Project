#include "Worker.h"
#include "Globals.h"
#include "Buildings.h"

Worker::Worker()
{
	srand(time(nullptr));
	int randomNuber = rand() % 4;

	textureRect = { 0, 0, textureWidth, textureHeight };
	animationSpeed = 0.08;

	characterType = MINER;

	switch (randomNuber)
	{
	case 0:
		Init(Textures::GetInstance().GetTexture("worker"), body, textureRect);
		break;
	case 1:
		Init(Textures::GetInstance().GetTexture("worker2"), body, textureRect);
		break;
	case 2:
		Init(Textures::GetInstance().GetTexture("worker3"), body, textureRect);
		break;
	case 3:
		Init(Textures::GetInstance().GetTexture("worker4"), body, textureRect);
		break;
		break;
	default:
		break;
	}
	body.setScale(1, 1);


}

void Worker::Update()
{ 
	UpdateCharacters();
	CheckAnimationState();
	AnimateWorker();

	if (workingPlace != nullptr)
	{
		if (body.getGlobalBounds().intersects(workingPlace->body.getGlobalBounds()) && isWorking)
		{
			if (workingPlace->status == workingPlace->GENERATE_GOLD)
			{
				SetCurrentState(GATHERING);
			}
			else if (workingPlace->status == workingPlace->DEPOSIT_GOLD)
			{
				SetCurrentState(UNLOADING);
			}
			else if (workingPlace->status == workingPlace->EMPTY && GetCurrentState(UNLOADING))
			{
				body.setScale(1, 1);
				SetCurrentState(RETURN_TO_BASE);
			}
		}
	}

	if (GetCurrentState(RETURN_TO_BASE))
	{
		MoveSpriteToTarget(GameManager::headquarters->body.getPosition());
		isWorking = false;
	}

	if (GetCurrentState(SEARCH_FOR_RESOURCE))
	{
		MoveSpriteToTarget(workingPlace->body.getPosition());
	}

	if (body.getGlobalBounds().intersects(GameManager::headquarters->body.getGlobalBounds()))
	{
		SetCurrentState(SEARCH_FOR_RESOURCE);
	}


	if (GetSelected())
	{
		SetCurrentState(IDLE);
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
			//workingPlace->status = workingPlace->EMPTY;
			isWorking = false;
			workingPlace = nullptr;
		}
	}

	//if (GetCurrentState(MOVING) || GetCurrentState(SEARCH_FOR_RESOURCE))
	//{
	//	if (workingPlace != nullptr)
	//	{
	//		/*if (body.getGlobalBounds().intersects(workingPlace->body.getGlobalBounds()))
	//		{
	//			SetCurrentState(GATHERING);
	//			body.setPosition(workingPlace->body.getPosition());
	//			workingPlace->isBeingUsed = true;
	//		}*/
	//	}
	//}

	//if (GetCurrentState(SEARCH_FOR_RESOURCE))
	//{
	//	//if (!workingPlace->isBeingUsed)
	//	//{
	//		MoveSpriteToTarget(workingPlace->body.getPosition());
	//	//}
	//}
	//if (GetCurrentState(GATHERING))
	//{
	//	//if (workingPlace->isFull)
	//	//{
	//		SetCurrentState(UNLOADING);
	//	//}
	//	//else
	//	//{
	//		//workingPlace->GenerateGold();
	//	//}
	//}
	//if (GetCurrentState(UNLOADING))
	//{
	//	if (workingPlace->isEmpty)
	//	{
	//		SetCurrentState(RETURN_TO_BASE);
	//	}
	//	else
	//	{
	//		//workingPlace->DepositGold();
	//	}
	//}
	//if (GetCurrentState(RETURN_TO_BASE))
	//{
	//	//workingPlace->isBeingUsed = false;
	//	MoveSpriteToTarget(GameManager::headquarters->body.getPosition());

	//	if (body.getGlobalBounds().intersects(GameManager::headquarters->body.getGlobalBounds()))
	//	{
	//		SetCurrentState(SEARCH_FOR_RESOURCE);
	//	}

	//}
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

void Worker::MouseRelease()
{
	if (isSelected)
	{
		SetCurrentState(MOVING);
		targetPosition = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());

		for (Buildings* object : GameManager::buildings)
		{
			if (object->GetBuildingType() == object->GOLD_MINE_BUILDING)
			{
				if (object->body.getGlobalBounds().contains(targetPosition))
				{
					Display_Text("MINE TIME");
					workingPlace = static_cast<GoldMine*>(object);
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

void Worker::MoveSpriteToTarget(sf::Vector2f targetPosition)
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

void Worker::AnimateWorker()
{ 
	Animate(currentFrameX, currentFrameY, textureWidth, textureHeight, body, amountOfSprites);
}

void Worker::CheckAnimationState()
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

sf::Sprite& Worker::GetSprite()
{
	return body;
}

sf::Vector2f& Worker::GetPos()
{
	sf::Vector2f pos = body.getPosition();
	return pos;
}
