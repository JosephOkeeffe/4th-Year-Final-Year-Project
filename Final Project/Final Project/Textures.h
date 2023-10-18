#pragma once
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>

class Textures
{
	sf::Texture warriorTexture;
	
public:

	Textures();
	void SetupTextures();

	std::map<std::string, sf::Texture> textureMap;
};

