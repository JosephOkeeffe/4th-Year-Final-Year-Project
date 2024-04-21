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

	Animate();
}

void Spaceship::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

//  tier,  _speed,  eggDelay,  amountOfEggs
void Spaceship::SetShipType()
{
	int randomNumber = rand() % 5;

	switch (randomNumber)
	{
	case Spaceship::TIER_1:
		SetupShip(1, 1, 10, 1);
		break;
	case Spaceship::TIER_2:
		SetupShip(2, 1, 9, 2);
		break;
	case Spaceship::TIER_3:
		SetupShip(3, 1, 7, 2);
		break;
	case Spaceship::TIER_4:
		SetupShip(4, 1, 6, 3);
		break;
	case Spaceship::TIER_5:
		SetupShip(5, 1, 5, 4);
		break;
	default:
		SetupShip(1, 1, 10, 1);
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
	float oppositePoint = Global::CELL_SIZE * Global::ROWS_COLUMNS - randomStartingPoint;

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

void Spaceship::Animate()
{

	int frame = m_frameNo;
	m_frameValue += m_frameIncrement;
	m_frameNo = static_cast<int>(m_frameValue);
	m_frameNo = m_frameNo % 5;
	if (frame != m_frameNo)
	{
		body.setTextureRect(sf::IntRect(m_frameNo * 48, 0, 48, 50));
	}
}



