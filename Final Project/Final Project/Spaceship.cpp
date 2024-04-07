#include "Spaceship.h"

Spaceship::Spaceship()
{
	Init();
}

void Spaceship::Init()
{
	SetShipType();

	body.setTexture(Textures::GetInstance().GetTexture("spaceship"));
	body.setTextureRect({ startX, startY , textureWidth, textureHeight });
	body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
	body.setScale(3, 3);

	PickStartPointAndEndPoint();
	eggSpawnTimer.restart();
	allEggsSpawned = false;
	eggCounter = 0;
}

void Spaceship::Update()
{
	if (Global::Distance(body.getPosition(), endPos) > 100)
	{
		Move();
		if (eggCounter >= MAX_EGGS)
		{
			allEggsSpawned = true;
		}

		// Spawn Egg
		if (eggSpawnTimer.getElapsedTime().asSeconds() > eggSpawnDelay && !allEggsSpawned)
		{
			SpawnEgg();
			eggSpawnTimer.restart();
		}
	}
}

void Spaceship::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Spaceship::SetShipType()
{
	int randomNumber = rand() % 5;

	switch (randomNumber)
	{
	case Spaceship::TIER_1:
		SetupShip(1, 2, 20, 1);
		break;
	case Spaceship::TIER_2:
		SetupShip(2, 2, 18, 2);
		break;
	case Spaceship::TIER_3:
		SetupShip(3, 2, 16, 2);
		break;
	case Spaceship::TIER_4:
		SetupShip(4, 2, 16, 3);
		break;
	case Spaceship::TIER_5:
		SetupShip(5, 2, 10, 4);
		break;
	default:
		SetupShip(1, 2, 20, 1);
		break;
	}
}

void Spaceship::PickStartPointAndEndPoint()
{
	float offset = 200;
	float minSpawnPos = -offset;
	float maxSpawnPos = (Global::CELL_SIZE * Global::ROWS_COLUMNS) + offset;

	int rangeSize = (offset)-((Global::CELL_SIZE * Global::ROWS_COLUMNS) - offset) + 1;
	float randomStartingPoint = rand() % rangeSize + offset;
	float oppositePoint = 5000 - randomStartingPoint;

	int side = rand() % 4;

	switch (side)
	{
	case 0: // Top 
		startPos.x = randomStartingPoint;
		startPos.y = minSpawnPos;
		endPos.x = oppositePoint;
		endPos.y = maxSpawnPos;
		break;
	case 1: // Right 
		startPos.x = maxSpawnPos;
		startPos.y = randomStartingPoint;
		endPos.x = minSpawnPos;
		endPos.y = oppositePoint;
		break;
	case 2: // Bottom 
		startPos.x = randomStartingPoint;
		startPos.y = maxSpawnPos;
		endPos.x = oppositePoint;
		endPos.y = minSpawnPos;
		break;
	case 3: // Left 
		startPos.x = minSpawnPos;
		startPos.y = randomStartingPoint;
		endPos.x = maxSpawnPos;
		endPos.y = oppositePoint;
		break;
	}
	body.setPosition(startPos);
}

void Spaceship::SetupShip(int tier, float _speed, float eggDelay, int amountOfEggs)
{
	spaceshipType = static_cast<SpaceshipType>(tier);
	speed = _speed;
	startX = textureWidth * (tier - 1);
	eggSpawnDelay = eggDelay;
	MAX_EGGS = amountOfEggs;
}

void Spaceship::Move()
{
	sf::Vector2f direction = endPos - startPos;

	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length != 0)
	{
		direction /= length;
	}

	body.move(direction * speed);
	float angle = atan2(direction.y, direction.x) * 180 / Global::PI;
	body.setRotation(angle + 90);
}

void Spaceship::SpawnEgg()
{
	sf::Vector2i tilePos = Global::ConvertPositionToCell(body.getPosition());

	if ((tilePos.x < 1 || tilePos.x > Global::ROWS_COLUMNS) || (tilePos.y < 1 || tilePos.y > Global::ROWS_COLUMNS)) { return; }

	if (GameManager::tiles[tilePos.x][tilePos.y].GetTileType() != TileType::OBSTACLE)
	{
		std::cout << "Spawn Egg on tile: " << tilePos.x << ", " << tilePos.y << "\n";
		Egg* egg = new Egg(body.getPosition(), eggSpawnDelay, spaceshipType);
		GameManager::eggs.push_back(egg);
		eggCounter++;
		std::cout << eggCounter << " of  " << MAX_EGGS << " eggs used up\n";

	}

}



