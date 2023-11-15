 #pragma once
class ResourceManagement
{
public:
	static int GetCoins();
	static void AddCoins(int amount);
	static void SpendCoins(int amount);
	static void AddShops(int amount);
	static int GetShops();

	static void ResetAndLoad(int coins, int shops);

	static bool isPlacingShop; 
	
private:

	static int coins;
	static int amountOfShops;
};



