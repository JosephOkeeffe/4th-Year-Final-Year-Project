#include "Button.h"
#include "Globals.h"
#include "GameManager.h"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& idleColour, const sf::Color& hoverColour, const sf::Texture& texture)
    : onClick(nullptr), isHovered(false), isPressed(false), idleColour(idleColour), hoverColour(hoverColour)
{
    shape.setSize(size);
    shape.setOrigin(size / 2.0f);
    shape.setPosition(position);
    shape.setFillColor(idleColour);
    shape.setTexture(&texture);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);


    label.setFont(Global::font);
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::Black);
    label.setOrigin(size / 2.0f);
    label.setPosition(position.x + (size.x * 0.1), position.y - (size.y * 0.1));

    // Center label text

}

void Button::setLabel(const std::string& text, unsigned characterSize, const sf::Color& textColor) 
{
    label.setString(text);
    label.setFont(Global::font);
    label.setCharacterSize(characterSize);
    label.setFillColor(textColor);
}

void Button::setCallback(std::function<void()> callback) 
{
    onClick = callback;
}

void Button::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved) 
    {
        mousePos = static_cast<sf::Vector2i>(Global::GetLocalMousePos(*GameManager::GetWindow()));

        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) 
        {
            isHovered = true;
            shape.setFillColor(hoverColour);
        }
        else 
        {
            isHovered = false;
            particleSystem.clearParticles();
            shape.setFillColor(idleColour);
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
    {
        if (isHovered) 
        {
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

    if (isHovered)
    {

    }
}

void Button::update() 
{
    // You can add additional update logic if needed
}

void Button::render(sf::RenderWindow& window) 
{
    particleSystem.draw(window);
    window.draw(shape);
    window.draw(label);

    if (isHovered)
    {
        sf::Vector2f randomVelocity((rand() % 5 - 2) * 2.0f, (rand() % 5 - 2) * 2.0f);
        sf::Color randomColor(rand() % 256, rand() % 256, rand() % 256, 255);
        float randomSize = static_cast<float>(rand() % 5 + 2);

        // add particles that go up
        particleSystem.addParticle(static_cast<sf::Vector2f>(mousePos), randomVelocity, randomColor, randomSize, 0);

        particleSystem.update();
    }
}

void Button::centreLabel(sf::Vector2f position)
{
    label.setOrigin(label.getLocalBounds().width / 2, label.getLocalBounds().height / 2);
    label.setPosition(position);

}

void Button::lowerLabelPosition()
{
    sf::Vector2f newPos;
    newPos.x = shape.getPosition().x;
    newPos.y = shape.getPosition().y + shape.getSize().y * 0.6;

    label.setPosition(newPos);
}

void Button::SetLabelPosInRelationToButton(float x, float y)
{
    sf::Vector2f newPos;
    newPos.x = shape.getPosition().x * x;
    newPos.y = shape.getPosition().y * y;

    label.setPosition(newPos);
}

void Button::SetLabelPos(float x, float y)
{
   // label.setPosition
}

sf::Vector2f Button::getButtonPos()
{
    return shape.getPosition();
}

sf::RectangleShape Button::getButtonSprite()
{
    return shape;

}
