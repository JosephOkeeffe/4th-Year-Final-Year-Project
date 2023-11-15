#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
public:
    Button(sf::RenderWindow& window, const sf::Vector2f& position, 
        const sf::Vector2f& size, const sf::Color& idleColor,
        const sf::Color& hoverColor, const sf::Font& font,
        const sf::Texture& texture);

    void setLabel(const std::string& text, const sf::Font& font, unsigned characterSize, const sf::Color& textColor);
    void setCallback(std::function<void()> callback);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update();
    void render(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
    sf::Text label;
    std::function<void()> onClick;

    bool isHovered;
    bool isPressed;
    sf::Color idleColour;
    sf::Color hoverColour;
 
};

