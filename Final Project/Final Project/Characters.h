#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "GameManager.h"
#include "HUD.h"
#include "ParticleSystem.h"
#include "Stats.h";
#include "Enemy.h"
#include "ProjectileFactory.h"

class Particles;
class ParticleSystem;

class Characters
{
public:

	enum CharacterType
	{
		WARRIOR,
		ARCHER,
		MINER,
		OIL_MAN,
		HAZMAT_MAN
	};

	enum State
	{
		IDLE,
		MOVING,
		ATTACKING,
		DEAD,

		SEARCH_FOR_RESOURCE,
		GATHERING,
		INVENTORY_FULL,
		RETURN_TO_BASE,
		UNLOADING,
	};

	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize);
	virtual void Update();
	virtual void MouseRelease();
	virtual void Draw();

	void InitDetectionCircle(int radius);

	void UpdateDetectionCircle();
	virtual void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites);

	void ChangeSpeedDependingOnTiles();
	
	void SetPosition(sf::Vector2f pos);
	void MoveCharacter();
	void MoveIntoFormation();
	void SelectCharacter();
	void DeselectCharacter();
	bool GetSelected();
	void ChangeSelectedColour();
	bool IsEnemyInAttackRadius(sf::Sprite& target);
	void FlipSpriteWithDirection(sf::Vector2f& direction, sf::Sprite& sprite);
	void FlipSprite();
	bool GetCurrentState(State stateToCheck);
	void SetCurrentState(State stateToChange);

	void FindClosestEnemy();
	void StartAttackingClosestEnemy();
	void TakeDamage(int damage);
	void ApplyKnockback(sf::Vector2f knockbackDirection, float knockbackDistance);
	void UpdateProjectiles();
	void ProjectilesCollideWithEnemies();

	void ChangeStateToDead();
	
	State currentState = IDLE;
	CharacterType characterType;

	sf::Sprite body;
	sf::Texture texture;
	sf::IntRect textureRect;
	sf::CircleShape detectionCircle;

	sf::Vector2f direction = { 0, 1 };
	sf::Vector2f velocity;
	sf::Vector2f targetPosition;
	sf::CircleShape tileDetectionCircle;

	bool isPartOfFormation = false;
	bool isSelected = false;
	bool isMovingIntoFormation = false;
	bool isFollowingLeader = false;
	bool isWorking = false;

	float detectionRadius = 200.0f;
	float tileDetectionRadius = 10;

	float defaultMoveSpeed = 1.0f;
	float currentMoveSpeed = defaultMoveSpeed;

	// Animation
	int animationCount = 0;
	int m_frameNo{ 0 };
	float m_frameValue{ 0.0f }; 
	float animationSpeed;
	int playerAnimation = 0;

	// Path
	Tile* startTile;
	Tile* goalTile;
	std::vector<Tile*> path;
	int pathFindingXOffset = 50;
	int pathFindingYOffset = 40;
	sf::Vector2f distanceFromLeader;
	bool hasFlipped = false;

	// Particles
	ParticleSystem particleSystem;

	// Projectiles
	ProjectileFactory factory;
	std::vector<Projectile*> projectiles;
	sf::Clock reloadTimer;
	float reloadDelay = 3;

	sf::Clock redTimer;

	Enemy* closestEnemy;
	float closestEnemyDistance = INT_MAX;

	Stats stats{ 5, 1, 1.5 };
private:


};

