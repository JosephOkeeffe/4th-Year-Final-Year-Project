#include "PauseMenu.h"
#include "Globals.h"
#include "Game.h"

void PauseMenu::Init(sf::RenderWindow& window, sf::Font& font)
{
	pauseBackground.setPosition(Global::S_WIDTH / 2, Global::S_HEIGHT / 2);
	pauseBackground.setSize(sf::Vector2f(Global::S_WIDTH / 2, Global::S_HEIGHT / 2));
	pauseBackground.setOrigin(pauseBackground.getSize().x / 2, pauseBackground.getSize().y / 2);
	pauseBackground.setFillColor(sf::Color::Red);

	saveBackground.setSize(sf::Vector2f(Global::S_WIDTH / 5, Global::S_HEIGHT / 5));
	saveBackground.setPosition(pauseBackground.getPosition().x, pauseBackground.getPosition().y * 0.85 + (saveBackground.getSize().y / 2) + 30);
	saveBackground.setOrigin(saveBackground.getSize().x / 2, saveBackground.getSize().y / 2);
	saveBackground.setFillColor(sf::Color::Blue);

	loadBackground.setSize(sf::Vector2f(Global::S_WIDTH / 5, Global::S_HEIGHT / 5));
	loadBackground.setPosition(pauseBackground.getPosition().x, pauseBackground.getPosition().y * 1.05 + (saveBackground.getSize().y / 2) + 30);
	loadBackground.setOrigin(saveBackground.getSize().x / 2, saveBackground.getSize().y / 2);
	loadBackground.setFillColor(sf::Color::Blue);

	Button resumeButton(window,
		sf::Vector2f(pauseBackground.getPosition().x, pauseBackground.getPosition().y * 0.65),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		font,
		Textures::GetInstance().GetTexture("edit"));

	resumeButton.setLabel("Resume", font, 30, sf::Color(0, 0, 0, 150));
	resumeButton.setCallback([=]()
		{
			Game::currentState = GAME;
			saveMenu = false;
			loadMenu = false;
		});
	resumeButton.centreLabel({ resumeButton.getButtonPos().x, resumeButton.getButtonPos().y - 5 });
	buttons.push_back(resumeButton);
	//
	//
	//
	Button saveMenuButton(window,
		sf::Vector2f(pauseBackground.getPosition().x, pauseBackground.getPosition().y * 0.85),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		font,
		Textures::GetInstance().GetTexture("edit"));

	saveMenuButton.setLabel("Save", font, 30, sf::Color(0, 0, 0, 150));
	saveMenuButton.setCallback([=]()
		{
			saveMenu = !saveMenu;
			loadMenu = false;
		});
	saveMenuButton.centreLabel({ saveMenuButton.getButtonPos().x, saveMenuButton.getButtonPos().y - 5 });
	buttons.push_back(saveMenuButton);
	//
	//
	//

	Button loadMenuButton(window,
		sf::Vector2f(pauseBackground.getPosition().x, pauseBackground.getPosition().y * 1.05),
		sf::Vector2f(200, 50),
		sf::Color::White,
		sf::Color::Magenta,
		font,
		Textures::GetInstance().GetTexture("edit"));

	loadMenuButton.setLabel("Load", font, 30, sf::Color(0, 0, 0, 150));
	loadMenuButton.setCallback([=]()
		{
			loadMenu = !loadMenu;
			saveMenu = false;
		});
	loadMenuButton.centreLabel({ loadMenuButton.getButtonPos().x, loadMenuButton.getButtonPos().y - 5 });
	buttons.push_back(loadMenuButton);

	// 
	//
	//


	// Save
	Button save1Button(window,
		sf::Vector2f(saveBackground.getPosition().x, saveBackground.getPosition().y * 0.9),
		sf::Vector2f(200, 25),
		sf::Color::White,
		sf::Color::Magenta,
		font,
		Textures::GetInstance().GetTexture("edit"));

	save1Button.setLabel("Save 1", font, 25, sf::Color(0, 0, 0, 150));
	save1Button.setCallback([=]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			savePath = (currentPath / "../../Saves/" / Global::gameData1).string();
			saveGame = true;
			saveMenu = false;
			Game::currentState = GAME;
		});
	save1Button.centreLabel({ save1Button.getButtonPos().x, save1Button.getButtonPos().y - 5 });
	saveButtons.push_back(save1Button);

	Button save2Button(window,
		sf::Vector2f(saveBackground.getPosition().x, saveBackground.getPosition().y),
		sf::Vector2f(200, 25),
		sf::Color::White,
		sf::Color::Magenta,
		font,
		Textures::GetInstance().GetTexture("edit"));

	save2Button.setLabel("Save 2", font, 25, sf::Color(0, 0, 0, 150));
	save2Button.setCallback([=]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			savePath = (currentPath / "../../Saves/" / Global::gameData2).string();
			saveGame = true;
			saveMenu = false;
			Game::currentState = GAME;
		});
	save2Button.centreLabel({ save2Button.getButtonPos().x, save2Button.getButtonPos().y - 5 });
	saveButtons.push_back(save2Button);

	Button save3Button(window,
		sf::Vector2f(saveBackground.getPosition().x, saveBackground.getPosition().y * 1.1),
		sf::Vector2f(200, 25),
		sf::Color::White,
		sf::Color::Magenta,
		font,
		Textures::GetInstance().GetTexture("edit"));

	save3Button.setLabel("Save 3", font, 25, sf::Color(0, 0, 0, 150));
	save3Button.setCallback([=]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			savePath = (currentPath / "../../Saves/" / Global::gameData3).string();
			saveGame = true;
			saveMenu = false;
			Game::currentState = GAME;
		});
	save3Button.centreLabel({ save3Button.getButtonPos().x, save3Button.getButtonPos().y - 5 });
	saveButtons.push_back(save3Button);

	// Load
	Button load1Button(window,
		sf::Vector2f(loadBackground.getPosition().x, loadBackground.getPosition().y * 0.9),
		sf::Vector2f(200, 25),
		sf::Color::White,
		sf::Color::Magenta,
		font,
		Textures::GetInstance().GetTexture("edit"));

	load1Button.setLabel("Load 1", font, 25, sf::Color(0, 0, 0, 150));
	load1Button.setCallback([=]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			loadGameDataPath = (currentPath / "../../Saves/" / Global::gameData1).string();
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::tileData1).string();
			loadSave = true;
			loadMenu = false;
			Game::currentState = GAME;
		});
	load1Button.centreLabel({ load1Button.getButtonPos().x, load1Button.getButtonPos().y - 5 });
	loadButtons.push_back(load1Button);

	Button load2Button(window,
		sf::Vector2f(loadBackground.getPosition().x, loadBackground.getPosition().y),
		sf::Vector2f(200, 25),
		sf::Color::White,
		sf::Color::Magenta,
		font,
		Textures::GetInstance().GetTexture("edit"));

	load2Button.setLabel("Load 2", font, 25, sf::Color(0, 0, 0, 150));
	load2Button.setCallback([=]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			loadGameDataPath = (currentPath / "../../Saves/" / Global::gameData2).string();
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::tileData2).string();
			loadSave = true;
			loadMenu = false;
			Game::currentState = GAME;
		});
	load2Button.centreLabel({ load2Button.getButtonPos().x, load2Button.getButtonPos().y - 5 });
	loadButtons.push_back(load2Button);

	Button load3Button(window,
		sf::Vector2f(loadBackground.getPosition().x, loadBackground.getPosition().y * 1.1),
		sf::Vector2f(200, 25),
		sf::Color::White,
		sf::Color::Magenta,
		font,
		Textures::GetInstance().GetTexture("edit"));

	load3Button.setLabel("Load 3", font, 25, sf::Color(0, 0, 0, 150));
	load3Button.setCallback([=]()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			loadGameDataPath = (currentPath / "../../Saves/" / Global::gameData3).string();
			loadTilesDataPath = (currentPath / "../../Saves/" / Global::tileData3).string();
			loadSave = true;
			loadMenu = false;
			Game::currentState = GAME;
		});
	load3Button.centreLabel({ load3Button.getButtonPos().x, load3Button.getButtonPos().y - 5 });
	loadButtons.push_back(load3Button);

}

void PauseMenu::Render(sf::RenderWindow& window)
{
	window.draw(pauseBackground);

	for (Button& button : buttons)
	{
		button.update();
		button.render(window);
	}

	if (saveMenu)
	{
		window.draw(saveBackground);

		for (Button& button : saveButtons)
		{
			button.update();
			button.render(window);
		}
	}
	if (loadMenu)
	{
		window.draw(loadBackground);

		for (Button& button : loadButtons)
		{
			button.update();
			button.render(window);
		}
	}
}

void PauseMenu::HandleEvents(sf::Event& event, sf::RenderWindow& window)
{
	for (Button& button : buttons)
	{
		button.handleEvent(event, window);
	}

	if (saveMenu)
	{
		for (Button& button : saveButtons)
		{
			button.handleEvent(event, window);
		}
	}
	if (loadMenu)
	{
		for (Button& button : loadButtons)
		{
			button.handleEvent(event, window);
		}
	}
}

void PauseMenu::SetupSave()
{
}

