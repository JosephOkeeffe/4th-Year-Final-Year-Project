#include <iostream>
#include "HUD.h"
#include "Globals.h"

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
			std::cout << "Button 1 clicked!\n";
		});

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
	
}

void HUD::HandleEvents(sf::Event& event)
{
	for (Button& button : buttons)
	{
		button.handleEvent(event, window);
	}
}
