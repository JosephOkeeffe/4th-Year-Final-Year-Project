#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Textures.h"

class HUD
{
public:

	HUD(sf::RenderWindow& window, sf::Font& font);
	void Init();
	void Render(sf::RenderWindow& window);
	void HandleEvents(sf::Event& event);
		
	sf::RectangleShape bottomRectangle;

	sf::RenderWindow& window;
	sf::Font& font;

	//Button button1{window, font, {200,200}, {100,100},sf::Color::Black, sf::Color::Green}

	std::vector<Button> buttons;

	sf::Text coinsText;
	sf::Sprite coinSprite;
	
};

