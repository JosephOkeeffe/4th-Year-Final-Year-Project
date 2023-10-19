#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class GameView 
{
public:
    //static GameView& GetInstance(sf::RenderWindow& window);
    GameView(sf::RenderWindow& t_window);

    void zoom(float factor);

    void move(sf::Vector2f offset);

    void handleInput(sf::Event& event);

    void setView();

    void SetMousePos(sf::Vector2i mousePos);

    void MoveScreen();
    sf::Vector2f GetMousePos();

private:
    sf::View view;
    float zoomFactor = 1;
    float minX = 600.0f;
    float minY = 300.0f;
    float maxX = 5000.0f;
    float maxY = 5000.0f;

    float screenMoveSpeed = 5;

    sf::Vector2f currentMousePos;

    sf::RenderWindow& window;


};

