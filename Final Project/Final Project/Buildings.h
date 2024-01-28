#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "GameObject.h"

class Buildings : public GameObject
{
public:
	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize, float scale);
	void Draw() override;
	
	void UpdateDetectionCircles();

	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites, bool isDead);
	void SetPosition(sf::Vector2f pos);
	void MoveBuilding();


	void SelectBuilding();
	void DeselectBuilding();
	bool CheckIfSelected();

	void PlaceBuilding();
	bool CheckIfPlaced();

	bool canBePlaced = true;

	

private:

	bool isPlaced = false;
	sf::RectangleShape mainRectangle;
	const int numSmallRectangles = 4;

};

