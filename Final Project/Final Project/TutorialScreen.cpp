#include "TutorialScreen.h"

TutorialScreen::TutorialScreen() : currentPage(0)
{
    background.setFillColor(sf::Color::White);
    background.setSize({ Global::S_WIDTH * 0.7, Global::S_HEIGHT * 0.8 });
    background.setPosition(Global::S_WIDTH / 2, Global::S_HEIGHT / 2);
    background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);

    headingText.setFont(Global::tutorialFont);
    headingText.setFillColor(sf::Color::Black);
    headingText.setOutlineColor(sf::Color::Red);
    headingText.setOutlineThickness(0.5);
    headingText.setCharacterSize(30);
    headingText.setPosition(background.getPosition().x, background.getPosition().x * 0.25);
    headingText.setStyle(headingText.Underlined);

    paragraphText.setFont(Global::tutorialFont);
    paragraphText.setFillColor(sf::Color::Black);
    paragraphText.setCharacterSize(18);
    paragraphText.setPosition(background.getPosition().x, background.getPosition().y * 0.7);

    pageImage.setSize({ 150, 150 });
    pageImage.setPosition(background.getPosition().x, background.getPosition().y * 1.2);
    pageImage.setFillColor(sf::Color::White);
    pageImage.setOrigin(pageImage.getSize().x / 2, pageImage.getSize().y / 2);
    pageImage.setOrigin(pageImage.getGlobalBounds().width / 2, pageImage.getGlobalBounds().height / 2);

    nextPageButton.setFillColor(sf::Color::Black);
    nextPageButton.setSize({ 100, 50 });
    nextPageButton.setPosition(background.getPosition().x * 1.5, background.getPosition().y * 1.7);
    nextPageButton.setOrigin(nextPageButton.getSize().x / 2, nextPageButton.getSize().y / 2);

    lastPageButton.setFillColor(sf::Color::Black);
    lastPageButton.setSize({ 100, 50 });
    lastPageButton.setPosition(background.getPosition().x * 0.5, background.getPosition().y * 1.7);
    lastPageButton.setOrigin(lastPageButton.getSize().x / 2, lastPageButton.getSize().y / 2);

    exitButton.setFillColor(sf::Color::Red);
    exitButton.setSize({ 50, 50 });
    exitButton.setPosition(background.getPosition().x, background.getPosition().y * 1.7); 
    exitButton.setOrigin(exitButton.getSize().x / 2, exitButton.getSize().y / 2);

    nextText.setFont(Global::tutorialFont);
    nextText.setFillColor(sf::Color::White);
    nextText.setCharacterSize(25);
    nextText.setPosition(nextPageButton.getPosition().x, nextPageButton.getPosition().y);
    nextText.setString("Next");

    lastText.setFont(Global::tutorialFont);
    lastText.setFillColor(sf::Color::White);
    lastText.setCharacterSize(25);
    lastText.setPosition(lastPageButton.getPosition().x, lastPageButton.getPosition().y);
    lastText.setString("Last");

    exitText.setFont(Global::tutorialFont);
    exitText.setFillColor(sf::Color::White);
    exitText.setCharacterSize(30);
    exitText.setPosition(exitButton.getPosition().x, exitButton.getPosition().y);
    exitText.setString("X");

}

void TutorialScreen::HandleEvent(sf::Event event, bool& exit)
{
    sf::Vector2f mousePos = Global::GetMousePos(*GameManager::GetWindow());
    if (nextPageButton.getGlobalBounds().contains(mousePos))
    {
        NextPage();
    }
    if (lastPageButton.getGlobalBounds().contains(mousePos))
    {
        LastPage();
    }
    if (exitButton.getGlobalBounds().contains(mousePos))
    {
        Exit(exit);
    }
}

void TutorialScreen::Update()
{

    if (currentPage < headings.size())
    {
        headingText.setString(headings[currentPage]);
        headingText.setOrigin(headingText.getLocalBounds().width / 2, headingText.getLocalBounds().height / 2);
    }

    if (currentPage < paragraphs.size())
    {
        ParagraphTextDelay();
    }

    if (currentPage < textures.size())
    {
        sf::Texture& texture = textures[currentPage];

        pageImage.setTexture(&texture);

        pageImage.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
    }
}

void TutorialScreen::Draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(headingText);
    window.draw(paragraphText);
    window.draw(pageImage);
    window.draw(exitButton);
    window.draw(exitText);
    exitText.setOrigin(exitText.getGlobalBounds().width / 2, exitText.getGlobalBounds().height / 2);
    if (currentPage < pages.size())
    {
        window.draw(nextPageButton);
        window.draw(nextText);
        nextText.setOrigin(nextText.getGlobalBounds().width / 2, nextText.getGlobalBounds().height / 2);
    }
    if (currentPage > 0)
    {
        window.draw(lastPageButton);
        window.draw(lastText);
        lastText.setOrigin(lastText.getGlobalBounds().width / 2, lastText.getGlobalBounds().height / 2);
    }
  
}

void TutorialScreen::AddPage(const std::string& heading, const std::string& paragraph, const sf::Texture& texture)
{
    headings.push_back(heading);
    paragraphs.push_back(paragraph);
    textures.push_back(texture);
}

void TutorialScreen::NextPage()
{
    if (currentPage < pages.size() - 1)
    {
        currentPage++;
        paragraphText.setString("");
        revealTimer.restart();
    }
}

void TutorialScreen::LastPage()
{
    if (currentPage >0)
    {
        currentPage--;
        paragraphText.setString("");
        revealTimer.restart();
    }
}

void TutorialScreen::Exit(bool& exit)
{
    exit = false;
    paragraphText.setString("");
    revealTimer.restart();
    currentPage = 0;
}


void TutorialScreen::ParagraphTextDelay()
{
    if (currentPage < paragraphs.size())
    {
        if (paragraphText.getString().getSize() < paragraphs[currentPage].size() && revealTimer.getElapsedTime() >= revealDelay) 
        {
            paragraphText.setString(paragraphs[currentPage].substr(0, paragraphText.getString().getSize() + 1));
            revealTimer.restart();
        }
        paragraphText.setOrigin(paragraphText.getLocalBounds().width / 2, paragraphText.getLocalBounds().height / 2);
    }
}
