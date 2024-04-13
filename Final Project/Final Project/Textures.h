
#pragma once
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>

class Textures {
public:
    static Textures& GetInstance();

    void SetupTextures();
    sf::Texture& GetTexture(const std::string& textureName);

private:
    Textures();

    // Units
    sf::Texture warriorTexture;
    sf::Texture archerTexture;
    sf::Texture minerTexture;
    sf::Texture miner2Texture;
    sf::Texture miner3Texture;
    sf::Texture miner4Texture;
    sf::Texture miner5Texture;
    sf::Texture oilManTexture;
    sf::Texture hazmatManTexture;

    // Enemy
    sf::Texture enemyTexture;
    sf::Texture sucklerTexture;
    sf::Texture suckler2Texture;
    sf::Texture sucklerDeadTexture;
    sf::Texture bigSucklerTexture;
    sf::Texture bigSucklerDeadTexture;
    sf::Texture gumperTexture;
    sf::Texture bigGumperTexture;
    sf::Texture spaceshipsTexture;
    sf::Texture eggTexture;

    // Projectiles
    sf::Texture blastTexture;
    sf::Texture blastTrailTexture;
    sf::Texture spitTexture;
    sf::Texture shieldTexture;
    sf::Texture flamingSwordTexture;
    sf::Texture flamingTrailTexture;

    // Buildings
    sf::Texture baseTexture;
    sf::Texture mineTexture;
    sf::Texture oilExtractorTexture;
    sf::Texture uraniumExtractorTexture;
    sf::Texture tilesTexture;
    sf::Texture enemyBaseTexture;
    sf::Texture enemyBaseDestroyedTexture;

    // Buttons
    sf::Texture warriorButtonIconTexture;
    sf::Texture archerButtonIconTexture;
    sf::Texture minerButtonIconTexture;
    sf::Texture oilManButtonIconTexture;
    sf::Texture hazmatManButtonIconTexture;

    sf::Texture buildHammerTexture;
    sf::Texture trainUnitsTexture;

    sf::Texture hqButtonIconTexture;
    sf::Texture goldMineButtonIconTexture;
    sf::Texture oilExtractorButtonIconTexture;
    sf::Texture uraniumExtractorButtonIconTexture;

    sf::Texture spaceshipIconTexture;

    // Other
    sf::Texture emptyTexture;

    sf::Texture fogTexture;
    sf::Texture coinTexture;
    sf::Texture rotateTexture;
    sf::Texture scaleTexture;
    sf::Texture goldParticleTexture;
    sf::Texture bloodTexture;
    sf::Texture sucklerTrailTexture;
    sf::Texture goopTexture;
    sf::Texture oilDropTexture;
    sf::Texture smokeTexture;
    sf::Texture sucklerHeadTexture;
    sf::Texture sucklerTentacleTexture;

    sf::Texture arrowTexture;
    sf::Texture cloudTexture;

    // Main Menu
    sf::Texture menuBackgroundTexture;
    sf::Texture menuMountainFarTexture;
    sf::Texture menuMountainCloseTexture;
    sf::Texture menuTreesFarTexture;
    sf::Texture menuTreesCloseTexture;

    sf::Texture uiArrowTexture;
    sf::Texture uiMenuTexture;

    sf::Texture uiBagTexture;
    sf::Texture uiSettingsTexture;

    // Backgrounds
    sf::Texture background1;
    sf::Texture background2;
    sf::Texture background3;
    sf::Texture button1;


    std::map<std::string, sf::Texture> textureMap;

};
