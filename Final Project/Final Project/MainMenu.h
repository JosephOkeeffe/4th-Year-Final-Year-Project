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
	void Update();
	void HandleEvents(sf::Event& event);

	
	 sf::Sprite menuBackground;
	 sf::Sprite menuMountainsFar[2];
	 sf::Sprite menuMountainsClose[2];
	 sf::Sprite menuTreesFar[2];
	 sf::Sprite menuTreesClose[2];
	 std::vector<Button> buttons;

	 void ResetSpritePosition(sf::Sprite& sprite, float offsetX);

};

