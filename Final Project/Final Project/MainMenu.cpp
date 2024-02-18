#include "MainMenu.h"
#include "Game.h"

void MainMenu::Init()
{
	menuBackground.setPosition(200, 200);
	menuBackground.setOrigin(200, 200);
	menuBackground.setSize(sf::Vector2f(Global::S_WIDTH, Global::S_HEIGHT));
	menuBackground.setFillColor(sf::Color::Red);

	Button playButton(
		sf::Vector2f(Global::S_WIDTH / 2, Global::S_HEIGHT / 2),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("edit"));

	playButton.setLabel("Start new game", 30, sf::Color(0, 0, 0, 150));
	playButton.setCallback([]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			//loadGameDataPath = (currentPath / "../../Saves/" / Global::gameData1).string();
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::defaultTiles).string();
			loadSave = true;
			Game::currentState = GAME;
		});
	

	playButton.centreLabel({ playButton.getButtonPos().x, playButton.getButtonPos().y - 5 });
	buttons.push_back(playButton);

	Button load1Button(
		sf::Vector2f(Global::S_WIDTH * 0.5, Global::S_HEIGHT * 0.6),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("edit"));

	load1Button.setLabel("Load save 1", 30, sf::Color(0, 0, 0, 150));
	load1Button.setCallback([]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			loadGameDataPath = (currentPath / "../../Saves/" / Global::gameData1).string();
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::tileData1).string();
			loadSave = true;
			Game::currentState = GAME;
		});

	load1Button.centreLabel({ load1Button.getButtonPos().x, load1Button.getButtonPos().y - 5 });
	buttons.push_back(load1Button);

	Button load2Button(
		sf::Vector2f(Global::S_WIDTH * 0.5, Global::S_HEIGHT * 0.7),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("edit"));

	load2Button.setLabel("Load save 2", 30, sf::Color(0, 0, 0, 150));
	load2Button.setCallback([]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			loadGameDataPath = (currentPath / "../../Saves/" / Global::gameData2).string();
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::tileData2).string();
			loadSave = true;
			Game::currentState = GAME;
		});

	load2Button.centreLabel({ load2Button.getButtonPos().x, load2Button.getButtonPos().y - 5 });
	buttons.push_back(load2Button);

	Button load3Button(
		sf::Vector2f(Global::S_WIDTH * 0.5, Global::S_HEIGHT * 0.8),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		Textures::GetInstance().GetTexture("edit"));

	load3Button.setLabel("Load save 3",30, sf::Color(0, 0, 0, 150));
	load3Button.setCallback([]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			loadGameDataPath = (currentPath / "../../Saves/" / Global::gameData3).string();
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::tileData3).string();
			loadSave = true;
			Game::currentState = GAME;
		});

	load3Button.centreLabel({ load3Button.getButtonPos().x, load3Button.getButtonPos().y - 5 });
	buttons.push_back(load3Button);
	
	
}

void MainMenu::Render(sf::RenderWindow& window)
{
	window.draw(menuBackground);

	for (Button& button : buttons)
	{
		button.update();
		button.render(window);
	}
}

void MainMenu::HandleEvents(sf::Event& event)
{
	for (Button& button : buttons)
	{
		button.handleEvent(event);
	}
}


