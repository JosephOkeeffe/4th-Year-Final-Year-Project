#pragma once
#include <SFML/Graphics.hpp>
#include "Buildings.h"
class Base : public Buildings
{
public:
	Base(sf::Vector2f pos);
	void MouseRelease() override;
	void Update() override;
	void DoIfSelected();
private:

	int textureWidth = 57;
	int textureHeight = 76;
	int currentFrameX = textureWidth * 2;
	int currentFrameY = 0;
	int amountOfSprites = 2;
};

