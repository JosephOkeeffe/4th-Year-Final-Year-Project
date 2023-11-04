#pragma once
class ResourceManagement
{
public:
	static int GetCoins();
	static void AddCoins(int amount);
	static void SpendCoins(int amount);
	
private:

	static int coins;
};



