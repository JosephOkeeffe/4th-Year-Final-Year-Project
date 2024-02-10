#pragma once
#include <SFML/Graphics.hpp>
#include "Buildings.h"

class GoldMine : public Buildings
{
public:
	GoldMine(sf::Vector2f pos);
	void Update() override;
	void MouseRelease() override;
	void Draw() override;
	void GenerateGold();
	void DepositGold();

	bool isBeingUsed = false;
	bool isEmpty = false;
	bool isFull = false;
private:

	int textureWidth = 56;
	int textureHeight = 65;
	int currentFrameX = 115;
	int currentFrameY = 0;


};
