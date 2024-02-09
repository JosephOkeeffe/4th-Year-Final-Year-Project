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
		HEADQUATERS,
		GOLD_MINE,
	};

	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize, float scale);
	virtual void Update();
	virtual void MouseRelease();
	void Draw();

	void InitDetectionCircle(int radius);
	
	void UpdateBuildings();
	void UpdateDetectionCircle();

	//void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites, bool isDead);
	void SetPosition(sf::Vector2f pos);
	void MoveBuilding();

	void SelectBuilding();
	void DeselectBuilding();
	bool CheckIfSelected();

	void PlaceBuilding();
	bool CheckIfPlaced();
	bool CheckIfCanBePlaced(sf::Vector2f mousePos, sf::Vector2i cell);
	void ChangeSelectedColour();

	void SetBuildingType(BuildingType type);
	BuildingType GetBuildingType();

	BuildingType buildingType;

	sf::Sprite body;
	sf::Texture texture;
	sf::IntRect textureRect;
	sf::CircleShape detectionCircle;
	float detectionRadius = 100.0f;

	
	bool isSelected = false;
	

private:

	bool canBePlaced = true;
	bool isPlaced = false;
	sf::RectangleShape mainRectangle;
	const int numSmallRectangles = 4;

	

};

