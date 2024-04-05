#include "Inventory.h"

Inventory::Inventory()
{
    inventoryBackground.setSize({ 500, Global::S_HEIGHT * 0.9 });
    inventoryBackground.setFillColor(sf::Color::Black);
    inventoryBackground.setPosition(Global::S_WIDTH / 2, Global::S_HEIGHT / 2);
    inventoryBackground.setOrigin(inventoryBackground.getSize().x / 2, inventoryBackground.getSize().y / 2);

    inventoryText.setFont(Global::font);
    inventoryText.setString("Inventory");
    inventoryText.setCharacterSize(50);
    inventoryText.setFillColor(sf::Color::Red);
    inventoryText.setPosition(inventoryBackground.getPosition().x - 90, inventoryBackground.getPosition().y * 0.1);    

    float totalWidth = numCols * (slotSize + padding) - padding;
    float totalHeight = numRows * (slotSize + padding) - padding;

    float startX = Global::S_WIDTH / 2 - totalWidth / 2;
    float startY = Global::S_HEIGHT / 2 - totalHeight / 2;

    float textOffsetX = 20.0f; 
    float textOffsetY = 30.0f; 

    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            Item* newItem = new Item(-1, "Default", 0, Textures::GetInstance().GetTexture("gold-icon"), "gold-icon"); 
            InventorySlots slot(newItem);

            float posX = startX + (col + 0.5f) * (slotSize + padding);
            float posY = startY + (row + 0.5f) * (slotSize + padding);

            float textPosX = posX + slotSize / 2 - textOffsetX;
            float textPosY = posY + slotSize / 2 - textOffsetY;

            slot.background.setSize({ slotSize, slotSize });
            slot.background.setFillColor(sf::Color::White);
            slot.background.setPosition(posX, posY);
            slot.background.setOrigin(slotSize / 2, slotSize / 2);

            slot.itemSprite.setSize({ itemSize, itemSize });
            slot.itemSprite.setFillColor(sf::Color::White);
            slot.itemSprite.setPosition(posX, posY);
            slot.itemSprite.setOrigin(itemSize / 2, itemSize / 2);

            slot.amountText.setFont(Global::font);
            slot.amountText.setFillColor(sf::Color::Red);

            slot.amountText.setCharacterSize(24);
            slot.amountText.setPosition(textPosX, textPosY);
            slot.amountText.setString("");

            inventorySlots.push_back(slot);
        }
    }
}

void Inventory::Draw(sf::RenderWindow& window)
{
    window.draw(inventoryBackground);
    window.draw(inventoryText);

    for (InventorySlots& slot : inventorySlots)
    {
        window.draw(slot.background);
        window.draw(slot.itemSprite);
        window.draw(slot.amountText);
    }
}

void Inventory::AddItem(std::string itemName, int amount)
{
    Item item = GameManager::itemManager.GetItemByName(itemName);

    for (InventorySlots& slot : inventorySlots)
    {
        // Create new slot
        if (!slot.isItemAlreadyInInventory)
        { 
            Item* newItem = new Item(item.GetID(), item.GetName(), item.GetQuantity(), item.GetTexture(), item.GetTextureName());
            slot.item = newItem;
            slot.item->IncreaseQuantity(amount);
            slot.CreateSlot();
            items.push_back(*slot.item);
            std::cout << slot.item->GetQuantity() << " " << slot.item->GetName() << " added to inventory \n";
            return;
        }
        // Increase exisiting amount
        else
        {
            if (item.GetName() == slot.item->GetName())
            {
                slot.item->IncreaseQuantity(amount);
                slot.UpdateSlot();
                std::cout << "Your " << slot.item->GetName() << " has increased by " << amount << "\n";
                return;
            }

        }
    }
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

void Inventory::SortInventorySlotsByQuantity()
{

    ascending = !ascending;

    // Sort the inventory slots by item quantity
    std::sort(inventorySlots.begin(), inventorySlots.end(),
        [](const InventorySlots& slot1, const InventorySlots& slot2)
        {
            if (slot1.item && slot2.item)
            {
                return slot1.item->GetQuantity() < slot2.item->GetQuantity();
            }
            return false;
        });

    // If descending order is requested, reverse the sorting order
    if (!ascending)
    {
        std::reverse(inventorySlots.begin(), inventorySlots.end());
    }

    float totalWidth = numCols * (slotSize + padding) - padding;
    float totalHeight = numRows * (slotSize + padding) - padding;

    float startX = Global::S_WIDTH / 2 - totalWidth / 2;
    float startY = Global::S_HEIGHT / 2 - totalHeight / 2;

    float textOffsetX = 20.0f;
    float textOffsetY = 30.0f;

    int col = 0, row = 0;

    for (InventorySlots& slot : inventorySlots)
    {
        float posX = startX + (col + 0.5f) * (slotSize + padding);
        float posY = startY + (row + 0.5f) * (slotSize + padding);

        float textPosX = posX + slotSize / 2 - textOffsetX;
        float textPosY = posY + slotSize / 2 - textOffsetY;

        slot.background.setPosition(posX, posY);
        slot.itemSprite.setPosition(posX, posY);
        slot.amountText.setPosition(textPosX, textPosY);

        col++;
        if (col >= numCols)
        {
            col = 0;
            row++;
        }
    }
}


void Inventory::SortInventorySlotsByID()
{
    std::sort(inventorySlots.begin(), inventorySlots.end(),
        [](const InventorySlots& slot1, const InventorySlots& slot2)
        {
            if (slot1.item && slot2.item)
            {
                if (slot1.item->GetID() >= 0 && slot2.item->GetID() >= 0)
                {
                    return slot1.item->GetID() < slot2.item->GetID();
                }
                else if (slot1.item->GetID() >= 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            return false;
        });

    float totalWidth = numCols * (slotSize + padding) - padding;
    float totalHeight = numRows * (slotSize + padding) - padding;

    float startX = Global::S_WIDTH / 2 - totalWidth / 2;
    float startY = Global::S_HEIGHT / 2 - totalHeight / 2;

    float textOffsetX = 20.0f;
    float textOffsetY = 30.0f;

    int col = 0, row = 0;

    for (InventorySlots& slot : inventorySlots)
    {
        float posX = startX + (col + 0.5f) * (slotSize + padding);
        float posY = startY + (row + 0.5f) * (slotSize + padding);

        float textPosX = posX + slotSize / 2 - textOffsetX;
        float textPosY = posY + slotSize / 2 - textOffsetY;

        slot.background.setPosition(posX, posY);
        slot.itemSprite.setPosition(posX, posY);
        slot.amountText.setPosition(textPosX, textPosY);

        col++;
        if (col >= numCols)
        {
            col = 0;
            row++;
        }
    }
}

