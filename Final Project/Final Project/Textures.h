
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

    sf::Texture warriorTexture;
    sf::Texture archerTexture;
    sf::Texture coinTexture;

    sf::Texture baseTexture;
    sf::Texture shopTexture;
    sf::Texture mineTexture;
    sf::Texture tilesTexture;

    sf::Texture warriorButtonIconTexture;
    sf::Texture archerButtonIconTexture;
    sf::Texture workerButtonIconTexture;
    sf::Texture mineButtonIconTexture;


    std::map<std::string, sf::Texture> textureMap;
};
