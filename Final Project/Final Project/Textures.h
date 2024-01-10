
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

    sf::Texture shopTexture;
    sf::Texture tilesTexture;
    sf::Texture grass0Texture;
    sf::Texture grass1Texture;
    sf::Texture grass2Texture;

    std::map<std::string, sf::Texture> textureMap;
};
