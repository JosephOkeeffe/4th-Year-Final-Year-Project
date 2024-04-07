#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <random>
#include "Textures.h"
#include "Globals.h"
#include "GameManager.h"
#include "Characters.h"
#include "ParticleSystem.h"
#include "Buildings.h"
#include "ItemManager.h"
#include "Shader.h"


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

	enum DropTable
	{
		GOLD_RESOURCE_DROP,
		OIL_RESOURCE_DROP,
		URANIUM_RESOURCE_DROP,
		MUSHED_SUCKLER_HEAD_DROP,
		SUCKLER_TENTACLE_DROP,
		PRESERVED_SUCKLER_SPIT_DROP
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
	Buildings* FindClosestBuilding();
	std::vector<sf::Vector2f> GetUnitsToMoveTowardsWithinWanderRadius();
	std::vector<sf::Vector2f> GetMergeTargetsToMoveTowardsWithinWanderRadius();
	std::vector<sf::Vector2f> GetBuildingsToMoveTowardsWithinWanderRadius();
	void ChangeState(CurrentState newState);
	void UpdateStates();
	bool GetCurrentState(CurrentState checkState);



	void Move();
	void MoveTowardsPointOfInterest();
	void StartWandering();

	void TakeDamage(int damage);
	void ApplyKnockback(sf::Vector2f knockbackDirection, float knockbackDistance);
	void ProjectilesCollideWithPlayerUnits();
	void ProjectilesCollideWithPlayerBuildings();
	void MakeWalkingTrail();
	void DeleteEnemy();
	void ChangeStateToDead();

	void GetRandomItemFromDropTable();
	void DropItem(std::string& itemName);
	void UnitsCanCollectItemDrop();
	



	int id = 0;
	CurrentState state = IDLE;
	
	sf::Sprite body;
	sf::Texture texture;
	sf::CircleShape enemyDetectionCircle;
	sf::CircleShape wanderCircle;

	sf::RectangleShape itemDropSprite;
	Item* droppedItem;
	bool isItemCollected = false;

	float detectionRadius = 150.0f;    
	float wanderRadius = 500.0f;    

	Enemy* target;
	std::vector <Enemy*> enemiesInRadius;

	bool toBeDeleted = false;
	bool hasMerged = false;
	bool hasFoundMerge = false;

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

	// Timers
	bool isReadyToAttack = true;
	sf::Clock attackingStateChangeTimer;
	sf::Clock wanderTimer;
	sf::Clock redTimer;
	sf::Clock walkingTrailTimer;

	sf::Vector2i currentTilePos;
	Tile* currentTile;
	bool readyToMove = false;

	std::vector<sf::Vector2f> pointsOfInterest;

	Stats stats{ 1, 1, 1 };

	Shader shader;

private:
};

