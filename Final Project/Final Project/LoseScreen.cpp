#include "LoseScreen.h"
#include <algorithm> 
#include <random>   
#include <cmath>

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

    float blockSize = 50;
    float gapX = 5;
    float gapY = 5;

    float totalWidth = 10 * (blockSize + gapX) - gapX;
    float totalHeight = 10 * (blockSize + gapY) - gapY;

    float startX = (Global::S_WIDTH - totalWidth) / 2.0f;
    float startY = (Global::S_HEIGHT - totalHeight) / 2.0f;

    sf::Texture& texture = Textures::GetInstance().GetTexture("background3");

    int textureWidth = texture.getSize().x / 10;
    int textureHeight = texture.getSize().y / 10;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 3); 

    for (int row = 0; row < 10; ++row)
    {
        for (int col = 0; col < 10; ++col)
        {
            sf::RectangleShape shape(sf::Vector2f(blockSize, blockSize));
            float x = startX + col * (blockSize + gapX);
            float y = startY + row * (blockSize + gapY);
            y -= col * 50;
            shape.setPosition(x, y - Global::S_HEIGHT);

            shape.setOrigin(blockSize / 2.0f, blockSize / 2.0f);

            int randomRotation = dis(gen) * 90;
            shape.setRotation(randomRotation);

            shape.setTexture(&texture);
            shape.setTextureRect(sf::IntRect(col * textureWidth, row * textureHeight, textureWidth, textureHeight));
            blocks.push_back(shape);
        }
    }

    fullImage.setTexture(&Textures::GetInstance().GetTexture("background3"));
    fullImage.setSize({ 500,500 });
    fullImage.setPosition({ (Global::S_WIDTH / 2) - 25, (Global::S_HEIGHT / 2) - 25 });
    fullImage.setOrigin(fullImage.getSize().x / 2, fullImage.getSize().y / 2);
    fullImage.setScale(0.1, 0.1);
    fullImage.setFillColor(sf::Color(255,255,255,0));

    isImageDone = false;
}


void LoseScreen::Draw(sf::RenderWindow& window)
{
    for (sf::RectangleShape& block : blocks)
    {
        window.draw(block);
    }

    if (isImageDone)
    {
        window.draw(fullImage);
    }
}

void LoseScreen::HandleEvent(sf::Event event)
{
}

void LoseScreen::Update()
{
    float moveSpeed = 2;
    float stopY = 600;
    float rotationSpeed = 1;
    bool allStopped = true; 

    for (int col = 0; col < 10; ++col)
    {
        bool stopColumn = false;

        for (int row = 9; row >= 0; --row)
        {
            int index = row * 10 + col;
            sf::RectangleShape& block = blocks[index];

            if (block.getPosition().y >= stopY)
            {
                stopColumn = true;
            }

            if (!stopColumn)
            {
              
                block.move(0, moveSpeed);
                allStopped = false; 
            }
        }
    }

    if (allStopped)
    {
        for (sf::RectangleShape& block : blocks)
        {
            float currentRotation = block.getRotation();
            if (currentRotation > 0) 
            {
                float newRotation = std::max(0.f, currentRotation - rotationSpeed);
                block.setRotation(newRotation);
            }
        }
    }

    if(!isImageDone)
    {
        bool allBlocksRotated = true;
        for (sf::RectangleShape& block : blocks)
        {
            if (block.getRotation() != 0)
            {
                allBlocksRotated = false;
                break;
            }
        }

        if (allBlocksRotated)
        {
            isImageDone = true;
            timer.restart();
        }
    }

    if (isImageDone && timer.getElapsedTime().asSeconds() > 0.3)
    {
        for (sf::RectangleShape& block : blocks)
        {
            sf::Color color = block.getFillColor(); 
            int alpha = color.a; 
            alpha = std::max(0, alpha - 15); 
            block.setFillColor(sf::Color(color.r, color.g, color.b, alpha));

            sf::Vector2f size = block.getScale();
            size *= 0.90f; 
            block.setScale(size);
        }

        sf::Color color = fullImage.getFillColor();
        int alpha = color.a;

        if(alpha < 240)
        {
            alpha = std::max(0, alpha + 15);
        }

        fullImage.setFillColor(sf::Color(color.r, color.g, color.b, alpha));

        sf::Vector2f size = fullImage.getScale();
        if(size.x < 1)
        {
            size *= 1.15f;
        }
        fullImage.setScale(size);

        timer.restart();
    }

}
