#include "BuildingUI.h"

bool BuildingUI::isActive = false;
sf::RectangleShape BuildingUI::mainRectangle;
sf::RectangleShape BuildingUI::smallRectangles[BuildingUI::numSmallRectangles];
sf::Font BuildingUI::font;
sf::Text BuildingUI::boxText[BuildingUI::numSmallRectangles];