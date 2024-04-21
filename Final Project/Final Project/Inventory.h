#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Globals.h"
#include "ItemManager.h"
#include "GameManager.h"

struct InventorySlots
{
    InventorySlots(Item* newItem) : item(newItem), isItemAlreadyInInventory(false) {}

   void CreateSlot() 
   {
       itemSprite.setTexture(&item->GetTexture());
       amountText.setString(std::to_string(item->GetQuantity()));
       isItemAlreadyInInventory = true;
   }

   void UpdateSlot()
   {
       amountText.setString(std::to_string(item->GetQuantity()));
   }

   void ResetSlot()
   {
       item = new Item(-1, "Default", 0, Textures::GetInstance().GetTexture("empty"), "empty");
       itemSprite.setTexture(nullptr);
       amountText.setString("");
       isItemAlreadyInInventory = false;
   }

    sf::RectangleShape background;
    sf::RectangleShape itemSprite;
    sf::Text amountText;
    bool isItemAlreadyInInventory;

    Item* item;
};

class Inventory
{
public:
    Inventory();

    void Draw(sf::RenderWindow& window);
    void ProcessMouseRelease(sf::Event t_event);
    void AddItem(std::string itemName, int amount);
    void RemoveItem(std::string itemName, int amount);

    void RemoveAllItems();

    void SortInventorySlotsByQuantity();
    void SortInventorySlotsByID();

    Item* GetInventoryItemByName(std::string name);
    

    bool quantityAscending = false;
    bool idAscending = false;
    void PrintItems();


    std::vector<Item*> items;

private:

   
    sf::Text inventoryText;
    sf::RectangleShape inventoryBackground;
    std::vector<InventorySlots> inventorySlots;


    sf::Text sortByQuantityText;
    sf::RectangleShape sortByQuantityButton;

    sf::Text sortByIDText;
    sf::RectangleShape sortByIDButton;

    int numSlots = 1; 
    int numRows = 5; 
    int numCols = 4; 
    float slotSize = 100.0f;
    float padding = 10.0f; 
    float itemSize = slotSize * 0.6;
};

