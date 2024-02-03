#pragma once
#include <SFML/Graphics.hpp>
#include "Buildings.h"
#include "BuildingUI.h"
class Base : public Buildings 
{
public:
	Base(sf::Vector2f pos);
	void Update() override;
	void MouseRelease() override;
	void DoIfSelected();
private:

	int textureWidth = 57;
	int textureHeight = 76;
	int currentFrameX = textureWidth * 2;
	int currentFrameY = 0;
	int amountOfSprites = 2;
};

