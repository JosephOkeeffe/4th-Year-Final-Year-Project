#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Globals.h"
#include "ItemManager.h"
#include "GameManager.h"

class Inventory
{
public:
    Inventory() {};
    void AddItem(std::string itemName, int amount);

    void RemoveItem(std::string itemName, int amount);
    void PrintItems();

private:
    std::vector<Item> items;
};
