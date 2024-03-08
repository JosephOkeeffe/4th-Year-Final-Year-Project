#pragma once
#include "Characters.h"
#include <iostream>
class Formation
{
public:

	Characters* leader;
	std::vector<Characters*> units;
};

