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


	// Initialize rotate handle
	rotateHandle.setSize(sf::Vector2f(20.0f, 20.0f));
	rotateHandle.setOrigin(rotateHandle.getSize() / 2.0f);
	rotateHandle.setFillColor(sf::Color::Green);  
	rotateHandle.setOutlineThickness(2);  
	rotateHandle.setOutlineColor(sf::Color::Black);
	rotateHandle.setTexture(&Textures::GetInstance().GetTexture("rotate"));



	// Initialize scale handle
	scaleHandle.setSize(sf::Vector2f(20.0f, 20.0f));
	scaleHandle.setOrigin(scaleHandle.getSize() / 2.0f);
	scaleHandle.setFillColor(sf::Color::Blue);
	scaleHandle.setOutlineThickness(2);
	scaleHandle.setOutlineColor(sf::Color::Black);
	scaleHandle.setTexture(&Textures::GetInstance().GetTexture("scale"));

	rotationHandleOffset = sf::Vector2f(30.0f, -30.0f);

	resizeHandleOffset = sf::Vector2f(-30.0f, 30.0f); 

	rotateHandle.setPosition(body.getPosition() + rotationHandleOffset);
	scaleHandle.setPosition(body.getPosition() + resizeHandleOffset);

	shader.InitShader("SelectedShader.frag");



}

void Headquarters::MouseRelease()
{

	int tempX = 200 / Global::CELL_SIZE;
	int tempY = 200 / Global::CELL_SIZE;
	GameManager::tiles[tempX][tempY].SetTileType(TILE_USED_UP);

	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());

	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		if (GetSelectedStatus())
		{
			DeselectBuilding();
		}
		else
		{
			SelectBuilding();
			SoundManager::GetInstance().PlaySound("select", 50, false);
		}
		ChangeSelectedColour();
	}

	BuildingUI::BuildMenu(*GameManager::GetWindow(), *GameManager::GetView());
	BuildingUI::TrainMenu(*GameManager::GetWindow(), *GameManager::GetView());
}
void Headquarters::Update()
{
	Buildings::Update();

	//


	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
		if (GetPlacedStatus() && GetSelectedStatus())
		{
			HandleRightClick(mousePos);
		}
	}
	else
	{
		HandleRightRelease();
	}

	if (isScaling || isRotating)
	{
		sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*GameManager::GetWindow()));
		HandleMouseMovement(mousePosition);
	}

	shader.Update();
	ChangeSelectedColour();
}
void Headquarters::Draw()
{
	particleSystem.draw(*GameManager::GetWindow());

	GameManager::GetWindow()->draw(detectionCircle);

	if (GetSelectedStatus())
	{
		GameManager::GetWindow()->draw(body, &shader.GetShader());
	}
	else
	{
		GameManager::GetWindow()->draw(body);
	}

	if (GetPlacedStatus() && GetSelectedStatus())
	{
		GameManager::GetWindow()->draw(rotateHandle);
		GameManager::GetWindow()->draw(scaleHandle);
	}
}
void Headquarters::ChangeSelectedColour()
{
	if (GetSelectedStatus())
	{
		BuildingUI::Activate({ body.getPosition().x, body.getPosition().y + 80  });
		body.setColor(sf::Color(128, 128, 128));
	}
	else
	{
		HUD::currentState = HUD::NONE;
		BuildingUI::Deactivate();
	}
}


void Headquarters::HandleRightClick(sf::Vector2f mousePosition)
{
	if (rotateHandle.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		isRotating = true;
		return;
	}

	if (scaleHandle.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		isScaling = true;
		return;
	}
}

void Headquarters::UpdateControlHandles()
{
	rotateHandle.setPosition(body.getPosition() + rotationHandleOffset);
	scaleHandle.setPosition(body.getPosition() + resizeHandleOffset);
}

void Headquarters::HandleMouseMovement(sf::Vector2f mousePosition)
{

	if (isRotating)
	{
		float angle = atan2(mousePosition.y - body.getPosition().y, mousePosition.x - body.getPosition().x) * (180 / 3.14159265);
		body.setRotation(angle);
	}

	if (isScaling)
	{
		sf::Vector2f newSize = (mousePosition - body.getPosition());
		body.setScale(newSize.x * 0.1, newSize.y * 0.1);
	}

	UpdateControlHandles();
}

void Headquarters::HandleRightRelease()
{
	isRotating = false;
	isScaling = false;
}
