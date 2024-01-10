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

    tilesTexture.loadFromFile("./assets/images/tiles.png");
    textureMap["tiles"] = tilesTexture;

    grass0Texture.loadFromFile("./assets/images/grass0.png");
    textureMap["grass0"] = grass0Texture;

    grass1Texture.loadFromFile("./assets/images/grass1.png");
    textureMap["grass1"] = grass1Texture;
}

sf::Texture& Textures::GetTexture(const std::string& textureName) 
{
    return textureMap[textureName];
}
