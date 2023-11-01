#include "Button.h"
#include "Globals.h"
Button::Button(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& idleColour, const sf::Color& hoverColour, const sf::Font& font)
    : onClick(nullptr), isHovered(false), isPressed(false), idleColour(idleColour), hoverColour(hoverColour)
{
    shape.setSize(size);
    shape.setOrigin(size / 2.0f);
    shape.setPosition(position);
    shape.setFillColor(idleColour);

    label.setFont(font); // Default font, you can set your own
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::White);
    label.setOrigin(size / 2.0f);
    label.setPosition(position.x + (size.x * 0.15), position.y - (size.y * 0.1));

    // Center label text

}

void Button::setLabel(const std::string& text, const sf::Font& font, unsigned characterSize, const sf::Color& textColor) 
{
    label.setString(text);
    label.setFont(font);
    label.setCharacterSize(characterSize);
    label.setFillColor(textColor);
}

void Button::setCallback(std::function<void()> callback) 
{
    onClick = callback;
}

void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseMoved) 
    {
        sf::Vector2i mousePos = static_cast<sf::Vector2i>(Global::GetMousePos(window));

        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) 
        {
            isHovered = true;
            shape.setFillColor(hoverColour);
        }
        else 
        {
            isHovered = false;
            shape.setFillColor(idleColour);
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
    {
        if (isHovered) {
            isPressed = true;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) 
    {
        if (isPressed && isHovered && onClick) 
        {
            onClick();
        }
        isPressed = false;
    }
}

void Button::update() 
{
    // You can add additional update logic if needed
}

void Button::render(sf::RenderWindow& window) 
{
    window.draw(shape);
    window.draw(label);
}