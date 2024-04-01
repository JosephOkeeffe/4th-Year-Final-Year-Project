#pragma once
#include "Enemy.h"
#include "Stats.h"
class Suckler : public Enemy
{
public:

	Suckler(int id);
	void Update() override;
	void Merge();
	void MoveTowardsMergingTarget();

	void ChangeStateToDead();

	void ShootSpit(sf::Vector2f target);
	void ShootShield();

	bool mergeComplete = false;

	sf::Clock shieldTimer;
	sf::Clock spitTimer;
	int shieldFireRate = 20;
	int chanceToSpawnShield = 4;

	int spitFireRate = 3;

};

