
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
    sf::Texture tilesTexture;


    std::map<std::string, sf::Texture> textureMap;
};
