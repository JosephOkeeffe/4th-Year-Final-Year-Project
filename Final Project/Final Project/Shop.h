#pragma once
#include <SFML/Graphics.hpp>
#include "Buildings.h"

class Shop : public Buildings
{
public:

	Shop(sf::Vector2f pos);
	void MouseRelease() override;
	void CheckIfSelected();

private:

	int textureWidth = 200;
	int textureHeight = 200;
	int currentFrameX = 0;
	int currentFrameY = 0;
};
