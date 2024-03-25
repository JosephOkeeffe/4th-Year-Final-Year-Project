#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Textures.h"
#include "Globals.h"
#include "GameManager.h"
#include "Characters.h"

#define Display_Text(x) std::cout << x << "\n";

class Enemy
{
public:

	enum CurrentState
	{
		IDLE,
		WALKING,
		MERGING,
		ATTACKING,
		DEAD 
	};

	enum EnemyType
	{
		SUCKLER_MALE,
		SUCKLER_FEMALE,
		BIG_SUCKLER,
		GUMPER,
		BIG_GUMPER
	};

	//enum MergingState
	//{
	//	NONE,
	//	MERGER,
	//	GETTING_MERGED
	//};

	EnemyType enemyType;
	//MergingState mergingState = NONE;

	void Init(sf::Texture& _texture);
	void Draw();
	virtual void Update();
	void SetPosition(sf::Vector2f pos);

	void CheckIfAnythingIsWithinRadius();
	void ChangeState(CurrentState newState);
	void UpdateStates();
	bool GetCurrentState(CurrentState checkState);
	bool IsCharacterWithinRadius(sf::Sprite& target);


	int id = 0;
	bool hasMerged = false;
	CurrentState state = IDLE;
	

	sf::Sprite body;
	sf::Texture texture;
	sf::CircleShape detectionCircle;

	float detectionRadius = 100.0f;    

	Enemy* target;

	std::vector <Enemy*> enemiesInRadius;

	bool toBeDeleted = false;

	bool hasFoundMerge = false;


	sf::Vector2f targetPos;
private:
};

