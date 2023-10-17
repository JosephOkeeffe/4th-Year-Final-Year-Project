#pragma once
#include <SFML/Graphics.hpp>
#include "GameView.h"

class Grid
{
public:	
	Grid();
	void Init(sf::RenderWindow& window);
	void Render(sf::RenderWindow& t_window);
	void Update(sf::Vector2i mousePos);
	void SetupGrid();

	bool showGrid = true;

	static const int ROWS = 60;
	static const int COLS = 30;
	int cellSize = 100;
	float gridThickness = 0.5;
	sf::RectangleShape cell[ROWS][COLS];

};

