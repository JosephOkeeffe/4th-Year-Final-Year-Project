#pragma once
#include <SFML/Graphics.hpp>
#include "Buildings.h"

class Mine : public Buildings
{
public:
	Mine(sf::Vector2f pos);
	void Update() override;
	void MouseRelease() override;
	void DoIfSelected();

private:

	int textureWidth = 56;
	int textureHeight = 65;
	int currentFrameX = 115;
	int currentFrameY = 0;
};
