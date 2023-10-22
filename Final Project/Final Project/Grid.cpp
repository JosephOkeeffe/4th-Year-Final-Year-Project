//#include "Grid.h"
//
//Grid::Grid(sf::RenderWindow& t_window) : window(t_window)
//{
//}
//
//void Grid::Init()
//{
//	SetupGrid();
//}
//
//void Grid::Render()
//{
//	if (showGrid)
//	{
//		for (int row = 0; row < ROWS; row++)
//		{
//			for (int col = 0; col < COLS; col++)
//			{
//				window.draw(cell[row][col]);
//			}
//		}
//	}
//}
//
//void Grid::Update()
//{
//	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//	sf::Vector2f localMousePos = window.mapPixelToCoords(mousePos);
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
//	{
//		for (int row = 0; row < ROWS; row++)
//		{
//			for (int col = 0; col < COLS; col++)
//			{
//				if (cell[row][col].getGlobalBounds().contains(sf::Vector2f(localMousePos)))
//				{
//					cell[row][col].setFillColor(sf::Color::Red);
//				}
//			}
//		}
//	}
//}
//void Grid::SetupGrid()
//{
//	for (int row = 0; row < ROWS; row++)
//	{
//		for (int col = 0; col < COLS; col++)
//		{
//			cell[row][col].setSize(sf::Vector2f(cellSize, cellSize));
//			cell[row][col].setPosition(row * cellSize, col * cellSize);
//			cell[row][col].setFillColor(sf::Color::Transparent);
//			cell[row][col].setOutlineColor(sf::Color(255, 255, 255, 50));
//			cell[row][col].setOutlineThickness(gridThickness);
//		}
//	}
//}
