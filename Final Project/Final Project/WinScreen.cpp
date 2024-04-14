#include "WinScreen.h"

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
        c.sprite.setOrigin(c.sprite.getGlobalBounds().width / 2, c.sprite.getGlobalBounds().height / 2); // Center origin
        sf::Color color = c.sprite.getColor();
        color.r = (rand() % 256);
        color.g = (rand() % 256);
        color.b = (rand() % 256);
        c.sprite.setColor(color);
        c.velocity = sf::Vector2f(static_cast<float>(rand() % 200 - 100), static_cast<float>(rand() % 200 - 100)); // Random velocity
        c.rotationSpeed = static_cast<float>(rand() % 200 - 100); 
        confetti.push_back(c);
    }
}

void WinScreen::Draw(sf::RenderWindow& window)
{
    for (Confetti& c : confetti)
    {
        window.draw(c.sprite);
    }
    window.draw(background);
    window.draw(winText);

}

void WinScreen::HandleEvent(sf::Event event)
{
}

void WinScreen::Update()
{
    winText.setOrigin(winText.getGlobalBounds().width / 2, winText.getGlobalBounds().height / 2);

    // Update confetti
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

