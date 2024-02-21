#include "Shader.h"

void Shader::InitShader(sf::String shaderName)
{
    if (!selectedShader.loadFromFile(shaderName, sf::Shader::Fragment))
    {
        sf::err() << "Error while loading custom fragment shader" << std::endl;
    }
    //m_shaderTexture.setRepeated(true);
    //m_shaderTexture.setSmooth(true);
}

void Shader::Update()
{
    selectedShader.setUniform("time", shader_timer.getElapsedTime().asSeconds());
}

sf::Shader& Shader::GetShader()
{
    return selectedShader;
}
