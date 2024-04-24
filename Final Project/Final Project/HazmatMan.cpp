#include "HazmatMan.h"
#include "Globals.h"
#include "Buildings.h"

HazmatMan::HazmatMan()
{
	textureRect = { 0, 0, textureWidth, textureHeight };
	animationSpeed = 0.1 ;
	Init(Textures::GetInstance().GetTexture("hazmat-man"), body, textureRect);
	body.setScale(defaultScale, defaultScale);
	characterType = HAZMAT_MAN;
}

void HazmatMan::MouseRelease()
{
	Characters::MouseRelease();

	if (isSelected)
	{
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
}

void HazmatMan::Update()
{

	if (GetCurrentState(DEAD) && m_frameNo != amountOfSprites - 1)
	{
		Animate(currentFrameX, currentFrameY, textureWidth, textureHeight, body, amountOfSprites);
		StopWorking();
	}

	if (!GetCurrentState(DEAD))
	{
		Characters::Update();
		CheckAnimationState();
		Animate(currentFrameX, currentFrameY, textureWidth, textureHeight, body, amountOfSprites);
		UpdateWorkingStates();
	}
	
}

void HazmatMan::UpdateWorkingStates()
{
	if (GetSelected())
	{
		SetCurrentState(IDLE);
	}

	if (GetCurrentState(IDLE))
	{
		StopWorking();
	}

	if (workingPlace != nullptr)
	{
		if (body.getGlobalBounds().intersects(workingPlace->body.getGlobalBounds()) && workingPlace->GetPlacedStatus() && isWorking)
		{
			if (workingPlace->status == workingPlace->GENERATING)
			{
				body.setScale(1.2, 1.2);
				SetCurrentState(GATHERING);
			}
			else if (workingPlace->status == workingPlace->DEPOSITING)
			{
				SetCurrentState(UNLOADING);
			}
			else if (workingPlace->status == workingPlace->EMPTY && GetCurrentState(UNLOADING))
			{
				body.setScale(defaultScale, defaultScale);
				SetCurrentState(RETURN_TO_BASE);
			}
		}
	}

	if (GetCurrentState(GATHERING))
	{
		sf::Vector2f randomVelocity = Global::CalculateVelocityUsingAnglesForParticles(-22.5, 22.5, body, 95);

		if (particleTimer.getElapsedTime().asMilliseconds() >= 100)
		{
			sf::Vector2f particlePos;
			particlePos.x = body.getPosition().x;
			particlePos.y = body.getPosition().y - 40;
			particleTimer.restart();
			particleSystem.AddSpriteParticle(particlePos, randomVelocity, sf::Color::White, Textures::GetInstance().GetTexture("goop"), 200, 0.3, 7);
		}
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

	if (body.getGlobalBounds().intersects(GameManager::headquarters->body.getGlobalBounds()) && workingPlace != nullptr && !GetCurrentState(SEARCH_FOR_RESOURCE))
	{
		SetCurrentState(SEARCH_FOR_RESOURCE);
		GameManager::inventory.AddItem("Uranium", workingPlace->resourcePerRun);
	}
}

void HazmatMan::MoveSpriteToTarget(sf::Vector2f targetPosition)
{
	if (path.empty())
	{
		int startX = body.getPosition().x / Global::CELL_SIZE;
		int startY = body.getPosition().y / Global::CELL_SIZE;

		int endX = targetPosition.x / Global::CELL_SIZE;
		int endY = targetPosition.y / Global::CELL_SIZE;

		Tile* startTile = &GameManager::tiles[startX][startY];
		Tile* goalTile = &GameManager::tiles[endX][endY];

		path = GameManager::FindPath(startTile, goalTile, true);
	}

	if (!path.empty())
	{
		Tile* nextTile = path.front();

		sf::Vector2f direction = nextTile->tile.getPosition() - body.getPosition();
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
			body.setPosition(nextTile->tile.getPosition());
			path.erase(path.begin());

			if (!path.empty())
			{
				targetPosition = path.front()->tile.getPosition();
			}
		}
	}
}

void HazmatMan::CheckAnimationState()
{
	if (GetCurrentState(IDLE) && !GetSelected())
	{
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
		currentFrameX = 50;
		currentFrameY = 241;
		textureWidth = 50;
		textureHeight = 46;
		amountOfSprites = 16 ;
	}
}

void HazmatMan::StopWorking()
{
	body.setScale(defaultScale, defaultScale);

	if (workingPlace != nullptr)
	{
		if (body.getGlobalBounds().intersects(workingPlace->body.getGlobalBounds()))
		{
			body.setPosition(body.getPosition().x, body.getPosition().y + 200);
		}
		isWorking = false;
	}
	workingPlace = nullptr;
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

