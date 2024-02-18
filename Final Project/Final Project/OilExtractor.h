#pragma once
#include <SFML/Graphics.hpp>
#include "Buildings.h"
#include "OilMan.h"

class OilMan;

class OilExtractor : public Buildings
{
public:
	OilExtractor(sf::Vector2f pos);
	void Update() override;
	void MouseRelease() override;
	void GenerateOil();
	void DepositOil();

private:
	int currentFrameX = 56;
	int currentFrameY = 66;
	int textureWidth = 55;
	int textureHeight = 62;
	int amountOfSprites = 7;


};
