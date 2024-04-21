#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Textures.h"
#include "Globals.h"
#include "GameManager.h"
#include "Egg.h"


class Spaceship
{
public:

	enum SpaceshipType
	{
		TIER_1,
		TIER_2,
		TIER_3,
		TIER_4,
		TIER_5,
	};
	Spaceship();
	void Init();
	void Update();
	void Draw(sf::RenderWindow& window);
	void SetShipType();
	void PickStartPointAndEndPoint();
	void SetupShip(int tier, float _speed, float eggDelay, int amountOfEggs);
	void Move();
	void SpawnEgg();

	void Animate();

	SpaceshipType spaceshipType;

	sf::Sprite body;
	sf::Texture texture;
	float speed;
	sf::Vector2f startPos;
	sf::Vector2f endPos;

	int startX = 0;
	int startY = 0;
	int textureWidth = 48;
	int textureHeight = 50;

	float eggSpawnDelay;
	int eggCounter;
	int MAX_EGGS;
	bool allEggsSpawned;
	sf::Clock eggSpawnTimer;

	int m_frameNo{ 0 }; 
	float m_frameValue{ 0.0f };
	float m_frameIncrement{ 0.07 };

private:

};

