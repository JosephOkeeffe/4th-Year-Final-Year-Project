#include "Textures.h"
#include <filesystem>

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

    // World
    tilesTexture.loadFromFile((std::filesystem::current_path() / "../../tiles.png").string());
    textureMap["tiles"] = tilesTexture;

    // Characters
    warriorTexture.loadFromFile("./assets/images/warrior.png");
    textureMap["warrior"] = warriorTexture;

    archerTexture.loadFromFile("./assets/images/mage.png");
    textureMap["archer"] = archerTexture;

    workerTexture.loadFromFile("./assets/images/worker.png");
    textureMap["worker"] = workerTexture;

    worker2Texture.loadFromFile("./assets/images/worker2.png");
    textureMap["worker2"] = worker2Texture;

    worker3Texture.loadFromFile("./assets/images/worker3.png");
    textureMap["worker3"] = worker3Texture;

    worker4Texture.loadFromFile("./assets/images/worker4.png");
    textureMap["worker4"] = worker4Texture;

    worker5Texture.loadFromFile("./assets/images/worker5.png");
    textureMap["worker5"] = worker5Texture;

    fogTexture.loadFromFile("./assets/images/fog.png");
    textureMap["fog"] = fogTexture;

    // Buildings
    baseTexture.loadFromFile("./assets/images/base.png");
    textureMap["hq"] = baseTexture;

    mineTexture.loadFromFile("./assets/images/mine.png");
    textureMap["mine"] = mineTexture;

    oilExtractorTexture.loadFromFile("./assets/images/oil2.png");
    textureMap["oil"] = oilExtractorTexture;

    // UI
    coinTexture.loadFromFile("./assets/images/coin.png");
    textureMap["coin"] = coinTexture;


    // UI - Icons
    warriorButtonIconTexture.loadFromFile("./assets/images/warrior-icon.png");
    textureMap["warrior-icon"] = warriorButtonIconTexture;

    archerButtonIconTexture.loadFromFile("./assets/images/archer-icon.png");
    textureMap["archer-icon"] = archerButtonIconTexture;

    workerButtonIconTexture.loadFromFile("./assets/images/worker-icon.png");
    textureMap["worker-icon"] = workerButtonIconTexture;

    mineButtonIconTexture.loadFromFile("./assets/images/mine-icon.png");
    textureMap["mine-icon"] = mineButtonIconTexture;

    oilButtonIconTexture.loadFromFile("./assets/images/oil-icon.png");
    textureMap["oil-icon"] = oilButtonIconTexture;
    
}

sf::Texture& Textures::GetTexture(const std::string& textureName) 
{
    return textureMap[textureName];
}
