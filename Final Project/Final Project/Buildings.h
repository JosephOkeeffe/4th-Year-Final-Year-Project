#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Textures.h"
#include "Globals.h"

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

	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize, float scale);
	virtual void Update();
	virtual void MouseRelease();
	virtual void Draw();

	void InitDetectionCircle(int radius);
	
	void UpdateBuildings();
	void UpdateDetectionCircle();

	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites);
	void SetPosition(sf::Vector2f pos);
	void MoveBuilding();

	void SelectBuilding();
	void DeselectBuilding();
	bool CheckIfSelected();

	void PlaceBuilding();
	bool GetPlacedStatus();
	bool CheckIfCanBePlaced(sf::Vector2i cell);
	void ChangeSelectedColour();

	void SetBuildingType(BuildingType type);
	BuildingType GetBuildingType();

	BuildingType buildingType;

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

private:

	bool canBePlaced = true;
	bool isPlaced = false;
	sf::RectangleShape mainRectangle;
	const int numSmallRectangles = 4;

	

};

