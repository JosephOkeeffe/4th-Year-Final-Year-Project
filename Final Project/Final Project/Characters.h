#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "GameManager.h"
#include "HUD.h"
#include "Particles.h"
#include "Projectile.h"
#include "Stats.h";

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
	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites);

	void ChangeSpeedDependingOnTiles();
	
	void SetPosition(sf::Vector2f pos);
	void MoveCharacter();
	void MoveIntoFormation();
	void SelectCharacter();
	void DeselectCharacter();
	bool GetSelected();
	void ChangeSelectedColour();
	void CalculateAngle(sf::Sprite& target);
	void FlipSpriteWithDirection(sf::Vector2f& direction, sf::Sprite& sprite);
	void FlipSprite();
	bool GetCurrentState(State stateToCheck);
	void SetCurrentState(State stateToChange);


	
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

	float detectionRadius = 100.0f;
	float tileDetectionRadius = 10;

	float defaultMoveSpeed = 1.0f;
	float currentMoveSpeed = defaultMoveSpeed;

	// Animation
	int animationCount = 0;
	int m_frameNo{ 0 };
	float m_frameValue{ 0.0f }; 
	float animationSpeed{ 0.2 };
	int playerAnimation = 0;

	Tile* startTile;
	Tile* goalTile;
	std::vector<Tile*> path;
	ParticleSystem particleSystem;

	int pathFindingXOffset = 50;
	int pathFindingYOffset = 40;

	sf::Vector2f distanceFromLeader;

	bool hasFlipped = false;

	std::vector<Projectile> projectiles;

	Stats stats{ 10, 1, 1 };
private:


};

