#include "MainMenu.h"
#include "Game.h"

void MainMenu::Init(sf::RenderWindow& window, sf::Font& font)
{
	menuBackground.setPosition(200, 200);
	menuBackground.setOrigin(200, 200);
	menuBackground.setSize(sf::Vector2f(400, 400));
	menuBackground.setFillColor(sf::Color::Red);

	Button playButton(window, sf::Vector2f(50,
		menuBackground.getPosition().y + (menuBackground.getSize().y / 2)),
		sf::Vector2f(50, 50),
		sf::Color::White,
		sf::Color::Magenta,
		font,
		Textures::GetInstance().GetTexture("edit"));

	playButton.setLabel("Edit", font, 30, sf::Color(0, 0, 0, 150));
	playButton.setCallback([]()
		{
			Game::currentState = GAME;
		});
	buttons.push_back(playButton);
	//buttons.push_back(levelEditorButton);
}

void MainMenu::Render(sf::RenderWindow& window)
{
	window.draw(menuBackground);

	for (Button& button : buttons)
	{
		button.update();
		button.render(window);
	}
}

void MainMenu::HandleEvents(sf::Event& event, sf::RenderWindow& window)
{
	for (Button& button : buttons)
	{
		button.handleEvent(event, window);
	}
}


