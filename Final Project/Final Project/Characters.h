#pragma once
#include <SFML/Graphics.hpp>
#include "Behaviour.h"
#include "Textures.h"
#include "GameManager.h"
#include "HUD.h"

class Characters
{
public:

	enum State
	{
		IDLE,
		MOVING,
		FORMATION_MOVING,
		ATTACKING,
		DEAD,
	};

	enum AnimationState
	{
		IDLE_ANIM,
		RUNNING_ANIM,
		ATTACKING_ANIM,
		DEAD_ANIM,

	};

	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize);
	virtual void Update();
	virtual void MouseRelease();
	void Draw();

	void InitDetectionCircle(int radius);

	void UpdateDetectionCircle();
	void UpdateCharacters();
	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites);
	void ChangeAnimation();
	
	void SetPosition(sf::Vector2f pos);
	void MoveCharacter();
	void SelectCharacter();
	void DeselectCharacter();
	bool GetSelected();
	void ChangeSelectedColour();
	void CalculateAngle(sf::Sprite& target);
	void FlipSpriteWithDirection(sf::Vector2f& direction, sf::Sprite& sprite);
	void FlipSprite();
	bool CheckCurrentState(State stateToCheck);
	void SetCurrentState(State stateToChange);
	
	AnimationState animationState = IDLE_ANIM;
	State currentState = IDLE;

	Behaviour* behaviour;

	sf::Sprite body;
	sf::Texture texture;
	sf::IntRect textureRect;
	sf::CircleShape detectionCircle;

	sf::Vector2f direction = { 0, 1 };
	sf::Vector2f targetPosition;
	sf::CircleShape tileDetectionCircle;
	
	bool isSelected = false;
	//bool isMoving = false;
	bool isFormationMoving = false;
	//bool isDead = false;

	float detectionRadius = 100.0f;
	float tileDetectionRadius = 10;

	float defaultMoveSpeed = 2.0f;
	float currentMoveSpeed = defaultMoveSpeed;

	// Animation
	int animationCount = 0;
	int m_frameNo{ 0 };
	float m_frameValue{ 0.0f }; 
	float animationSpeed{ 0.2 };
	int playerAnimation = 0;

private:
};

