#include "Shader.h"

void Shader::InitShader(sf::String shaderName)
{
    if (!selectedShader.loadFromFile(shaderName, sf::Shader::Fragment))
    {
        sf::err() << "Error while loading custom fragment shader" << std::endl;
    }
}

void Shader::Update()
{
    selectedShader.setUniform("time", shader_timer.getElapsedTime().asSeconds());
}

sf::Shader& Shader::GetShader()
{
    return selectedShader;
}
