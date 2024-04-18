#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Textures.h"
#include "Globals.h"
#include "GameManager.h"

class HUD
{
public:

	static enum HUDState
	{
		NONE,
		TRAIN_HUD,
		BUILD_HUD
	};

	static enum UnitButtonType
	{
		NO_UNIT,
		WARRIOR,
		ARCHER,
		MINER,
		OIL_MAN,
		HAZMAT_MAN
	};

	static enum BuildingButtonType
	{
		NO_BUILDING,
		MINE,
		OIL_REFINERY,
		URANIUM_EXTRACTOR,
	};

	static void Init()
	{
		hudBackground.setFillColor(sf::Color::Red);
		hudBackground.setSize(sf::Vector2f(Global::S_WIDTH, 150));
		hudBackground.setOutlineThickness(0.5f);
		hudBackground.setOutlineColor(sf::Color(255, 255, 255, 100));
		hudBackground.setPosition(0, Global::S_HEIGHT - hudBackground.getSize().y);

		InitBuildButtons();
		InitUnitButtons();
	}

	static void Render(sf::RenderWindow& window)
	{

		if (currentState != NONE)
		{
			window.draw(hudBackground);

		}

		if (currentState == BUILD_HUD)
		{
			for (Button& button : buildingButtons)
			{
				button.update();
				button.render(window);
			}
		}
		if (currentState == TRAIN_HUD)
		{
			for (Button& button : unitButtons)
			{
				button.update();
				button.render(window);
			}

			window.draw(CreateUnitCostText(150, GameManager::warriorPurchaseCost));
			window.draw(CreateUnitCostText(260, GameManager::archerPurchaseCost));
			window.draw(CreateUnitCostText(370, GameManager::minerPurchaseCost));
			window.draw(CreateUnitCostText(480, GameManager::oilManPurchaseCost));
			window.draw(CreateUnitCostText(590, GameManager::hazmatManPurchaseCost));
		}




		CheckIfCanPurchaseUnit(GameManager::warriorPurchaseCost, canPurchaseWarrior);
		CheckIfCanPurchaseUnit(GameManager::archerPurchaseCost, canPurchaseArcher);
		CheckIfCanPurchaseUnit(GameManager::minerPurchaseCost, canPurchaseMiner);
		CheckIfCanPurchaseUnit(GameManager::oilManPurchaseCost, canPurchaseOilMan);
		CheckIfCanPurchaseUnit(GameManager::hazmatManPurchaseCost, canPurchaseHazmatMan);


		
	
	}
	static void HandleEvents(sf::Event& event)
	{
		if (currentState == BUILD_HUD)
		{
			for (Button& button : buildingButtons)
			{
				button.handleEvent(event);
			}
		}

		if (currentState == TRAIN_HUD)
		{
			for (Button& button : unitButtons)
			{
				button.handleEvent(event);
			}
		}
	}

	static void InitBuildButtons()
	{
		// Gold Mine
		Button mineButton(sf::Vector2f(150, 
			hudBackground.getPosition().y + (hudBackground.getSize().y * 0.4)), 
			sf::Vector2f(100, 100),
			sf::Color::White, 
			sf::Color(210, 210, 210),
			Textures::GetInstance().GetTexture("mine-icon")); 

		mineButton.setLabel("Mine", 30, sf::Color::Black);
		mineButton.setCallback([]()
			{
				ChangeBuildingSelected(MINE);
			});

		// Oil Extractor
		Button oilButton(sf::Vector2f(280, 
			hudBackground.getPosition().y + (hudBackground.getSize().y * 0.4)), 
			sf::Vector2f(100, 100), 
			sf::Color::White, 
			sf::Color(210, 210, 210), 
			Textures::GetInstance().GetTexture("oil-icon"));

		oilButton.setLabel("Oil Extractor", 30, sf::Color::Black);
		oilButton.setCallback([]()
			{
				ChangeBuildingSelected(OIL_REFINERY);
			});

		// Uranium Extractor
		Button reactorButton(sf::Vector2f(410,
			hudBackground.getPosition().y + (hudBackground.getSize().y * 0.4)), 
			sf::Vector2f(100, 100),
			sf::Color::White,
			sf::Color(210, 210, 210),
			Textures::GetInstance().GetTexture("reactor-icon")); 

		reactorButton.setLabel("Reactor", 30, sf::Color::Black);
		reactorButton.setCallback([]()
			{
				ChangeBuildingSelected(URANIUM_EXTRACTOR);
			});

		buildingButtons.push_back(mineButton);
		buildingButtons.push_back(oilButton);
		buildingButtons.push_back(reactorButton);

		for (Button& button : buildingButtons)
		{
			sf::Vector2f newPos;
			newPos.x = button.getButtonSprite().getPosition().x;
			newPos.y = button.getButtonSprite().getPosition().y + button.getButtonSprite().getSize().y * 0.6;

			button.centreLabel(newPos);
		}
	}

