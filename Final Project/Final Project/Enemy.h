#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Textures.h"
#include "Globals.h"
#include "GameManager.h"
#include "Characters.h"
#include "ParticleSystem.h"


#include "ProjectileFactory.h"

#define Display_Text(x) std::cout << x << "\n";

class Enemy
{
public:

	enum CurrentState
	{
		IDLE,
		MOVING,
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


	EnemyType enemyType;

	void Init(sf::Texture& _texture);
	void Draw();
	virtual void Update();
	void SetPosition(sf::Vector2f pos);

	bool IsCharacterWithinRadius(sf::Sprite& target);
	void CheckIfAnythingIsWithinRadius();
	std::vector<Characters*> GetUnitsWithinRadius();
	Characters* FindClosestEnemy();
	void ChangeState(CurrentState newState);
	void UpdateStates();
	bool GetCurrentState(CurrentState checkState);

	void Move();
	void StartWandering();

	void TakeDamage(int damage);
	void ApplyKnockback(sf::Vector2f knockbackDirection, float knockbackDistance);
	void DeleteEnemy();



	int id = 0;
	CurrentState state = IDLE;
	
	sf::Sprite body;
	sf::Texture texture;
	sf::CircleShape enemyDetectionCircle;
	sf::CircleShape wanderCircle;

	float detectionRadius = 150.0f;    
	float wanderRadius = 300.0f;    

	Enemy* target;
	std::vector <Enemy*> enemiesInRadius;

	bool toBeDeleted = false;
	bool hasMerged = false;
	bool hasFoundMerge = false;

	sf::Clock redTimer;
	sf::Vector2f targetPos;

	ProjectileFactory factory;
	std::vector<Projectile*> projectiles; 
	ParticleSystem particleSystem;

	// Path
	sf::Vector2f targetPosition;
	sf::Vector2f direction;
	sf::Vector2f velocity;
	Tile* startTile;
	Tile* goalTile;
	std::vector<Tile*> path;
	int pathFindingXOffset = 50;
	int pathFindingYOffset = 40;
	float defaultMoveSpeed = 1.0f;
	float currentMoveSpeed = defaultMoveSpeed;

	sf::Clock wanderTimer;

	sf::Vector2i currentTilePos;
	Tile* currentTile;
	bool readyToMove = false;

	Stats stats{ 5, 1, 1 };

private:
};

