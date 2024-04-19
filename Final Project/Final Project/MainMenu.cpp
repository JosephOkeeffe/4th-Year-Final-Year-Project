#include "MainMenu.h"
#include "Game.h"

void MainMenu::Init()
{

	menuBackground.setTexture(Textures::GetInstance().GetTexture("menu-bg"));
	menuBackground.setOrigin(menuBackground.getLocalBounds().width / 2, menuBackground.getLocalBounds().height / 2);
	menuBackground.setPosition(Global::S_WIDTH / 2, Global::S_HEIGHT / 2);
	menuBackground.setScale(sf::Vector2f(Global::S_WIDTH / menuBackground.getGlobalBounds().width, Global::S_HEIGHT / menuBackground.getGlobalBounds().height));

	for (int i = 0; i < 2; ++i)
	{
		menuMountainsFar[i].setTexture(Textures::GetInstance().GetTexture("menu-mountain-far"));
		menuMountainsFar[i].setOrigin(menuMountainsFar[i].getLocalBounds().width / 2, menuMountainsFar[i].getLocalBounds().height / 2);
		menuMountainsFar[i].setPosition(Global::S_WIDTH * 0.3, Global::S_HEIGHT / 2);
		menuMountainsFar[i].setScale(sf::Vector2f(Global::S_WIDTH / menuMountainsFar[i].getGlobalBounds().width, Global::S_HEIGHT / menuMountainsFar[i].getGlobalBounds().height));

		menuMountainsClose[i].setTexture(Textures::GetInstance().GetTexture("menu-mountain-close"));
		menuMountainsClose[i].setOrigin(menuMountainsClose[i].getLocalBounds().width / 2, menuMountainsClose[i].getLocalBounds().height / 2);
		menuMountainsClose[i].setPosition(Global::S_WIDTH / 2 , Global::S_HEIGHT / 2);
		menuMountainsClose[i].setScale(sf::Vector2f(Global::S_WIDTH / menuMountainsClose[i].getGlobalBounds().width, Global::S_HEIGHT / menuMountainsClose[i].getGlobalBounds().height));

		menuTreesFar[i].setTexture(Textures::GetInstance().GetTexture("menu-trees-far"));
		menuTreesFar[i].setOrigin(menuTreesFar[i].getLocalBounds().width / 2, menuTreesFar[i].getLocalBounds().height / 2);
		menuTreesFar[i].setPosition(Global::S_WIDTH * 0.5 , Global::S_HEIGHT * 0.4);
		menuTreesFar[i].setScale(5, 6);

		menuTreesClose[i].setTexture(Textures::GetInstance().GetTexture("menu-trees-close"));
		menuTreesClose[i].setOrigin(menuTreesClose[i].getLocalBounds().width / 2, menuTreesClose[i].getLocalBounds().height / 2);
		menuTreesClose[i].setPosition(Global::S_WIDTH * 0.6, Global::S_HEIGHT * 0.6);
		menuTreesClose[i].setScale(3, 4);
	}

	menuMountainsFar[1].setPosition((menuMountainsFar[0].getPosition().x * 2) + menuMountainsFar[0].getGlobalBounds().width / 2, Global::S_HEIGHT / 2);
	menuMountainsClose[1].setPosition((menuMountainsClose[0].getPosition().x * 2) + menuMountainsClose[0].getGlobalBounds().width / 2, Global::S_HEIGHT / 2);
	menuTreesFar[1].setPosition((menuTreesFar[0].getPosition().x * 2) + menuTreesFar[0].getGlobalBounds().width / 2, Global::S_HEIGHT * 0.4);
	menuTreesClose[1].setPosition((menuTreesClose[0].getPosition().x * 2) + menuTreesClose[0].getGlobalBounds().width / 2, Global::S_HEIGHT * 0.6);

	titleText.setFont(Global::font);
	titleText.setCharacterSize(50);
	titleText.setString("The Upper Cliff Valley");
	titleText.setOrigin(titleText.getLocalBounds().width / 2.0f, titleText.getLocalBounds().height / 2.0f);
	titleText.setPosition((Global::S_WIDTH * 0.5), Global::S_HEIGHT * 0.3);
	titleText.setFillColor(sf::Color::Black);

	for (int i = 0; i < titleText.getString().getSize(); ++i)
	{
		sf::Text letterText;
		letterText.setFont(Global::font);
		letterText.setCharacterSize(50);
		letterText.setString(std::string(1, titleText.getString()[i]));
		letterText.setOrigin(letterText.getLocalBounds().width / 2.0f, letterText.getLocalBounds().height / 2.0f);

		float xPos = titleText.getPosition().x - titleText.getOrigin().x + letterText.getLocalBounds().width / 2.0f + titleText.findCharacterPos(i).x;
		float yPos = titleText.getPosition().y;
		originalYPositions[i] = yPos;
		letterText.setPosition(xPos - Global::S_WIDTH * 0.33, yPos);

		letterText.setFillColor(sf::Color::Black);

		individualLetterTexts.push_back(letterText);
	}


	SetupButtons();


}

