#include "WinScreen.h"
#include "Game.h"

WinScreen::WinScreen() : rng(std::random_device{}())
{

    Init(); // Initialize confetti
}

void WinScreen::Init()
{
    background.setSize({ 500,500 });
    background.setFillColor(sf::Color(255, 255, 255, 200));
    background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);
    background.setPosition(Global::S_WIDTH / 2, Global::S_HEIGHT / 2);


    winText.setFont(Global::font); 
    winText.setString("You win!"); 
    winText.setCharacterSize(48);
    winText.setFillColor(sf::Color::White);
    winText.setOutlineColor(sf::Color::Black);
    winText.setOutlineThickness(2); 

    winText.setPosition(background.getPosition());

    for (int i = 0; i < 100; ++i) 
    {
        Confetti c;

        if (i % 3 == 0)
        {
            c.sprite.setTexture(Textures::GetInstance().GetTexture("egg"));
            c.sprite.setScale(0.5, 0.5);
        }
        else if (i % 3 == 1)
        {
            c.sprite.setTexture(Textures::GetInstance().GetTexture("coin"));
            c.sprite.setScale(0.3, 0.3);
        }
        else
        {
            c.sprite.setTexture(Textures::GetInstance().GetTexture("spaceship"));
            c.sprite.setTextureRect({ 0, 0, 48, 50 });
            c.sprite.setScale(2, 2);
        }
        c.sprite.setPosition(static_cast<float>(rand() % Global::S_WIDTH), static_cast<float>(rand() % Global::S_HEIGHT));
        c.sprite.setOrigin(c.sprite.getGlobalBounds().width / 2, c.sprite.getGlobalBounds().height / 2); 
        sf::Color color = c.sprite.getColor();
        color.r = (rand() % 256);
        color.g = (rand() % 256);
        color.b = (rand() % 256);
        c.sprite.setColor(color);
        c.velocity = sf::Vector2f(static_cast<float>(rand() % 200 - 100), static_cast<float>(rand() % 200 - 100)); 
        c.rotationSpeed = static_cast<float>(rand() % 200 - 100); 
        confetti.push_back(c);
    }

    homeButton.setTexture(&Textures::GetInstance().GetTexture("button1"));
    homeButton.setSize({ 150,30 });
    homeButton.setPosition(background.getPosition().x, background.getPosition().y * 1.4);
    homeButton.setOrigin(homeButton.getSize().x / 2, homeButton.getSize().y / 2);
    homeButton.setFillColor(sf::Color::Black);

    homeText.setFont(Global::font);
    homeText.setCharacterSize(30);
    homeText.setString("Home");
    homeText.setPosition(homeButton.getPosition().x, homeButton.getPosition().y - 5);
    homeText.setFillColor(sf::Color::White);
}

void WinScreen::Draw(sf::RenderWindow& window)
{
    for (Confetti& c : confetti)
    {
        window.draw(c.sprite);
    }
    window.draw(background);
    window.draw(winText);
    window.draw(homeButton);
    window.draw(homeText);

}

void WinScreen::HandleEvent(sf::Event event)
{
    sf::Vector2i mousePos = Global::GetLocalMousePos(*GameManager::GetWindow());

    if (homeButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
    {
        Game::currentState = GameState::MENU;
    }
}

void WinScreen::Update()
{
    winText.setOrigin(winText.getGlobalBounds().width / 2, winText.getGlobalBounds().height / 2);
    homeText.setOrigin(homeText.getGlobalBounds().width / 2, homeText.getGlobalBounds().height / 2);

    for (Confetti& c : confetti)
    {
        c.sprite.move(c.velocity * 0.01f);

        // Bounce off screen edges
        if (c.sprite.getPosition().x < 0)
        {
            c.sprite.setPosition(Global::S_WIDTH, c.sprite.getPosition().y);
        }
        else if (c.sprite.getPosition().x > Global::S_WIDTH)
        {
            c.sprite.setPosition(0, c.sprite.getPosition().y);
        }
        if (c.sprite.getPosition().y < 0)
        {
            c.sprite.setPosition(c.sprite.getPosition().x, Global::S_HEIGHT);
        }
        else if (c.sprite.getPosition().y > Global::S_HEIGHT)
        {
            c.sprite.setPosition(c.sprite.getPosition().x, 0);
        }

        c.sprite.rotate(c.rotationSpeed * 0.01f);

        sf::Color color = c.sprite.getColor();


        color.r += 0.05;
        color.g += 0.02;
        color.b += 0.01;
        c.sprite.setColor(color);
    }
}

