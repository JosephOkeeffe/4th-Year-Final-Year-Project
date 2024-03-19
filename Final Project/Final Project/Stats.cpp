#include "Stats.h"
#include "Globals.h"

void Stats::InitSprites()
{
}

void Stats::Draw(sf::RenderWindow& window)
{
}

void Stats::DisplayStats(sf::RenderWindow& window, sf::Vector2f pos)
{
    sf::Text text;
    text.setFont(Global::font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    text.setString("Level: " + std::to_string(GetLevel()) + "\n" +
        "XP: " + std::to_string(GetCurrentXP()) + "\n" +
        "Health: " + std::to_string(GetHealth()) + "\n" +
        "Damage: " + std::to_string(GetDamage()) + "\n" +
        "Attack Speed: " + std::to_string(GetAttackSpeed()));

    window.draw(text);

    DrawStatBar(window, "HP", GetHealth() / MAX_HEALTH, sf::Color::Red, pos.x, pos.y);
    DrawStatBar(window, "XP", GetCurrentXP() / xpNeededForNextLevel, sf::Color::Green, pos.x, pos.y + 20);
}

void Stats::DrawStatBar(sf::RenderWindow& window, const std::string& label, int percentage, const sf::Color& color, float xPosition, float yPosition)
{
    sf::Vector2f barSize = { 100,15 };
    int textSize = 15;
    sf::RectangleShape statBarBackground(barSize);
    statBarBackground.setPosition(xPosition, yPosition);
    statBarBackground.setFillColor(sf::Color::Black);
    statBarBackground.setOutlineThickness(2);
    statBarBackground.setOutlineColor(sf::Color::Black);
    statBarBackground.setOrigin(statBarBackground.getSize().x / 2, statBarBackground.getSize().y / 2);

    sf::RectangleShape statBar(barSize);
    statBar.setPosition(xPosition, yPosition);
    statBar.setFillColor(color);
    statBar.setOrigin(statBar.getSize().x / 2, statBar.getSize().y / 2);
    // Text
    sf::Text statLabel;
    statLabel.setFont(Global::font);
    statLabel.Bold;
    statLabel.setCharacterSize(textSize);
    statLabel.setFillColor(sf::Color::White);
    statLabel.setString(label);
    statLabel.setPosition(xPosition - barSize.x * 0.45, yPosition - barSize.y * 0.6);
    statLabel.setOutlineThickness(0.4);
    statLabel.setOutlineColor(sf::Color::Black);

    sf::Text percentageText;
    percentageText.setFont(Global::font);
    percentageText.Bold;
    percentageText.setCharacterSize(textSize);
    percentageText.setFillColor(sf::Color::White);
    percentageText.setString(std::to_string(percentage * 100) + "%");
    percentageText.setPosition((xPosition - barSize.x * 0.45) + statLabel.getGlobalBounds().width * 1.2, yPosition - barSize.y * 0.6);
    percentageText.setOutlineThickness(0.4);
    percentageText.setOutlineColor(sf::Color::Black);

    window.draw(statBarBackground);
    window.draw(statBar);
    window.draw(percentageText);
    window.draw(statLabel);
}
