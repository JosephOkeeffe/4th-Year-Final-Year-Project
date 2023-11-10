#include "View.h"

#include <iostream>

View::View(sf::RenderWindow& t_window, sf::View& t_gameView, sf::View& t_hudView) : window(t_window), gameView(t_gameView), hudView(t_hudView)
{
    gameView = window.getDefaultView();
    hudView = window.getDefaultView();
}

void View::move(sf::Vector2f offset) 
{
    gameView.move(offset);
}

void View::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled) 
    {
        zoomFactor += (event.mouseWheelScroll.delta * 0.1f);

        float minZoom = 0.01f;
        float maxZoom = 1.1f;
        zoomFactor = std::max(minZoom, std::min(maxZoom, zoomFactor));

        std::cout << "Zoom Factor: " << zoomFactor << "\n";
        std::cout << "View Size X: " << gameView.getSize().x << "\n";
        std::cout << "View Size Y: " << gameView.getSize().y << "\n";
        gameView.zoom(zoomFactor + event.mouseWheel.delta * 0.1f);
        SetGameView();
    }
}
// textures
// save and load level
void View::SetGameView() 
{
   window.setView(gameView);
}

void View::SetHudView()
{
    window.setView(hudView);
}

void View::MoveScreen()
{
    sf::Vector2f viewCenter = gameView.getCenter();
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (mousePosition.x < Global::S_WIDTH * 0.1 && viewCenter.x - screenMoveSpeed > minX)
        {
            viewCenter.x -= screenMoveSpeed;
        }
        if (mousePosition.x > Global::S_WIDTH * 0.9 && viewCenter.x + screenMoveSpeed < maxX)
        {
            viewCenter.x += screenMoveSpeed;
        }
        if (mousePosition.y < Global::S_HEIGHT * 0.1 && viewCenter.y - screenMoveSpeed > minY)
        {
            viewCenter.y -= screenMoveSpeed;
        }
        if (mousePosition.y > Global::S_HEIGHT * 0.9 && viewCenter.y + screenMoveSpeed < maxY)
        {
            viewCenter.y += screenMoveSpeed;
        }
    }

    gameView.setCenter(viewCenter);
    SetGameView();
}
