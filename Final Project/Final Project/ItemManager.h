#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "Globals.h"
#include "Textures.h"
#include "json.hpp"

class Item
{
public:
    Item(int id, std::string name, int quantity, sf::Texture texture) : itemID(id), itemName(name), itemQuantity(quantity), itemTexture(texture) {}

    // Getters
    sf::Sprite& GetTexture() { return itemTexture; }
    int GetID() const { return itemID; }
    int GetQuantity() const { return itemQuantity; }
    std::string GetName() const { return itemName; }

    void IncreaseQuantity(int amountToAdd) { itemQuantity += amountToAdd; }
    void DecreaseQuantity(int amountToLose) { itemQuantity -= amountToLose; }

private:
    sf::Sprite itemTexture;
    int itemID;
    int itemQuantity;
    std::string itemName;

};

class ItemManager
{
public:
    void LoadItemsFromJSON();

    Item& GetItemByID(int id);
    Item& GetItemByName(std::string name);

private:
   std::vector<Item> items;

};



