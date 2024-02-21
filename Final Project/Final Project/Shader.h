#pragma once
#include "SFML/Graphics.hpp"
#include "Textures.h"

class Shader
{
private:

	sf::Shader selectedShader;
	sf::Clock shader_timer;
	sf::Texture m_shaderTexture;

public:

	void InitShader(sf::String shaderName);
	void Update();
	sf::Shader& GetShader();

};

