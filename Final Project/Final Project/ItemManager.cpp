#include "ItemManager.h"

void ItemManager::LoadItemsFromJSON()
{

    std::filesystem::path currentPath = std::filesystem::current_path();
    std::string itemsFilePath = (currentPath / "../../Items/Items.json" ).string();

    std::ifstream file(itemsFilePath);

    if (file.is_open())
    {
        nlohmann::json jsonData;
        file >> jsonData;
        file.close();

        for (const auto& itemData : jsonData)
        {
            int id = itemData["id"];
            std::string name = itemData["name"];
            std::string textureName = itemData["texture"];

            sf::Texture texture = Textures::GetInstance().GetTexture(textureName);
            items.emplace_back(id, name, 0, texture, textureName);

            std::cout << "Loaded Item: \n";
            std::cout << "ID: " << id << "\n";
            std::cout << "NAME: " << name << "\n";
            std::cout << "TEXTURE NAME: " << textureName << "\n";
        }
    }
    else
    {
        std::cerr << "Error loading Items file!" << std::endl;
    }
}

Item& ItemManager::GetItemByID(int id)
{
    for (Item& item : items)
    {
        if (item.GetID() == id)
        {
            return item;
        }
    }
}

Item& ItemManager::GetItemByName(std::string name)
{
    for (Item& item : items)
    {
        if (item.GetName() == name)
        {
            return item;
        }
    }
}
