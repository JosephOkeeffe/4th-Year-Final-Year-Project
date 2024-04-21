#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Globals.h"
#include "Textures.h"

class WinScreen
{
public:
    WinScreen();
    void Init();
    void Draw(sf::RenderWindow& window);
    void HandleEvent(sf::Event event);
    void Update();

private:
    struct Confetti
    {
        sf::Sprite sprite;
        sf::Vector2f velocity;
        float rotationSpeed;
    };

    sf::RectangleShape background;
    sf::Text winText;
    sf::Vector2f winTextVelocity;
    float winTextRotationSpeed;
    std::vector<Confetti> confetti;
    std::mt19937 rng; 

    sf::RectangleShape homeButton;
    sf::Text homeText;
};
