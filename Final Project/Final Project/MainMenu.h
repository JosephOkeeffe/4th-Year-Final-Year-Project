#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Textures.h"

class MainMenu
{
public:

	void Init(sf::RenderWindow& window, sf::Font& font);
	void Render(sf::RenderWindow& window);
	void HandleEvents(sf::Event& event, sf::RenderWindow& window);

	
	 sf::RectangleShape menuBackground;
	 std::vector<Button> buttons;

};

