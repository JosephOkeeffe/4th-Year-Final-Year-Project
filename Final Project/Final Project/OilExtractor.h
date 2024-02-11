#pragma once
#include <SFML/Graphics.hpp>
#include "Buildings.h"

class OilExtractor : public Buildings
{
public:
	OilExtractor(sf::Vector2f pos);
	void Update() override;
	void MouseRelease() override;
	void Draw() override;
	void GenerateOil();
	void DepositOil();

	bool isBeingUsed = false;
	bool isEmpty = false;
	bool isFull = false;
private:
	int currentFrameX = 56;
	int currentFrameY = 66;
	int textureWidth = 55;
	int textureHeight = 62;
	int amountOfSprites = 7;


};
