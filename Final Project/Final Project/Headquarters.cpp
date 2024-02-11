#include "Headquarters.h"
#include "HUD.h"

Headquarters::Headquarters(sf::Vector2f pos)
{
	textureRect = { currentFrameX, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("hq"), body, textureRect, 1.8);
	body.setPosition(pos);
	BuildingUI::Activate({ body.getPosition().x, body.getPosition().y + 80 });
	BuildingUI::Deactivate();
	SetBuildingType(HEADQUATERS_BUILDING);
	//detectionRadius = 0;
}

void Headquarters::MouseRelease()
{
	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
	sf::Vector2i currentCell = Global::GetCurrentCell(*GameManager::GetWindow(), *GameManager::GetView());

	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		if (CheckIfSelected())
		{
			DeselectBuilding();
		}
		else
		{
			SelectBuilding();
		}
		ChangeSelectedColour();
	}
	/*else
	{
		if (!BuildingUI::mainRectangle.getGlobalBounds().contains(sf::Vector2f(mousePos)))
		{
			DeselectBuilding();

		}
	}*/
	BuildingUI::BuildMenu(*GameManager::GetWindow(), *GameManager::GetView());
	BuildingUI::TrainMenu(*GameManager::GetWindow(), *GameManager::GetView());
}
void Headquarters::Update()
{
	ChangeSelectedColour();
	UpdateDetectionCircle();
}
void Headquarters::ChangeSelectedColour()
{
	if (CheckIfSelected())
	{
		BuildingUI::Activate({ body.getPosition().x, body.getPosition().y + 80  });
		body.setColor(sf::Color(128, 128, 128));
	}
	else
	{
		HUD::currentState = HUD::NONE;
		BuildingUI::Deactivate();
		body.setColor(sf::Color::White);
	}
}

