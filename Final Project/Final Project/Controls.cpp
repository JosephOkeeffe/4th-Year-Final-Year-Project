#include "Controls.h"

Controls::Controls()
{
    background.setFillColor(sf::Color::White);
    background.setSize({ Global::S_WIDTH * 0.7, Global::S_HEIGHT * 0.8 });
    background.setPosition(Global::S_WIDTH / 2, Global::S_HEIGHT / 2);
    background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);

    headingText.setFont(Global::tutorialFont);
    headingText.setString("Controls");
    headingText.setFillColor(sf::Color::Black);
    headingText.setOutlineColor(sf::Color::Red);
    headingText.setOutlineThickness(0.5);
    headingText.setCharacterSize(30);
    headingText.setPosition(background.getPosition().x, background.getPosition().x * 0.25);
    headingText.setStyle(headingText.Underlined);
}

void Controls::HandleEvent(sf::Event event, bool& exit)
{
}

void Controls::Update()
{
}

void Controls::Draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(headingText);
}
