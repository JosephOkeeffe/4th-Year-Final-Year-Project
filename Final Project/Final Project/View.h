#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class View 
{
public:
    //static GameView& GetInstance(sf::RenderWindow& window);
    View(sf::RenderWindow& t_window, sf::View& t_gameView, sf::View& t_hudView);

    //void zoom(float factor);

    void move(sf::Vector2f offset);

    void handleInput(sf::Event& event);

    void SetGameView();
    void SetHudView();
    void MoveScreen();

private:
    sf::View& gameView;
    sf::View& hudView;
    float zoomFactor = 1;
    float minX = 500.0f;
    float minY = 300.0f;
    float maxX = Global::CELL_SIZE * Global::ROWS_COLUMNS;
    float maxY = Global::CELL_SIZE * Global::ROWS_COLUMNS;

    float screenMoveSpeed = 5;

    sf::Vector2f currentMousePos;

    sf::RenderWindow& window;


};

