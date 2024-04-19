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
	sf::RectangleShape pauseBackground;
	sf::RectangleShape saveBackground;
	sf::RectangleShape loadBackground;
	std::vector<Button> buttons;
	ParticleSystem particleSystem;
	sf::Clock delay;

	int particleCount = 0;
	int MAX_PARTICLES = 30;

};