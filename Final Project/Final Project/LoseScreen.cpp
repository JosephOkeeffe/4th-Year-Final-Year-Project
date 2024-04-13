#include "LoseScreen.h"
#include <algorithm> 
#include <random>   

LoseScreen::LoseScreen()
{
    blockWidth = 30;
    blockHeight = 30;
    fallSpeed = 2;

    Init();
}

void LoseScreen::Init() 
{
    blocks.clear();

    float blockSize = 50.0f;
    float gap = 5.0f; 

    float totalWidth = 10 * (blockSize + gap) - gap;
    float totalHeight = 10 * (blockSize + gap) - gap;

    float startX = (Global::S_WIDTH - totalWidth) / 2.0f;
    float startY = (Global::S_HEIGHT - totalHeight) / 2.0f;

    sf::Texture& texture = Textures::GetInstance().GetTexture("coin");

    int textureWidth = texture.getSize().x / 10; 
    int textureHeight = texture.getSize().y / 10; 

    for (int row = 0; row < 10; ++row) 
    {
        for (int col = 0; col < 10; ++col) 
        {
            sf::RectangleShape shape(sf::Vector2f(blockSize, blockSize));
            float x = startX + col * (blockSize + gap);
            float y = startY + row * (blockSize + gap);
            shape.setPosition(x, y);

            shape.setTexture(&texture);
            shape.setTextureRect(sf::IntRect(col * textureWidth, row * textureHeight, textureWidth, textureHeight));
            blocks.push_back(shape);
        }
    }
}



void LoseScreen::Draw(sf::RenderWindow& window)
{

    for (const auto& block : blocks)
    {
        window.draw(block);
    }
}

void LoseScreen::HandleEvent(sf::Event event)
{

}

void LoseScreen::Update() {


}
