#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Particles.h"


class Button
{
public:
    Button(const sf::Vector2f& position, 
        const sf::Vector2f& size, const sf::Color& idleColor,
        const sf::Color& hoverColor,
        const sf::Texture& texture);

    void setLabel(const std::string& text, unsigned characterSize, const sf::Color& textColor);
    void setCallback(std::function<void()> callback);
    void handleEvent(const sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);
    void centreLabel(sf::Vector2f position);
    void lowerLabelPosition();
    void SetLabelPosInRelationToButton(float x, float y);
    void SetLabelPos(float x, float y);

    sf::Vector2f getButtonPos();
    sf::RectangleShape getButtonSprite();

    ParticleSystem particleSystem;

private:
    sf::RectangleShape shape;
    sf::Text label;
    std::function<void()> onClick;

    bool isHovered;
    bool isPressed;
    sf::Color idleColour;
    sf::Color hoverColour;
 
};

