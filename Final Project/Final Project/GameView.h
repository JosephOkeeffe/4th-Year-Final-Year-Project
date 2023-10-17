#pragma once
#include <SFML/Graphics.hpp>

class GameView 
{
public:
    static GameView& GetInstance(sf::RenderWindow& window);
    GameView(sf::RenderWindow& window);

    // Zoom the view in or out.
    void zoom(float factor);

    // Move the view based on an offset.
    void move(sf::Vector2f offset);

    // Update the view in response to user input, e.g., mouse scrolling and dragging.
    void handleInput(sf::Event& event, sf::RenderWindow& window);

    // Set the target to draw to.
    void setView(sf::RenderWindow& window);

    void SetMousePos(sf::Vector2i mousePos);
    sf::Vector2i GetMousePos();

private:
    sf::View view;
    float zoomFactor = 1;
    float minX = 600.0f;
    float minY = 300.0f;
    float maxX = 5000.0f;
    float maxY = 5000.0f;

    sf::Vector2i currentMousePos;

};

