#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Textures.h"
#include "Globals.h"
#include "ResourceManagement.h"
#include "GameState.h"

class HUD
{
public:

	static void Init(sf::RenderWindow& window, sf::Font& font)
	{
		hudBackground.setFillColor(sf::Color::Red);
		hudBackground.setSize(sf::Vector2f(Global::S_WIDTH, 100));
		hudBackground.setOutlineThickness(0.5f);
		hudBackground.setOutlineColor(sf::Color(255, 255, 255, 100));
		hudBackground.setPosition(0, Global::S_HEIGHT - hudBackground.getSize().y);

		Button shopButton(window, sf::Vector2f(150,
			hudBackground.getPosition().y + (hudBackground.getSize().y / 2)),
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

		coinSprite.setTexture(Textures::GetInstance().GetTexture("coin"));
		coinSprite.setOrigin(coinSprite.getGlobalBounds().width / 2, coinSprite.getGlobalBounds().height / 2);
		coinSprite.setPosition(Global::S_WIDTH * 0.95, Global::S_HEIGHT - hudBackground.getSize().y + 20);
		coinSprite.setScale(0.1, 0.1);

		coinsText.setFont(font);
		coinsText.setCharacterSize(24);
		coinsText.setOrigin(coinsText.getCharacterSize() / 2, coinsText.getCharacterSize() / 2);
		coinsText.setPosition(coinSprite.getPosition().x + 30, coinSprite.getPosition().y);

		buttons.push_back(shopButton);
	}
	static void Render(sf::RenderWindow& window)
	{
		if (isActive)
		{
			window.draw(hudBackground);

			for (Button& button : buttons)
			{
				button.update();
				button.render(window);
			}

			coinsText.setString("x" + std::to_string(ResourceManagement::GetCoins()));
			window.draw(coinSprite);
			window.draw(coinsText);
		}
	}
	static void HandleEvents(sf::Event& event, sf::RenderWindow& window)
	{
		for (Button& button : buttons)
		{
			button.handleEvent(event, window);
		}
	}
		
	static sf::RectangleShape hudBackground;
	static std::vector<Button> buttons;
	static sf::Text coinsText;
	static sf::Sprite coinSprite;
	static bool isActive;
	
};
