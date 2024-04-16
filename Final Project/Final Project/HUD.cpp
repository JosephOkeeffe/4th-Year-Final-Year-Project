#include "HUD.h"

sf::RectangleShape HUD::hudBackground;
std::vector<Button> HUD::buildingButtons;
std::vector<Button> HUD::unitButtons;
HUD::HUDState HUD::currentState = HUD::NONE;
HUD::UnitButtonType HUD::currentUnitSelected = HUD::NO_UNIT;
HUD::BuildingButtonType HUD::currentBuildingSelected = HUD::NO_BUILDING;
int HUD::currentGoldInInventory = 0;
bool HUD::canPurchaseWarrior = false;
bool HUD::canPurchaseArcher = false;
bool HUD::canPurchaseMiner = false;
bool HUD::canPurchaseOilMan = false;
bool HUD::canPurchaseHazmatMan = false;



