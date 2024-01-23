#pragma once
#include <SFML/Graphics.hpp>

class BuildingUI
{
public:
    static void Init()
    {
        // Initialize the main rectangle
        mainRectangle.setSize(sf::Vector2f(180, 120));
        mainRectangle.setFillColor(sf::Color::Blue);
        mainRectangle.setOrigin(mainRectangle.getLocalBounds().width / 2, 0);
        font.loadFromFile("./assets/fonts/Flinton.otf");


        // Initialize the array of small rectangles
        for (int i = 0; i < numSmallRectangles; ++i)
        {
            smallRectangles[i].setSize(sf::Vector2f( mainRectangle.getSize().x * 0.35, mainRectangle.getSize().y / 1.5 ));
            smallRectangles[i].setFillColor(sf::Color::Red);
            smallRectangles[i].setOrigin(smallRectangles[i].getLocalBounds().width / 2, smallRectangles[i].getLocalBounds().height / 2);
           
            boxText[i].setFont(font);
            boxText[i].setFillColor(sf::Color::Black);
            boxText[i].setCharacterSize(20);
            boxText[i].setOrigin(boxText[i].getLocalBounds().width / 2, boxText[i].getLocalBounds().height / 2);
        }

        boxText[0].setPosition(smallRectangles[0].getPosition().x - boxText[0].getLocalBounds().width / 2, smallRectangles[0].getPosition().y + 40);
        boxText[1].setPosition(smallRectangles[1].getPosition().x - boxText[1].getLocalBounds().width / 2, smallRectangles[0].getPosition().y + 40);
    }

    static void Draw(sf::RenderWindow& window)
    {
        if (isActive)
        {
            window.draw(mainRectangle);
            for (int i = 0; i < numSmallRectangles; ++i)
            {
                window.draw(smallRectangles[i]);
                window.draw(boxText[i]);
            }
        }
    }

    static void Activate(sf::Vector2f pos)
    {
        mainRectangle.setPosition(pos);

        float offsetY = (mainRectangle.getSize().y / 2) ; // Half the height of the small rectangles

        // 180 / 2 = 90
        smallRectangles[0].setPosition(pos.x - (mainRectangle.getSize().x * 0.22), pos.y + offsetY);
        boxText[0].setPosition(smallRectangles[0].getPosition().x - boxText[0].getLocalBounds().width / 2, smallRectangles[0].getPosition().y + 37);
        boxText[0].setString("Build");

        smallRectangles[1].setPosition(pos.x + (mainRectangle.getSize().x * 0.22), pos.y + offsetY);
        boxText[1].setPosition(smallRectangles[1].getPosition().x - boxText[1].getLocalBounds().width / 2, smallRectangles[0].getPosition().y + 37);
        boxText[1].setString("Train");

        isActive = true;
    }

    static void Deactivate()
    {
        isActive = false;
    }

    static bool isActive;
    static sf::Font font;
    static sf::Text boxText[2];


private:
    static sf::RectangleShape mainRectangle;
    static const int numSmallRectangles = 2;
    static sf::RectangleShape smallRectangles[numSmallRectangles];
};
