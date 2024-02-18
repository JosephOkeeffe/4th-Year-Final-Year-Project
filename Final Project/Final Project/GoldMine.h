#pragma once
#include <SFML/Graphics.hpp>
#include "Buildings.h"
#include "Miner.h"

class Miner;

class GoldMine : public Buildings
{
public:

	GoldMine(sf::Vector2f pos);
	void Update() override;
	void MouseRelease() override;
	void GenerateGold();
	void DepositGold();

private:

	int textureWidth = 56;
	int textureHeight = 65;
	int currentFrameX = 115;
	int currentFrameY = 0;

	

};