void MainMenu::Render(sf::RenderWindow& window)
{
	window.draw(menuBackground);
	for (int i = 0; i < 2; ++i)
	{
		window.draw(menuMountainsFar[i]);
	}

	for (int i = 0; i < 2; ++i)
	{
		window.draw(menuMountainsClose[i]);
	}

	for (int i = 0; i < 2; ++i)
	{
		window.draw(menuTreesFar[i]);
	}

	for (int i = 0; i < 2; ++i)
	{
		window.draw(menuTreesClose[i]);
	}

	if (!continueGame && !newGame)
	{
		for (Button& button : buttons)
		{
			button.render(window);
		}
	}
	 
	if (continueGame || newGame)
	{
		for (Button& button : playGameButtons)
		{
			button.render(window);
		}
	}
	

	for (const sf::Text& letterText : individualLetterTexts)
	{
		window.draw(letterText);
	}
}

void MainMenu::Update()
{
	float farSpeed = 0.1f;
	float closeSpeed = 0.5f;

	for (int i = 0; i < 2; ++i) 
	{
		menuMountainsFar[i].move(-farSpeed, 0);
		menuMountainsClose[i].move(-farSpeed, 0);
		menuTreesFar[i].move(-0.3, 0);
		menuTreesClose[i].move(-0.5, 0);

		ResetSpritePosition(menuMountainsFar[i], Global::S_WIDTH * i);
		ResetSpritePosition(menuMountainsClose[i], Global::S_WIDTH * i);
		ResetSpritePosition(menuTreesFar[i], Global::S_WIDTH * i);
		ResetSpritePosition(menuTreesClose[i], Global::S_WIDTH * i);
	}
}

void MainMenu::ResetSpritePosition(sf::Sprite& sprite, float offsetX)
{
	int x = sprite.getPosition().x + sprite.getLocalBounds().width;

	if (sprite.getPosition().x + sprite.getLocalBounds().width < 0) 
	{
		sprite.setPosition(Global::S_WIDTH + sprite.getGlobalBounds().width / 2, sprite.getPosition().y);
	}
}


void MainMenu::HandleEvents(sf::Event& event)
{
	sf::Vector2f mousePosition = Global::GetMousePos(*GameManager::GetWindow());

	if (!continueGame && !newGame)
	{
		for (Button& button : buttons)
		{
			button.handleEvent(event);
		}
	}

	if (continueGame || newGame)
	{
		for (Button& button : playGameButtons)
		{
			button.handleEvent(event);
		}
	}

	for (int i = 0; i < individualLetterTexts.size(); ++i)
	{
		if (individualLetterTexts[i].getGlobalBounds().contains(mousePosition))
		{
			for (int j = 0; j <= i; ++j)
			{
				individualLetterTexts[j].setRotation(-1 * i);
				individualLetterTexts[j].setFillColor(sf::Color::Red);
			}

			sf::Color backgroundColor = sf::Color(255, 255 - i * 6, 255 - i * 6);
			menuBackground.setColor(backgroundColor);

			menuMountainsFar[0].setColor(backgroundColor);
			menuMountainsFar[1].setColor(backgroundColor);
			menuMountainsClose[0].setColor(backgroundColor);
			menuMountainsClose[1].setColor(backgroundColor);
			menuTreesFar[0].setColor(backgroundColor);
			menuTreesFar[1].setColor(backgroundColor);
			menuTreesClose[0].setColor(backgroundColor);
			menuTreesClose[1].setColor(backgroundColor);
		}
		else
		{
			individualLetterTexts[i].setRotation(0.0f);
			individualLetterTexts[i].setPosition(individualLetterTexts[i].getPosition().x, originalYPositions[i]);
			individualLetterTexts[i].setFillColor(sf::Color::Black);
		}
	}
}

