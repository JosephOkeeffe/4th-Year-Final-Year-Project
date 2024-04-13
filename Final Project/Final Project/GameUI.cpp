#include "GameUI.h"
#include "Game.h"

GameUI::GameUI()
{
	Init();
}

void GameUI::Init()
{
	isMenuOpen = false;
	sf::Color colour = sf::Color::White;
	colour.a = 100;

	arrow.setSize({ 55,99 });
	arrow.setPosition(Global::S_WIDTH * 0.94, Global::S_HEIGHT / 2);
	arrow.setTexture(&Textures::GetInstance().GetTexture("ui-arrow"));
	arrow.setOrigin(arrow.getSize().x / 2, arrow.getSize().y / 2);
	arrow.setScale(0.3, 0.3);
	

	background.setSize({ 339,64 });
	background.setPosition(Global::S_WIDTH, Global::S_HEIGHT / 2);
	background.setTexture(&Textures::GetInstance().GetTexture("ui-menu"));
	background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);
	background.setRotation(90);
	background.setScale(1.5, 1.5);


	inventoryBag.setSize({ 50,50 });
	inventoryBag.setPosition(background.getPosition().x, background.getPosition().y * 1.3);
	inventoryBag.setTexture(&Textures::GetInstance().GetTexture("bag"));
	inventoryBag.setOrigin(inventoryBag.getSize().x / 2, inventoryBag.getSize().y / 2);

	pause.setSize({ 50,50 });
	pause.setPosition(background.getPosition().x, background.getPosition().y * 1.5);
	pause.setTexture(&Textures::GetInstance().GetTexture("settings"));
	pause.setOrigin(pause.getSize().x / 2, pause.getSize().y / 2);

	enemyBase.setSize({ 50,50 });
	enemyBase.setPosition(background.getPosition().x, background.getPosition().y * 0.5);
	enemyBase.setTexture(&Textures::GetInstance().GetTexture("enemy-base"));
	enemyBase.setOrigin(enemyBase.getSize().x / 2, enemyBase.getSize().y / 2);

	enemyBasesLeftText.setFont(Global::font);
	enemyBasesLeftText.setPosition(enemyBase.getPosition().x, enemyBase.getPosition().y + 50);
	enemyBasesLeftText.setCharacterSize(30);
	enemyBasesLeftText.setFillColor(sf::Color::Black);
	enemyBasesLeftText.setString(std::to_string(GameManager::enemyBasesLeftAlive) + " / 4");


	background.setFillColor(colour);
	inventoryBag.setFillColor(colour);
	pause.setFillColor(colour);

	startX = background.getPosition().x;
	endX = startX - (background.getSize().y);

	uiItems.push_back(&background);
	uiItems.push_back(&inventoryBag);
	uiItems.push_back(&pause);
	uiItems.push_back(&enemyBase);

}

void GameUI::Draw(sf::RenderWindow& window)
{
	window.draw(arrow);

	for (sf::RectangleShape* shape : uiItems)
	{
		window.draw(*shape);
	}

	window.draw(enemyBasesLeftText);
}

void GameUI::HandleEvent(sf::Event event)
{
	sf::Vector2i mousePos = Global::GetLocalMousePos(*GameManager::GetWindow());

	if (arrow.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		isMenuOpen = !isMenuOpen;
		arrow.setScale(arrow.getScale().x * -1, arrow.getScale().y);
	}

	if (inventoryBag.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		Game::isInventoryOpen = !Game::isInventoryOpen;
	}
	if (pause.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		Game::currentState = GameState::PAUSED;
	}
}

void GameUI::Update()
{
	HoverArrow();
	MoveBackground();
	enemyBasesLeftText.setString(std::to_string(GameManager::enemyBasesLeftAlive) + " / 4");
	enemyBasesLeftText.setOrigin(enemyBasesLeftText.getGlobalBounds().width / 2, enemyBasesLeftText.getGlobalBounds().height / 2);
	
}

void GameUI::HoverArrow()
{
	sf::Vector2i mousePos = Global::GetLocalMousePos(*GameManager::GetWindow());

	if (arrow.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		arrow.setFillColor(sf::Color::White);
	}
	else
	{
		sf::Color colour = sf::Color::White;
		colour.a = 100;
		arrow.setFillColor(colour);
	}
}

void GameUI::MoveBackground()
{
	float moveSpeed = 1;
	sf::Color colour = sf::Color::White;
	colour.a = 100;

	if (isMenuOpen)
	{
		if (background.getPosition().x > endX)
		{
			
			for (sf::RectangleShape* shape : uiItems)
			{
				shape->move(-moveSpeed, 0);
				shape->setFillColor(sf::Color::White);

			}
			enemyBasesLeftText.move(-moveSpeed * 2, 0);
			arrow.move(-moveSpeed * 2, 0);
		}
		else
		{
			background.setPosition(endX, background.getPosition().y);
		}
	}
	else
	{
		if (background.getPosition().x < startX)
		{

			for (sf::RectangleShape* shape : uiItems)
			{
				shape->move(moveSpeed, 0);
				shape->setFillColor(colour);

			}

			enemyBasesLeftText.move(moveSpeed * 2, 0);
			arrow.move(moveSpeed * 2, 0);
		}
		else
		{
			background.setPosition(startX, background.getPosition().y);
		}
	}
}
