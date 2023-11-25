#include <iostream>
#include "HUD.h"
#include "Globals.h"
#include "ResourceManagement.h"
#include "GameState.h"


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

	Button shopButton(window, sf::Vector2f(150, 
										bottomRectangle.getPosition().y + (bottomRectangle.getSize().y / 2)), 
										sf::Vector2f(100, 100), 
										sf::Color::White, 
										sf::Color::Magenta, 
										font,
										Textures::GetInstance().GetTexture("shop"));

	shopButton.setLabel("Shop", font, 50, sf::Color::Black);
	shopButton.setCallback([]() 
		{
			ResourceManagement::isPlacingShop = true;
		});


	Button editMapButton(window, sf::Vector2f(50,
		bottomRectangle.getPosition().y + (bottomRectangle.getSize().y / 2)),
		sf::Vector2f(50, 50),
		sf::Color::White,
		sf::Color::Magenta,
		font,
		Textures::GetInstance().GetTexture("edit"));

	editMapButton.setLabel("Edit", font, 30, sf::Color(0,0,0,150));
	editMapButton.setCallback([]()
		{
			// Make pallette class for level editor
			
		});


	 
	coinSprite.setTexture(Textures::GetInstance().GetTexture("coin"));
	coinSprite.setOrigin(coinSprite.getGlobalBounds().width / 2, coinSprite.getGlobalBounds().height / 2);
	coinSprite.setPosition(Global::S_WIDTH * 0.95, Global::S_HEIGHT - bottomRectangle.getSize().y + 20);
	coinSprite.setScale(0.1, 0.1);

	coinsText.setFont(font);
	coinsText.setCharacterSize(24);
	coinsText.setOrigin(coinsText.getCharacterSize() / 2, coinsText.getCharacterSize() / 2);
	coinsText.setPosition(coinSprite.getPosition().x + 30, coinSprite.getPosition().y);

	buttons.push_back(shopButton);
	buttons.push_back(editMapButton);
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
