#pragma once
#include <SFML/Graphics.hpp>
#include "Buildings.h"

class Mine : public Buildings
{
public:
	// 286, 261
	// 56, 65
	Mine(sf::Vector2f pos);
	void MouseRelease() override;
	void Update() override;
	void DoIfSelected();

private:

	int textureWidth = 56;
	int textureHeight = 65;
	int currentFrameX = 115;
	int currentFrameY = 0;
};
