#pragma once
class ResourceManagement
{
public:
	static int GetCoins();
	static void AddCoins(int amount);
	static void SpendCoins(int amount);
	static void AddShops(int amount);
	static int GetShops(int amount);

	static bool isPlacingShop; 
	
private:

	static int coins;
	static int amountOfShops;
};



