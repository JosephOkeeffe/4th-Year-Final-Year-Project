#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "GameManager.h"
#include "Textures.h"
class Controls
{
public:
    Controls();
    void HandleEvent(sf::Event event, bool& exit);
    void Update();
    void Draw(sf::RenderWindow& window);

    sf::RectangleShape background;
    sf::Text headingText;
    sf::Text controlsText;

    std::string firstThing;


};

