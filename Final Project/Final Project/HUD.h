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

	static enum HUDState
	{
		NONE,
		TRAIN_HUD,
		BUILD_HUD
	};

	static enum UNIT_IDS
	{
		NO_UNIT,
		WARRIOR,
		ARCHER
	};

	static void Init(sf::RenderWindow& window, sf::Font& font)
	{
		hudBackground.setFillColor(sf::Color::Red);
		hudBackground.setSize(sf::Vector2f(Global::S_WIDTH, 150));
		hudBackground.setOutlineThickness(0.5f);
		hudBackground.setOutlineColor(sf::Color(255, 255, 255, 100));
		hudBackground.setPosition(0, Global::S_HEIGHT - hudBackground.getSize().y);

		InitBuildButtons(window,font);
		InitUnitButtons(window,font);

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

		if (currentState != NONE)
		{
			window.draw(hudBackground);

			coinsText.setString("x" + std::to_string(ResourceManagement::GetCoins()));
			window.draw(coinSprite);
			window.draw(coinsText);
		}

		if (currentState == BUILD_HUD)
		{
			for (Button& button : buildingButtons)
			{
				button.update();
				button.render(window);
			}
		}
		if (currentState == TRAIN_HUD)
		{
			for (Button& button : unitButtons)
			{
				button.update();
				button.render(window);
			}
		}
	}
	static void HandleEvents(sf::Event& event, sf::RenderWindow& window)
	{
		if (currentState == BUILD_HUD)
		{
			for (Button& button : buildingButtons)
			{
				button.handleEvent(event, window);
			}
		}

		if (currentState == TRAIN_HUD)
		{
			for (Button& button : unitButtons)
			{
				button.handleEvent(event, window);
			}
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
			sf::Vector2f(150, hudBackground.getPosition().y + (hudBackground.getSize().y * 0.4)),
			sf::Vector2f(100, 100),
			sf::Color::White,
			sf::Color::Magenta,
			font,
			Textures::GetInstance().GetTexture("warrior-icon"));

		warriorButton.setLabel("Warrior", font, 30, sf::Color::Black);
		warriorButton.setCallback([]()
			{
				ChangeUnitSelected(WARRIOR);
			});

		Button archerButton(window,
			sf::Vector2f(260, hudBackground.getPosition().y + (hudBackground.getSize().y * 0.4)),
			sf::Vector2f(100, 100),
			sf::Color::White,
			sf::Color::Magenta,
			font,
			Textures::GetInstance().GetTexture("archer-icon"));

		archerButton.setLabel("Archer", font, 30, sf::Color::Black);
		archerButton.setCallback([]()
			{
				ChangeUnitSelected(ARCHER);
			});

		unitButtons.push_back(warriorButton);
		unitButtons.push_back(archerButton);

		for (Button& button : unitButtons)
		{
			sf::Vector2f newPos;
			newPos.x = button.getButtonSprite().getPosition().x;
			newPos.y = button.getButtonSprite().getPosition().y + button.getButtonSprite().getSize().y * 0.6;

			button.centreLabel(newPos);
		}
	}

	static void ChangeUnitSelected(UNIT_IDS name)
	{
		currentUnitSelected = name;
		currentState = NONE;
	}
	

	static sf::RectangleShape hudBackground;
	static std::vector<Button> buildingButtons;
	static std::vector<Button> unitButtons;
	static sf::Text coinsText;
	static sf::Sprite coinSprite;
	static HUDState currentState;
	static UNIT_IDS currentUnitSelected;
	
};
