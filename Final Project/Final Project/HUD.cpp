#include "HUD.h"

sf::RectangleShape HUD::hudBackground;
std::vector<Button> HUD::buildingButtons;
std::vector<Button> HUD::unitButtons;
HUD::HUDState HUD::currentState = HUD::NONE;
HUD::UnitButtonType HUD::currentUnitSelected = HUD::NO_UNIT;
HUD::BuildingButtonType HUD::currentBuildingSelected = HUD::NO_BUILDING;


