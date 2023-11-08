#include <iostream>
#include "HUD.h"
#include "Globals.h"
#include "ResourceManagement.h"


HUD::HUD(sf::RenderWindow& window, sf::Font& font) : window(window), font(font)
{

}

void HUD::Init()
{
	bottomRectangle.setFillColor(sf::Color::Red);
	bottomRectangle.setSize(sf::Vector2f(Global::S_WIDTH, 100));
	bottomRectangle.setOutlineThickness(0.5f);
	bottomRectangle.setOutlineColor(sf::Color(255, 255, 255, 100));
	bottomRectangle.setPosition(0, Global::S_HEIGHT - bottomRectangle.getSize().y);

	Button button1(window, sf::Vector2f(150, bottomRectangle.getPosition().y + (bottomRectangle.getSize().y / 2)), sf::Vector2f(200, 50), sf::Color::Green, sf::Color::Magenta, font);
	button1.setLabel("Warrior", font, 50, sf::Color::White);
	button1.setCallback([]() 
		{
			ResourceManagement::AddCoins(2);
			ResourceManagement::isPlacingShop = true;
			std::cout << "Coins " << ResourceManagement::GetCoins() << "\n";
		});



	 
	coinSprite.setOrigin(coinSprite.getGlobalBounds().width / 2, coinSprite.getGlobalBounds().height / 2);
	coinSprite.setPosition(Global::S_WIDTH * 0.95, Global::S_HEIGHT - bottomRectangle.getSize().y + 20);
	coinSprite.setScale(0.1, 0.1);

	coinsText.setFont(font);
	coinsText.setCharacterSize(24);
	coinsText.setOrigin(coinsText.getCharacterSize() / 2, coinsText.getCharacterSize() / 2);
	coinsText.setPosition(coinSprite.getPosition().x + 30, coinSprite.getPosition().y);

	buttons.push_back(button1);
}



void HUD::Render(sf::RenderWindow& window)
{
	window.draw(bottomRectangle);

	for (Button& button : buttons) 
	{
		button.update();
		button.render(window);
	}

	coinsText.setString("x" + std::to_string(ResourceManagement::GetCoins()));
	window.draw(coinSprite);
	window.draw(coinsText);

	
}

void HUD::HandleEvents(sf::Event& event)
{
	for (Button& button : buttons)
	{
		button.handleEvent(event, window);
	}
}
