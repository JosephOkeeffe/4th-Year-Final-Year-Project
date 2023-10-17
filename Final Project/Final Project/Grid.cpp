#include "Grid.h"

Grid::Grid()
{
}

void Grid::Init(sf::RenderWindow& window)
{
	SetupGrid();
}

void Grid::Render(sf::RenderWindow& t_window)
{
	if (showGrid)
	{
		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{
				t_window.draw(cell[row][col]);
			}
		}
	}
}

void Grid::Update(sf::Vector2i mousePos)
{
	sf::FloatRect mouseRect(sf::Vector2f(mousePos.x, mousePos.y), sf::Vector2f(1.0f, 1.0f));

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			sf::FloatRect cellRect = cell[row][col].getGlobalBounds();

			if (mouseRect.intersects(cellRect)) 
			{
				cell[row][col].setFillColor(sf::Color::Red);
			}
		}

	}
}
void Grid::SetupGrid()
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			cell[row][col].setSize(sf::Vector2f(cellSize, cellSize));
			cell[row][col].setPosition(row * cellSize, col * cellSize);
			cell[row][col].setFillColor(sf::Color::Transparent);
			cell[row][col].setOutlineColor(sf::Color(255, 255, 255, 50));
			cell[row][col].setOutlineThickness(gridThickness);
		}
	}
}
