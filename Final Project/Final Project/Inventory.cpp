#include "Inventory.h"

void Inventory::AddItem(std::string itemName, int amount)
{
    Item item = GameManager::itemManager.GetItemByName(itemName);
    item.IncreaseQuantity(amount);

    if (items.empty()) 
    {
        std::cout << item.GetQuantity() << " " << item.GetName() << " added to inventory \n";
        items.push_back(item);
        return;
    }

    for (Item& existingItem : items)
    {
        if (existingItem.GetName() == item.GetName())
        {
            std::cout << "Your " << item.GetName() << " has increased by "<< item.GetQuantity() << "\n";
            existingItem.IncreaseQuantity(item.GetQuantity());
            return;
        }
    }

    items.push_back(item);
}
void Inventory::RemoveItem(std::string itemName, int amount)
{
    auto it = std::remove_if(items.begin(), items.end(), [&](Item& item) 
        {
            if (item.GetName() == itemName) 
            {
                item.DecreaseQuantity(amount);
                std::cout << amount << " " << item.GetName() << " removed from inventory \n";

                if (item.GetQuantity() <= 0) 
                {
                    std::cout << item.GetName() << " is no longer in your inventory \n";
                    return true;
                }
            }
            return false;
        });

    items.erase(it, items.end()); 
}

void Inventory::PrintItems()
{
    std::cout << "Inventory Items:" << "\n";
    for (Item& item : items) 
    {
        std::cout << "Name: " << item.GetName() << ", ID: " << item.GetID() << ", Quantity: " << item.GetQuantity() << " \n";
    }
}
