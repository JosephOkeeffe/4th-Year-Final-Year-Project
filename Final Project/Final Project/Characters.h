//#pragma once
//#include <SFML/Graphics.hpp>
//#include "Behaviour.h"
//#include "Textures.h"
//#include "GameObject.h"
//
//class Characters : public GameObject
//{
//public:
//
//	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize);
//	void Draw() override;
//	void MouseRelease() override;
//
//	void UpdateDetectionCircles();
//
//	void SelectCharacter();
//
//	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites, bool isDead);
//	void CheckIfSelected();
//	void CalculateAngle(sf::Sprite& target);
//	void FlipSpriteWithDirection(sf::Vector2f& direction, sf::Sprite& sprite);
//	void FlipSprite();
//	void SetPosition(sf::Vector2f pos);
//
//	sf::Vector2f direction;
//	sf::Vector2f targetPosition;
//	void MoveCharacter();
//
//	
//
//	sf::CircleShape tileDetectionCircle;
//	float tileDetectionRadius = 10;
//
//	Behaviour* behaviour;
//
//	int animationCount = 0;
//	int m_frameNo{ 0 };
//	float m_frameValue{ 0.0f }; 
//	float animationSpeed{ 0.2 };
//	int playerAnimation = 0;
//	bool isDeadAnimationPending = false;
//
//	bool isMoving = false;
//	bool isFormationMoving = false;
//	bool isDead = false;
//
//	float defaultMoveSpeed = 2.0f;
//	float currentMoveSpeed = defaultMoveSpeed;
//
//};
//
