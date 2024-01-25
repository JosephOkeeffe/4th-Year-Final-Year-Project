#include "Textures.h"

Textures& Textures::GetInstance() 
{
    static Textures instance;
    return instance;
}

// Private constructor to prevent instantiation
Textures::Textures() 
{
    SetupTextures();
}

void Textures::SetupTextures() 
{
    warriorTexture.loadFromFile("./assets/images/warrior.png");
    textureMap["warrior"] = warriorTexture;

    archerTexture.loadFromFile("./assets/images/mage.png");
    textureMap["archer"] = archerTexture;

    coinTexture.loadFromFile("./assets/images/coin.png");
    textureMap["coin"] = coinTexture;
    
    shopTexture.loadFromFile("./assets/images/shop.png");
    textureMap["shop"] = shopTexture;

    baseTexture.loadFromFile("./assets/images/base.png");
    textureMap["base"] = baseTexture;

    tilesTexture.loadFromFile("./assets/images/tiles.png");
    textureMap["tiles"] = tilesTexture;

    tilesTexture.loadFromFile("./assets/images/warrior-icon.png");
    textureMap["warrior-icon"] = tilesTexture;

    tilesTexture.loadFromFile("./assets/images/archer-icon.png");
    textureMap["archer-icon"] = tilesTexture;

}

sf::Texture& Textures::GetTexture(const std::string& textureName) 
{
    return textureMap[textureName];
}
