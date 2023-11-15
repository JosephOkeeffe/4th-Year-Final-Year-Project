#include "ResourceManagement.h"

int ResourceManagement::coins = 0;
bool ResourceManagement::isPlacingShop = false; 
int ResourceManagement::amountOfShops = 0;

int ResourceManagement::GetCoins()
{
    return coins;
}

void ResourceManagement::AddCoins(int amount)
{
    coins += amount;
}

void ResourceManagement::SpendCoins(int amount)
{
	coins -= amount;
	if (coins < 0)
	{
		coins = 0; // Ensure that coins cannot go negative
	}
}

void ResourceManagement::AddShops(int amount)
{
	amountOfShops++;
}

int ResourceManagement::GetShops()
{
	return amountOfShops;
}

void ResourceManagement::ResetAndLoad(int t_coins, int shops)
{
	amountOfShops = 0;
	AddShops(shops);
	coins = 0;
	AddCoins(t_coins);

}
