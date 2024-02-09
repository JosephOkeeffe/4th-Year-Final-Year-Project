#include "Worker.h"
#include "Globals.h"
#include "Buildings.h"

Worker::Worker()
{
	srand(time(nullptr));
	int randomNuber = rand() % 5;

	if (randomNuber == 0)
	{
		Init(Textures::GetInstance().GetTexture("worker"), body, textureRect);
	}
	else if (randomNuber == 1)
	{
		Init(Textures::GetInstance().GetTexture("worker1"), body, textureRect);
	}

	textureRect = { 0, 0, textureWidth, textureHeight };

	body.setScale(1, 1);
	animationSpeed = 0.08;

}

void Worker::Update()
{
	UpdateCharacters();
	CheckAnimationState();
	AnimateWorker();

	if (GetCurrentState(SEARCH_FOR_RESOURCE))
	{
		if (body.getGlobalBounds().intersects(workingPlace->body.getGlobalBounds()))
		{
			SetCurrentState(GATHERING);
			body.setPosition(workingPlace->body.getPosition());
		}
	}
}

void Worker::MouseRelease()
{
	if (isSelected)
	{
		currentState = MOVING;
		targetPosition = Global::GetMousePos(*GameManager::GetWindow());

		for (Buildings* object : GameManager::buildings)
		{
			if (object->GetBuildingType() == object->GOLD_MINE)
			{

				if (object->body.getGlobalBounds().contains(targetPosition))
				{
						Display_Text("MINE TIME");
						SetCurrentState(SEARCH_FOR_RESOURCE);
						workingPlace = object;
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
	else if (GetCurrentState(UNLOADING) || GetSelected())
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
