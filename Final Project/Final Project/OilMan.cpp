#include "OilMan.h"

OilMan::OilMan()
{
	srand(time(nullptr));

	textureRect = { 0, 0, textureWidth, textureHeight };
	animationSpeed = 0.08;
	Init(Textures::GetInstance().GetTexture("oil-man"), body, textureRect);
	body.setScale(defaultScale, defaultScale);
	characterType = OIL_MAN;
}

void OilMan::MouseRelease()
{
	Characters::MouseRelease();

	if (isSelected)
	{
		for (Buildings* object : GameManager::buildings)
		{
			if (object->GetBuildingType() == object->GOLD_MINE_BUILDING)
			{
				if (object->body.getGlobalBounds().contains(targetPosition))
				{
					Display_Text("MINE TIME");
					workingPlace = static_cast<OilExtractor*>(object);
				}

			}
		}
	}
}

void OilMan::Update()
{
	if (GetCurrentState(DEAD))
	{
		body.setTextureRect(sf::IntRect{ 488, 0, 56, 68});
		StopWorking();
		
	}

	if (!GetCurrentState(DEAD))
	{
		Characters::Update();
		CheckAnimationState();
		Animate(currentFrameX, currentFrameY, textureWidth, textureHeight, body, amountOfSprites);
		RemoveFromWorkPlace();
		UpdateWorkingStates();
	}
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
	if (GetCurrentState(IDLE))
	{
		StopWorking();
	}

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
			particlePos.y = body.getPosition().y - 50;
			particleTimer.restart();
			particleSystem.AddSpriteParticle(particlePos, randomVelocity, sf::Color::White, Textures::GetInstance().GetTexture("gold-icon"), 200, 0.3, 7);
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

	if (body.getGlobalBounds().intersects(GameManager::headquarters->body.getGlobalBounds()) && workingPlace != nullptr)
	{
		SetCurrentState(SEARCH_FOR_RESOURCE);
	}
}


void OilMan::MoveSpriteToTarget(sf::Vector2f targetPosition)
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

void OilMan::StopWorking()
{
	body.setScale(defaultScale, defaultScale);

	if (workingPlace != nullptr)
	{
		if (body.getGlobalBounds().intersects(workingPlace->body.getGlobalBounds()))
		{
			body.setPosition(body.getPosition().x, body.getPosition().y + 130);
		}
		isWorking = false;
	}
	workingPlace = nullptr;
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