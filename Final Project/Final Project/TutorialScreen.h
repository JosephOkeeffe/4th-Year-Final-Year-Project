#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "GameManager.h"
#include "Textures.h"

class TutorialScreen
{
public:

    TutorialScreen();
    void HandleEvent(sf::Event event, bool& exit);
    void Update();
    void Draw(sf::RenderWindow& window);

    void AddPage(const std::string& heading, const std::string& paragraph, const sf::Texture& texture);
    void NextPage();
    void LastPage();
    void Exit(bool& exit);

    void ParagraphTextDelay();    
private:

    std::vector<std::string> headings;
    std::vector<std::string> paragraphs;
    std::vector<sf::Texture> textures;

    sf::RectangleShape background;
    sf::RectangleShape pageImage;
    sf::Text headingText;
    sf::Text paragraphText;
    sf::Text nextText;
    sf::Text lastText;
    sf::Text exitText;
    sf::RectangleShape nextPageButton;
    sf::RectangleShape lastPageButton;
    sf::RectangleShape exitButton;
    int currentPage;

    sf::Clock revealTimer; 
    sf::Time revealDelay = sf::milliseconds(50);


};

