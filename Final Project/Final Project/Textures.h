
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
    sf::Texture oilManTexture;
    sf::Texture hazmatManTexture;

    // Enemy
    sf::Texture enemyTexture;


    // Buildings
    sf::Texture baseTexture;
    sf::Texture mineTexture;
    sf::Texture oilExtractorTexture;
    sf::Texture uraniumExtractorTexture;
    sf::Texture tilesTexture;

    // Buttons
    sf::Texture warriorButtonIconTexture;
    sf::Texture archerButtonIconTexture;
    sf::Texture minerButtonIconTexture;
    sf::Texture oilManButtonIconTexture;
    sf::Texture hazmatManButtonIconTexture;

    sf::Texture goldMineButtonIconTexture;
    sf::Texture oilExtractorButtonIconTexture;
    sf::Texture uraniumExtractorButtonIconTexture;

    // Other
    sf::Texture fogTexture;
    sf::Texture coinTexture;
    sf::Texture rotateTexture;
    sf::Texture scaleTexture;
    // Main Menu
    sf::Texture menuBackgroundTexture;
    sf::Texture menuMountainFarTexture;
    sf::Texture menuMountainCloseTexture;
    sf::Texture menuTreesFarTexture;
    sf::Texture menuTreesCloseTexture;


    std::map<std::string, sf::Texture> textureMap;

};
