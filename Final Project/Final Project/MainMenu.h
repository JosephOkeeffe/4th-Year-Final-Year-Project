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

	void SetupButtons();

	sf::Text titleText;
	sf::Sprite menuBackground;
	sf::Sprite menuMountainsFar[2];
	sf::Sprite menuMountainsClose[2];
	sf::Sprite menuTreesFar[2];
	sf::Sprite menuTreesClose[2];
	std::vector<Button> buttons;
	std::vector<sf::Text> individualLetterTexts;

	float originalYPositions[22];

	void ResetSpritePosition(sf::Sprite& sprite, float offsetX);

};

