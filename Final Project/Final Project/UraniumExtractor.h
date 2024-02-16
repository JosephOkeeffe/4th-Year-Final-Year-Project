#pragma once
#include <SFML/Graphics.hpp>
#include "Buildings.h"
class UraniumExtractor : public Buildings
{
public:

	UraniumExtractor(sf::Vector2f pos);
	void Update() override;
	void MouseRelease() override;
	void Draw() override;
	void GenerateUranium();
	void DepositUranium();

	bool isBeingUsed = false;
	bool isEmpty = false;
	bool isFull = false;
private:
	int currentFrameX = 56;
	int currentFrameY = 66;
	int textureWidth = 163;
	int textureHeight = 132;

};

