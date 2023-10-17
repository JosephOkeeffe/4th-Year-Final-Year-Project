#include "GameView.h"

#include <iostream>



GameView::GameView(sf::RenderWindow& window)
{
    // Initialize the view with the initial settings.
    view = window.getDefaultView();
}

GameView& GameView::GetInstance(sf::RenderWindow& window)
{
    static GameView instance(window);
    return instance;
}

void GameView::zoom(float factor) 
{
    view.zoom(factor);
    std::cout <<"View Size: " << view.getSize().x << "\n";
}

void GameView::move(sf::Vector2f offset) 
{
    view.move(offset);
}

void GameView::handleInput(sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseWheelScrolled) 
    {
        zoomFactor += (event.mouseWheelScroll.delta / 10.0f);

        float minZoom = 0.1f;
        float maxZoom = 3.0f;
        zoomFactor = std::max(minZoom, std::min(maxZoom, zoomFactor));

        std::cout << "Zoom Factor: " << zoomFactor << "\n";
        zoom(zoomFactor);
        setView(window);
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i initialMousePos = sf::Mouse::getPosition();
            std::cout << "x: " << initialMousePos.x << " Y: " << initialMousePos.y << "\n";
            sf::Vector2f initialViewCenter = view.getCenter();
            bool isDragging = true;

            while (isDragging)
            {
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                    {
                        isDragging = false;
                        break;
                    }
                }

                sf::Vector2i currentMousePos = sf::Mouse::getPosition();
                sf::Vector2f offset = window.mapPixelToCoords(initialMousePos) - window.mapPixelToCoords(currentMousePos);

                sf::Vector2f newViewCenter = initialViewCenter + offset;

                newViewCenter.x = std::max(minX, std::min(newViewCenter.x, maxX));
                newViewCenter.y = std::max(minY, std::min(newViewCenter.y, maxY));
                view.setCenter(newViewCenter);

                setView(window);
            }
        }
        else if (event.mouseButton.button == sf::Mouse::Right)
        {
            SetMousePos(sf::Vector2i{ event.mouseButton.x, event.mouseButton.y });
        }
    }

}

void GameView::setView(sf::RenderWindow& window) 
{
    window.setView(view);
}

void GameView::SetMousePos(sf::Vector2i mousePos)
{
    currentMousePos = mousePos;
    std::cout << "Mouse x: " << currentMousePos.x << " Mouse Y: " << currentMousePos.y << "\n";

}

sf::Vector2i GameView::GetMousePos()
{
    return currentMousePos;
}
