#include "HUD.h"

sf::RectangleShape HUD::hudBackground;
std::vector<Button> HUD::buildingButtons;
std::vector<Button> HUD::unitButtons;
sf::Text HUD::coinsText;
sf::Sprite HUD::coinSprite;
HUD::HUDState HUD::currentState = HUD::NONE;
HUD::UNIT_IDS HUD::currentUnitSelected = HUD::NO_UNIT;
HUD::BUILDING_IDS HUD::currentBuildingSelected = HUD::NO_BUILDING;


