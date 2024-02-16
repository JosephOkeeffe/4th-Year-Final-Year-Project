#include "UraniumExtractor.h"

UraniumExtractor::UraniumExtractor(sf::Vector2f pos)
{
	textureRect = { 0, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("uranium"), body, textureRect, 1.8);
	body.setPosition(pos);
	body.setScale(0.8, 0.8);
	SetBuildingType(URANIUM_EXTRACTOR_BUILDING);
	animationSpeed = 0.05;
}

void UraniumExtractor::MouseRelease()
{
	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
	sf::Vector2i currentCell = Global::GetCurrentCell(*GameManager::GetWindow(), *GameManager::GetView());

	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		if (!GetPlacedStatus())
		{
			if (CheckIfCanBePlaced(currentCell))
			{
				PlaceBuilding();
				GameManager::tiles[currentCell.x][currentCell.y].SetTileType(TILE_USED_UP);
			}
		}
	}
}

void UraniumExtractor::Draw()
{
	GameManager::GetWindow()->draw(detectionCircle);
	GameManager::GetWindow()->draw(body);

	if (GetPlacedStatus() && isBeingUsed)
	{
		GameManager::GetWindow()->draw(resourceText);
		GameManager::GetWindow()->draw(background);
		GameManager::GetWindow()->draw(resource);
	}
}

void UraniumExtractor::Update()
{
	UpdateBuildings();
	deltaTime = clock.restart();
}

void UraniumExtractor::GenerateUranium()
{
	background.setPosition(body.getPosition().x, body.getPosition().y - 65);
	resource.setPosition(background.getPosition());
	resource.setFillColor(sf::Color::Yellow);


	if (currentWidth < maxWidth)
	{
		resourceText.setPosition(background.getPosition().x + background.getSize().x * 0.6, background.getPosition().y - 15);
		resourceText.setString(std::to_string(static_cast<int>(currentWidth)));

		float increaseAmount = fillSpeed * deltaTime.asSeconds();
		currentWidth = std::min(currentWidth + increaseAmount, maxWidth);
		resource.setSize(sf::Vector2f(currentWidth, barSize.y));
		isEmpty = false;
	}

	if (currentWidth >= maxWidth)
	{
		resourceText.setPosition(background.getPosition().x, background.getPosition().y - 50);

		isFull = true;

	}
}

void UraniumExtractor::DepositUranium()
{
	background.setPosition(body.getPosition().x, body.getPosition().y - 65);
	resource.setPosition(background.getPosition());
	resource.setFillColor(sf::Color::Red);

	if (currentWidth > 0)
	{
		resourceText.setPosition(background.getPosition().x + background.getSize().x * 0.6, background.getPosition().y - 15);
		resourceText.setString(std::to_string(static_cast<int>(currentWidth)));

		float decreaseAmount = fillSpeed * deltaTime.asSeconds();
		currentWidth = std::max(currentWidth - decreaseAmount, 0.f);
		resource.setSize(sf::Vector2f(currentWidth, barSize.y));
		isFull = false;
	}

	if (currentWidth <= 0)
	{
		resourceText.setPosition(background.getPosition().x, background.getPosition().y - 50);

		isEmpty = true;
	}
}

