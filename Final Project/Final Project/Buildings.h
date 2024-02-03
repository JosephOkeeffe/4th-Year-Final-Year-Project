#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Textures.h"

#define Display_Text(x) std::cout << x << "\n";

class Buildings
{
public:
	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize, float scale);
	virtual void Update();
	virtual void MouseRelease();
	void Draw();

	void InitDetectionCircle(int radius);
	
	void UpdateDetectionCircles();

	//void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites, bool isDead);
	void SetPosition(sf::Vector2f pos);
	void MoveBuilding();

	void CheckForCollisions();

	void SelectBuilding();
	void DeselectBuilding();
	bool CheckIfSelected();

	void PlaceBuilding();
	bool CheckIfPlaced();

	sf::Sprite body;
	sf::Texture texture;
	sf::IntRect textureRect;
	sf::CircleShape detectionCircle;
	float detectionRadius = 100.0f;

	bool canBePlaced = true;
	bool isSelected = false;
	

private:

	bool isPlaced = false;
	sf::RectangleShape mainRectangle;
	const int numSmallRectangles = 4;

	

};

