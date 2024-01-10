#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Textures.h"

class PauseMenu
{
public:

	void Init(sf::RenderWindow& window, sf::Font& font);
	void Render(sf::RenderWindow& window);
	void HandleEvents(sf::Event& event, sf::RenderWindow& window);
	void SetupSave();
	void SetupLoad();
	bool saveMenu = false;
	bool loadMenu = false;
	sf::RectangleShape pauseBackground;
	sf::RectangleShape saveBackground;
	sf::RectangleShape loadBackground;
	std::vector<Button> buttons;
	std::vector<Button> saveButtons;
	std::vector<Button> loadButtons;

};