#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "GameObject.h"

class Buildings : public GameObject
{
public:
	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize, float scale);
	void Draw() override;
	void Update() override;
	void MouseUp() override;

	void SelectBuilding();
	//void CheckIfSelected();

	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites, bool isDead);
	void SetPosition(sf::Vector2f pos);

	bool GetSelected();


private:

	bool isSelected = false;
	sf::RectangleShape mainRectangle;
	const int numSmallRectangles = 4;

};

