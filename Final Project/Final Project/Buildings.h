#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Textures.h"
#include "Globals.h"

#include "Characters.h"
#include "Stats.h"

#define Display_Text(x) std::cout << x << "\n";

class Buildings
{
public:

	enum BuildingType
	{
		HEADQUATERS_BUILDING,
		GOLD_MINE_BUILDING,
		URANIUM_EXTRACTOR_BUILDING,
		OIL_EXTRACTOR_BUILDING,
	};

	enum BuildingStatus
	{
		EMPTY,
		GENERATING,
		DEPOSITING,
	};

	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize, float scale);
	virtual void Update();
	virtual void MouseRelease() = 0;
	virtual void Draw();

	void InitDetectionCircle(int radius);
	
	void UpdateDetectionCircle();

	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites);
	void SetPosition(sf::Vector2f pos);
	void MoveBuilding();

	void SelectBuilding();
	void DeselectBuilding();
	bool GetSelectedStatus();

	void PlaceBuilding();
	bool GetPlacedStatus();
	bool CheckIfCanBePlaced(sf::Vector2i cell);
	void ChangeSelectedColour();

	void AlignWorkersPosition(std::vector<Characters*> temp, int texWidth, int texHeight);

	std::vector<Characters*> assignedWorkers;

	void SetBuildingType(BuildingType type);
	BuildingType GetBuildingType();

	void TakeDamage(int damage);

	BuildingType buildingType;
	BuildingStatus status;

	sf::Sprite body;
	sf::Texture texture;
	sf::IntRect textureRect;
	sf::CircleShape detectionCircle;

	sf::RectangleShape background;
	sf::RectangleShape resource;

	sf::Text resourceText;
	float amount = 0;
	float detectionRadius = 100.0f;

	sf::Vector2f barSize{ 100, 10 };
	float maxWidth = barSize.x + 1;
	float fillSpeed = 5;
	float currentWidth = 0;
	sf::Clock clock;
	sf::Time deltaTime;

	bool isSelected = false;
	
	int animationCount = 0;
	int m_frameNo{ 0 };
	float m_frameValue{ 0.0f };
	float animationSpeed{ 0.2 };
	int playerAnimation = 0;

	sf::Clock redTimer;
	ParticleSystem particleSystem;

private:

	bool canBePlaced = true;
	bool isPlaced = false;
	sf::RectangleShape mainRectangle;
	const int numSmallRectangles = 4;

	Stats stats{ 25, 0, 0 };



	

};

