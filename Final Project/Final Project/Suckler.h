#pragma once
#include "Enemy.h"
class Suckler : public Enemy
{
public:

	enum MyEnum
	{

	};
	Suckler(int id);
	void Update() override;


	bool mergeComplete = false;
	//Enemy* target;
};

