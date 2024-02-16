
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
    sf::Texture workerTexture;
    sf::Texture worker2Texture;
    sf::Texture worker3Texture;
    sf::Texture worker4Texture;
    sf::Texture oilManTexture;
    sf::Texture hazmatManTexture;

    // Buildings
    sf::Texture baseTexture;
    sf::Texture mineTexture;
    sf::Texture oilExtractorTexture;
    sf::Texture uraniumExtractorTexture;
    sf::Texture tilesTexture;

    // Buttons
    sf::Texture warriorButtonIconTexture;
    sf::Texture archerButtonIconTexture;
    sf::Texture workerButtonIconTexture;
    sf::Texture oilManButtonIconTexture;
    sf::Texture hazmatManButtonIconTexture;

    sf::Texture goldMineButtonIconTexture;
    sf::Texture oilExtractorButtonIconTexture;
    sf::Texture uraniumExtractorButtonIconTexture;

    // Other
    sf::Texture fogTexture;
    sf::Texture coinTexture;


    std::map<std::string, sf::Texture> textureMap;

};
