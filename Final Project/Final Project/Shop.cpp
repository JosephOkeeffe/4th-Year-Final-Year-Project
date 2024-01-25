#include "Shop.h"

Shop::Shop(sf::Vector2f pos)
{
	textureRect = { 0, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("shop"), body, textureRect, 0.5);
	body.setPosition(pos);
}

void Shop::MouseRelease()
{
	sf::Vector2f mousePos = Global::GetWindowMousePos(*GetWindow(), *GetView());
	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		SelectBuilding();
		CheckIfSelected();
	}
}

void Shop::CheckIfSelected()
{
	if (GetSelected())
	{
		Display_Text("Shop Selected");
		body.setColor(sf::Color(128, 128, 128));
	}
	else
	{
		body.setColor(sf::Color::White);
	}
}