void MainMenu::SetupButtons()
{

	Button newGameButton(
		sf::Vector2f(Global::S_WIDTH / 2, Global::S_HEIGHT / 2),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("button1"));

	newGameButton.setLabel("New Game", 30, sf::Color(0, 0, 0, 150));
	newGameButton.setCallback([=]()
		{
			newGame = true;
		});


	newGameButton.centreLabel({ newGameButton.getButtonPos().x, newGameButton.getButtonPos().y - 5 });
	buttons.push_back(newGameButton);

	Button continueGameButton(
		sf::Vector2f(Global::S_WIDTH * 0.5, Global::S_HEIGHT * 0.6),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("button1"));

	continueGameButton.setLabel("Continue Game", 30, sf::Color(0, 0, 0, 150));
	continueGameButton.setCallback([=]()
		{
			continueGame = true;
		});

	continueGameButton.centreLabel({ continueGameButton.getButtonPos().x, continueGameButton.getButtonPos().y - 5 });
	buttons.push_back(continueGameButton);

	Button level1Button(
		sf::Vector2f(Global::S_WIDTH * 0.5, Global::S_HEIGHT * 0.5),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("button1"));

	level1Button.setLabel("Play level 1", 30, sf::Color(0, 0, 0, 150));
	level1Button.setCallback([=]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();

			if (newGame)
			{
				loadGameDataPath = (currentPath / "../../Saves/" / Global::defaultGameData1).string();
			}
			else if (continueGame)
			{
				loadGameDataPath = (currentPath / "../../Saves/" / Global::customGameData1).string();
			}

			GameManager::currentLevel = 1;
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::tileData1).string();
			loadSave = true;
			Game::currentState = GAME;
			GameManager::spaceShipTimer.restart();
		});

	level1Button.centreLabel({ level1Button.getButtonPos().x, level1Button.getButtonPos().y - 5 });
	playGameButtons.push_back(level1Button);

	Button level2Button(
		sf::Vector2f(Global::S_WIDTH * 0.5, Global::S_HEIGHT * 0.6),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("button1"));

	level2Button.setLabel("Play level 2", 30, sf::Color(0, 0, 0, 150));
	level2Button.setCallback([=]()
		{

			std::filesystem::path currentPath = std::filesystem::current_path();

			if (newGame)
			{
				loadGameDataPath = (currentPath / "../../Saves/" / Global::defaultGameData2).string();
			}
			else if (continueGame)
			{
				loadGameDataPath = (currentPath / "../../Saves/" / Global::customGameData2).string();
			}
			
			GameManager::currentLevel = 2;
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::tileData2).string();
			loadSave = true;
			Game::currentState = GAME;
			GameManager::spaceShipTimer.restart();
		});

	level2Button.centreLabel({ level2Button.getButtonPos().x, level2Button.getButtonPos().y - 5 });
	playGameButtons.push_back(level2Button);

	Button level3Button(
		sf::Vector2f(Global::S_WIDTH * 0.5, Global::S_HEIGHT * 0.7),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("button1"));

	level3Button.setLabel("Play level 3", 30, sf::Color(0, 0, 0, 150));
	level3Button.setCallback([=]()
		{

			std::filesystem::path currentPath = std::filesystem::current_path();

			if (newGame)
			{
				loadGameDataPath = (currentPath / "../../Saves/" / Global::defaultGameData3).string();
			}
			else if (continueGame)
			{
				loadGameDataPath = (currentPath / "../../Saves/" / Global::customGameData3).string();
			}

			GameManager::currentLevel = 3;
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::tileData3).string();
			loadSave = true;
			Game::currentState = GAME;
			GameManager::spaceShipTimer.restart();
		});

	level3Button.centreLabel({ level3Button.getButtonPos().x, level3Button.getButtonPos().y - 5 });
	playGameButtons.push_back(level3Button);

	/*Button playButton(
		sf::Vector2f(Global::S_WIDTH / 2, Global::S_HEIGHT / 2),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("button1"));

	playButton.setLabel("Start new game", 30, sf::Color(0, 0, 0, 150));
	playButton.setCallback([]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			loadGameDataPath = (currentPath / "../../Saves/" / Global::defaultGameData).string();
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::defaultTiles).string();
			loadSave = true;
			Game::currentState = GAME;
			GameManager::spaceShipTimer.restart();
		});


	playButton.centreLabel({ playButton.getButtonPos().x, playButton.getButtonPos().y - 5 });
	buttons.push_back(playButton);*/

	/*Button load1Button(
		sf::Vector2f(Global::S_WIDTH * 0.5, Global::S_HEIGHT * 0.6),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("button1"));

	load1Button.setLabel("Play level 1", 30, sf::Color(0, 0, 0, 150));
	load1Button.setCallback([]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			loadGameDataPath = (currentPath / "../../Saves/" / Global::gameData1).string();
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::tileData1).string();
			loadSave = true;
			Game::currentState = GAME;
			GameManager::spaceShipTimer.restart();
		});

	load1Button.centreLabel({ load1Button.getButtonPos().x, load1Button.getButtonPos().y - 5 });
	buttons.push_back(load1Button);

	Button load2Button(
		sf::Vector2f(Global::S_WIDTH * 0.5, Global::S_HEIGHT * 0.7),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("button1"));

	load2Button.setLabel("Play level 2", 30, sf::Color(0, 0, 0, 150));
	load2Button.setCallback([]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			loadGameDataPath = (currentPath / "../../Saves/" / Global::gameData2).string();
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::tileData2).string();
			loadSave = true;
			Game::currentState = GAME;
			GameManager::spaceShipTimer.restart();
		});

	load2Button.centreLabel({ load2Button.getButtonPos().x, load2Button.getButtonPos().y - 5 });
	buttons.push_back(load2Button);

	Button load3Button(
		sf::Vector2f(Global::S_WIDTH * 0.5, Global::S_HEIGHT * 0.8),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("button1"));

	load3Button.setLabel("Play level 3", 30, sf::Color(0, 0, 0, 150));
	load3Button.setCallback([]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			loadGameDataPath = (currentPath / "../../Saves/" / Global::gameData3).string();
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::tileData3).string();
			loadSave = true;
			Game::currentState = GAME;
			GameManager::spaceShipTimer.restart();
		});

	load3Button.centreLabel({ load3Button.getButtonPos().x, load3Button.getButtonPos().y - 5 });
	buttons.push_back(load3Button);*/
}