	static void InitUnitButtons()
	{

		// WARRIOR
		Button warriorButton(
			sf::Vector2f(150, hudBackground.getPosition().y + (hudBackground.getSize().y * 0.4)),
			sf::Vector2f(100, 100),
			sf::Color::White,
			sf::Color(210, 210, 210),
			Textures::GetInstance().GetTexture("warrior-icon"));

		warriorButton.setLabel("Warrior", 30, sf::Color::Black);
		warriorButton.setCallback([]()
			{
				if (canPurchaseWarrior)
				{
					ChangeUnitSelected(WARRIOR);
					GameManager::inventory.RemoveItem("Gold", GameManager::warriorPurchaseCost);
					GameManager::warriorPurchaseCost++;
				}
				else
				{
					std::cout << "Cant afford warrior \n";
				}

			});

		// ARCHER
		Button archerButton(
			sf::Vector2f(260, hudBackground.getPosition().y + (hudBackground.getSize().y * 0.4)),
			sf::Vector2f(100, 100),
			sf::Color::White,
			sf::Color(210, 210, 210),
			Textures::GetInstance().GetTexture("archer-icon"));

		archerButton.setLabel("Archer",  30, sf::Color::Black);
		archerButton.setCallback([]()
			{
				if (canPurchaseArcher)
				{
					ChangeUnitSelected(ARCHER);
					GameManager::inventory.RemoveItem("Gold", GameManager::archerPurchaseCost);
					GameManager::archerPurchaseCost++;
				}
				else
				{
					std::cout << "Cant afford archer \n";
				}
			});


		// MINER
		Button workerButton(
			sf::Vector2f(370, hudBackground.getPosition().y + (hudBackground.getSize().y * 0.4)),
			sf::Vector2f(100, 100),
			sf::Color::White,
			sf::Color(210, 210, 210),
			Textures::GetInstance().GetTexture("miner-icon"));

		workerButton.setLabel("Miner",  30, sf::Color::Black);
		workerButton.setCallback([]()
			{
				if (canPurchaseMiner)
				{
					ChangeUnitSelected(MINER);
					GameManager::inventory.RemoveItem("Gold", GameManager::minerPurchaseCost);
					GameManager::minerPurchaseCost++;
				}
				else
				{
					std::cout << "Cant afford miner \n";
				}
			});

		// OIL MAN
		Button oilManButton(
			sf::Vector2f(480, hudBackground.getPosition().y + (hudBackground.getSize().y * 0.4)),
			sf::Vector2f(100, 100),
			sf::Color::White,
			sf::Color(210, 210, 210),
			Textures::GetInstance().GetTexture("oil-man-icon"));

		oilManButton.setLabel("Oil Man", 30, sf::Color::Black);
		oilManButton.setCallback([]()
			{
				if (canPurchaseOilMan)
				{
					ChangeUnitSelected(OIL_MAN);
					GameManager::inventory.RemoveItem("Gold", GameManager::oilManPurchaseCost);
					GameManager::oilManPurchaseCost++;
				}
				else
				{
					std::cout << "Cant afford oil man \n";
				}
			});

		// HAZMAT MAN
		Button hazmatManButton(
			sf::Vector2f(590, hudBackground.getPosition().y + (hudBackground.getSize().y * 0.4)),
			sf::Vector2f(100, 100),
			sf::Color::White,
			sf::Color(210, 210, 210),
			Textures::GetInstance().GetTexture("hazmat-man-icon"));

		hazmatManButton.setLabel("Hazmat Man", 30, sf::Color::Black);
		hazmatManButton.setCallback([]()
			{
				if (canPurchaseHazmatMan)
				{
					ChangeUnitSelected(HAZMAT_MAN);
					GameManager::inventory.RemoveItem("Gold", GameManager::hazmatManPurchaseCost);
					GameManager::hazmatManPurchaseCost++;
				}
				else
				{
					std::cout << "Cant afford hazmat man \n";
				}
			});

		unitButtons.push_back(warriorButton);
		unitButtons.push_back(archerButton);
		unitButtons.push_back(workerButton);
		unitButtons.push_back(oilManButton);
		unitButtons.push_back(hazmatManButton);

		for (Button& button : unitButtons)
		{
			sf::Vector2f newPos;
			newPos.x = button.getButtonSprite().getPosition().x;
			newPos.y = button.getButtonSprite().getPosition().y + button.getButtonSprite().getSize().y * 0.6;

			button.centreLabel(newPos);
		}
	}

	static void ChangeUnitSelected(UnitButtonType name)
	{
		currentUnitSelected = name;
		currentState = NONE;
	}

	static void ChangeBuildingSelected(BuildingButtonType name)
	{
		currentBuildingSelected = name;
		currentState = NONE;
	}

	static void CheckIfCanPurchaseUnit(int price, bool& unitToCheckBool)
	{
		if (GameManager::inventory.GetInventoryItemByName("Gold") != nullptr)
		{
			currentGoldInInventory = GameManager::inventory.GetInventoryItemByName("Gold")->GetQuantity();
		}
		else
		{
			currentGoldInInventory = 0;
		}


		if (price <= 0 || currentGoldInInventory >= price)
		{
			unitToCheckBool = true;
		}
		else if (currentGoldInInventory < price)
		{
			unitToCheckBool = false;
		}
	}

	static sf::Text CreateUnitCostText(float xPos, int price )
	{
		sf::Text text;
		text.setFont(Global::font);
		text.setPosition(xPos, hudBackground.getPosition().y + (hudBackground.getSize().y * 0.2));
		text.setFillColor(sf::Color::Black);
		text.setOutlineColor(sf::Color::White);
		text.setOutlineThickness(1);
		text.setString(std::to_string(currentGoldInInventory) + "/" + std::to_string(price));
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);

		return  text;
	}

	
	static bool canPurchaseWarrior;
	static bool canPurchaseArcher;
	static bool canPurchaseMiner;
	static bool canPurchaseOilMan;
	static bool canPurchaseHazmatMan;

	

	static int currentGoldInInventory;
	static sf::RectangleShape hudBackground;
	static std::vector<Button> buildingButtons;
	static std::vector<Button> unitButtons;
	static HUDState currentState;
	static UnitButtonType currentUnitSelected;
	static BuildingButtonType currentBuildingSelected;
	
};
