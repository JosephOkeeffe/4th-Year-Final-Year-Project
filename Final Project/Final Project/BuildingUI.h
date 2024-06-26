#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "HUD.h"
#include "SoundManager.h"

class BuildingUI
{
public:
    static void Init()
    {
        mainRectangle.setSize(sf::Vector2f(150, 100));
        mainRectangle.setFillColor(sf::Color(0,0, 255, 100));
        mainRectangle.setOrigin(mainRectangle.getLocalBounds().width / 2, 0);
        font.loadFromFile("./assets/fonts/Flinton.otf");

        buildButton.setSize(sf::Vector2f( mainRectangle.getSize().x * 0.35, mainRectangle.getSize().y / 1.5 ));
        buildButton.setOrigin(buildButton.getLocalBounds().width / 2, buildButton.getLocalBounds().height / 2);
        buildButton.setTexture(&Textures::GetInstance().GetTexture("build-hammer"));
           
        trainButton.setSize(sf::Vector2f(mainRectangle.getSize().x * 0.35, mainRectangle.getSize().y / 1.5));
        trainButton.setOrigin(buildButton.getLocalBounds().width / 2, buildButton.getLocalBounds().height / 2);
        trainButton.setTexture(&Textures::GetInstance().GetTexture("train-units"));


        for (int i = 0; i < 2; i++)
        {
            boxText[i].setFont(font);
            boxText[i].setFillColor(sf::Color::Black);
            boxText[i].setCharacterSize(20);
            boxText[i].setOrigin(boxText[i].getLocalBounds().width / 2, boxText[i].getLocalBounds().height / 2);
        }
      

        boxText[0].setPosition(buildButton.getPosition().x - boxText[0].getLocalBounds().width / 2, buildButton.getPosition().y + 40);
        boxText[1].setPosition(trainButton.getPosition().x - boxText[1].getLocalBounds().width / 2, trainButton.getPosition().y + 40);
    }

    static void Draw(sf::RenderWindow& window)
    {
        if (isActive)
        {
            window.draw(mainRectangle);
            window.draw(buildButton);
            window.draw(trainButton);
            for (int i = 0; i < 2; ++i)
            {
                window.draw(boxText[i]);
            }
        }
    }

    static void Activate(sf::Vector2f pos)
    {
        mainRectangle.setPosition(pos);

        float offsetY = (mainRectangle.getSize().y / 2);

        buildButton.setPosition(pos.x - (mainRectangle.getSize().x * 0.22), pos.y + offsetY);
        boxText[0].setPosition(buildButton.getPosition().x - boxText[0].getLocalBounds().width / 2, buildButton.getPosition().y + 30);
        boxText[0].setString("Build");

        trainButton.setPosition(pos.x + (mainRectangle.getSize().x * 0.22), pos.y + offsetY);
        boxText[1].setPosition(trainButton.getPosition().x - boxText[1].getLocalBounds().width / 2, trainButton.getPosition().y + 30);
        boxText[1].setString("Train");

        if (HUD::currentState == HUD::NONE)
        {
            isActive = true;
        }
    }

    static void Deactivate()
    {
        isActive = false;
    }

    static void BuildMenu(sf::RenderWindow& window, sf::View& view)
    {

        sf::Vector2f mousePos = Global::GetWindowMousePos(window, view);
        if (isActive)
        {
            if (buildButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                SoundManager::GetInstance().PlaySound("select", 50, false);
               HUD::currentState = HUD::BUILD_HUD;
               isActive = false;
            }
        }
    }

    static void TrainMenu(sf::RenderWindow& window, sf::View& view)
    {
        sf::Vector2f mousePos = Global::GetWindowMousePos(window, view);
        if (isActive)
        {
            if (trainButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                SoundManager::GetInstance().PlaySound("select", 50, false);
                HUD::currentState = HUD::TRAIN_HUD;
                isActive = false;
            }
        }
    }

    static bool isActive;
    static sf::Font font;
    static sf::Text boxText[2];

    static sf::RectangleShape mainRectangle;


private:

    static sf::RectangleShape buildButton;
    static sf::RectangleShape trainButton;
};
