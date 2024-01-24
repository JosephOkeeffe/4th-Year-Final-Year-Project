#include "Base.h"
#include "HUD.h"

Base::Base(sf::Vector2f pos)
{
	textureRect = { currentFrameX, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("base"), body, textureRect, 1.8);
	body.setPosition(pos);
	BuildingUI::Activate({ body.getPosition().x, body.getPosition().y + 80 });
	BuildingUI::Deactivate();
}

void Base::MouseUp()
{
	sf::Vector2f mousePos = Global::GetWindowMousePos(*GetWindow(), *GetView());
	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		SelectBuilding();
		CheckIfSelected();
	}
	BuildingUI::BuildMenu(*GetWindow(), *GetView());
}
void Base::CheckIfSelected()
{
	if (GetSelected())
	{
		BuildingUI::Activate({ body.getPosition().x, body.getPosition().y + 80  });
		Display_Text("Base Selected");
		body.setColor(sf::Color(128, 128, 128));
	}
	else
	{
		HUD::isActive = false;
		BuildingUI::Deactivate();
		body.setColor(sf::Color::White);
	}
}

