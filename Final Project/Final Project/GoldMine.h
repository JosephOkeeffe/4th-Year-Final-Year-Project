#pragma once
#include <SFML/Graphics.hpp>
#include "Buildings.h"
#include "Worker.h"

class Worker;

class GoldMine : public Buildings
{
public:


	enum GoldMineStatus
	{
		EMPTY,
		GENERATE_GOLD,
		DEPOSIT_GOLD,		
	};

	GoldMine(sf::Vector2f pos);
	void Update() override;
	void MouseRelease() override;
	void Draw() override;
	void GenerateGold();
	void DepositGold();

	void AlignMinersPosition();

	GoldMineStatus status;

	std::vector<Worker*> assignedMiners;

	bool isEmpty = false;
	bool isFull = false;
private:

	int textureWidth = 56;
	int textureHeight = 65;
	int currentFrameX = 115;
	int currentFrameY = 0;

	

};
