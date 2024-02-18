#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Textures.h"
#include "Globals.h"
#include "GameManager.h"

class MainMenu
{
public:

	void Init();
	void Render(sf::RenderWindow& window);
	void HandleEvents(sf::Event& event);

	
	 sf::RectangleShape menuBackground;
	 std::vector<Button> buttons;

};

