#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Textures.h"
#include "ParticleSystem.h"

class PauseMenu
{
public:

	void Init();
	void Render(sf::RenderWindow& window);
	void HandleEvents(sf::Event& event);
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
	ParticleSystem particleSystem;
	sf::Clock delay;

};