#include "GameView.h"

#include <iostream>



GameView::GameView(sf::RenderWindow& t_window) : window(t_window)
{
    // Initialize the view with the initial settings.
    view = window.getDefaultView();
}

//GameView& GameView::GetInstance(sf::RenderWindow& window)
//{
//    static GameView instance(window);
//    return instance;
//}

void GameView::zoom(float factor) 
{
    view.zoom(factor);
    std::cout <<"View Size: " << view.getSize().x << "\n";
    std::cout <<"Factor Size: " << factor << "\n";
}

void GameView::move(sf::Vector2f offset) 
{
    view.move(offset);
}

void GameView::handleInput(sf::Event& event)
{
   /* if (event.type == sf::Event::MouseWheelScrolled) 
    {
        zoomFactor += (event.mouseWheelScroll.delta * 0.1f);

        float minZoom = 0.01f;
        float maxZoom = 1.1f;
        zoomFactor = std::max(minZoom, std::min(maxZoom, zoomFactor));

        std::cout << "Zoom Factor: " << zoomFactor << "\n";
        zoom(zoomFactor);
        setView(window);
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Middle)
        {
            sf::Vector2i initialMousePos = sf::Mouse::getPosition();
            sf::Vector2f initialViewCenter = view.getCenter();
            bool isDragging = true;

            while (isDragging)
            {
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Middle)
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
    }*/
}

void GameView::setView() 
{
   window.setView(view);
}

//void GameView::SetMousePos(sf::Vector2i mousePos)
//{
//    currentMousePos = window.mapPixelToCoords(mousePos);
//    std::cout << "Mouse x: " << currentMousePos.x << " Mouse Y: " << currentMousePos.y << "\n";
//}

void GameView::MoveScreen()
{
    sf::Vector2f viewCenter = view.getCenter();
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

    view.setCenter(viewCenter);
    setView();
}

//sf::Vector2f GameView::GetMousePos()
//{
//    return currentMousePos;
//}
