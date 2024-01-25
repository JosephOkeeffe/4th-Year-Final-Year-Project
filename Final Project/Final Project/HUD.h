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
		hudBackground.setSize(sf::Vector2f(Global::S_WIDTH, 150));
		hudBackground.setOutlineThickness(0.5f);
		hudBackground.setOutlineColor(sf::Color(255, 255, 255, 100));
		hudBackground.setPosition(0, Global::S_HEIGHT - hudBackground.getSize().y);

		InitBuildButtons(window,font);

		coinSprite.setTexture(Textures::GetInstance().GetTexture("coin"));
		coinSprite.setOrigin(coinSprite.getGlobalBounds().width / 2, coinSprite.getGlobalBounds().height / 2);
		coinSprite.setPosition(Global::S_WIDTH * 0.95, Global::S_HEIGHT - hudBackground.getSize().y + 20);
		coinSprite.setScale(0.1, 0.1);

		coinsText.setFont(font);
		coinsText.setCharacterSize(24);
		coinsText.setOrigin(coinsText.getCharacterSize() / 2, coinsText.getCharacterSize() / 2);
		coinsText.setPosition(coinSprite.getPosition().x + 30, coinSprite.getPosition().y);

		


	}
	static void Render(sf::RenderWindow& window)
	{
		if (isActive)
		{
			window.draw(hudBackground);

			for (Button& button : buildingButtons)
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
		for (Button& button : buildingButtons)
		{
			button.handleEvent(event, window);
		}
	}

	static void InitBuildButtons(sf::RenderWindow& window, sf::Font& font)
	{
		Button shopButton(window,
			sf::Vector2f(150, hudBackground.getPosition().y + (hudBackground.getSize().y * 0.4)), // pos
			sf::Vector2f(100, 100), // size
			sf::Color::White, // color
			sf::Color::Magenta, // click color
			font, // font
			Textures::GetInstance().GetTexture("shop")); // texture

		shopButton.setLabel("Shop", font, 30, sf::Color::Black);
		shopButton.setCallback([]()
			{
				ResourceManagement::isPlacingShop = true;
			});

		buildingButtons.push_back(shopButton);

		for (Button& button : buildingButtons)
		{
			sf::Vector2f newPos;
			newPos.x = button.getButtonSprite().getPosition().x;
			newPos.y = button.getButtonSprite().getPosition().y + button.getButtonSprite().getSize().y * 0.6;

			button.centreLabel(newPos);
		}
	}

	static void InitUnitButtons(sf::RenderWindow& window, sf::Font& font)
	{
		Button warriorButton(window,
			sf::Vector2f(260, hudBackground.getPosition().y + (hudBackground.getSize().y * 0.4)),
			sf::Vector2f(100, 100),
			sf::Color::White,
			sf::Color::Magenta,
			font,
			Textures::GetInstance().GetTexture("warrior-icon"));

		warriorButton.setLabel("Warrior", font, 30, sf::Color::Black);
		warriorButton.setCallback([]()
			{
				//ResourceManagement::isPlacingShop = true;
			});

		unitButtons.push_back(warriorButton);

		for (Button& button : unitButtons)
		{
			sf::Vector2f newPos;
			newPos.x = button.getButtonSprite().getPosition().x;
			newPos.y = button.getButtonSprite().getPosition().y + button.getButtonSprite().getSize().y * 0.6;

			button.centreLabel(newPos);
		}
	}
		
	static sf::RectangleShape hudBackground;
	static std::vector<Button> buildingButtons;
	static std::vector<Button> unitButtons;
	static sf::Text coinsText;
	static sf::Sprite coinSprite;
	static bool isActive;
	
};
