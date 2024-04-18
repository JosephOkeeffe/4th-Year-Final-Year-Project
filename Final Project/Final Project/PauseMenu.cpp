#include "PauseMenu.h"
#include "Globals.h"
#include "Game.h"

void PauseMenu::Init()
{

	sf::Vector2f buttonSize {200, 40};

	pauseBackground.setSize(sf::Vector2f(Global::S_WIDTH / 2, Global::S_HEIGHT * 0.6));
	pauseBackground.setPosition(Global::S_WIDTH / 2, Global::S_HEIGHT / 2);
	pauseBackground.setOrigin(pauseBackground.getSize().x / 2, pauseBackground.getSize().y / 2);
	//pauseBackground.setFillColor(sf::Color::Red);
	pauseBackground.setTexture(&Textures::GetInstance().GetTexture("background2"));

	saveBackground.setSize(sf::Vector2f(Global::S_WIDTH / 5, Global::S_HEIGHT / 5));
	saveBackground.setPosition(pauseBackground.getPosition().x, pauseBackground.getPosition().y * 1.2 + (saveBackground.getSize().y / 2) + 30);
	saveBackground.setOrigin(saveBackground.getSize().x / 2, saveBackground.getSize().y / 2);
	saveBackground.setFillColor(sf::Color::Blue);

	loadBackground.setSize(sf::Vector2f(Global::S_WIDTH / 5, Global::S_HEIGHT / 5));
	loadBackground.setPosition(pauseBackground.getPosition().x, pauseBackground.getPosition().y * 1.4 + (saveBackground.getSize().y / 2) + 30);
	loadBackground.setOrigin(saveBackground.getSize().x / 2, saveBackground.getSize().y / 2);
	loadBackground.setFillColor(sf::Color::Blue);

	Button resumeButton(
		sf::Vector2f(pauseBackground.getPosition().x, pauseBackground.getPosition().y * 0.60),
		sf::Vector2f(buttonSize),
		sf::Color::White,
		sf::Color(143,137,137),
		Textures::GetInstance().GetTexture("button1"));

	resumeButton.setLabel("Resume", 30, sf::Color(0, 0, 0, 150));
	resumeButton.setCallback([=]()
		{
			Game::currentState = GAME;
			saveMenu = false;
			loadMenu = false;
			particleCount = 0;
			particleSystem.clearParticles();
		});
	resumeButton.centreLabel({ resumeButton.getButtonPos().x, resumeButton.getButtonPos().y - 5 });
	buttons.push_back(resumeButton);
	//
	//
	//
	Button controlsButton(
		sf::Vector2f(pauseBackground.getPosition().x, pauseBackground.getPosition().y * 0.80),
		sf::Vector2f(buttonSize),
		sf::Color::White,
		sf::Color(143, 137, 137),
		Textures::GetInstance().GetTexture("button1"));

	controlsButton.setLabel("Controls", 30, sf::Color(0, 0, 0, 150));
	controlsButton.setCallback([=]()
		{
			Game::isControlsOpen = true;
			particleCount = 0;
			particleSystem.clearParticles();
		});
	controlsButton.centreLabel({ controlsButton.getButtonPos().x, controlsButton.getButtonPos().y - 5 });
	buttons.push_back(controlsButton);
	//
	//
	//
	Button instructionsButton(
		sf::Vector2f(pauseBackground.getPosition().x, pauseBackground.getPosition().y * 1),
		sf::Vector2f(buttonSize),
		sf::Color::White,
		sf::Color(143, 137, 137),
		Textures::GetInstance().GetTexture("button1"));

	instructionsButton.setLabel("Instructions", 30, sf::Color(0, 0, 0, 150));
	instructionsButton.setCallback([=]()
		{
			Game::isInstructionsOpen = true;
			particleCount = 0;
			particleSystem.clearParticles();
		});
	instructionsButton.centreLabel({ instructionsButton.getButtonPos().x, instructionsButton.getButtonPos().y - 5 });
	buttons.push_back(instructionsButton);
	//
	//
	//
	Button saveMenuButton(
		sf::Vector2f(pauseBackground.getPosition().x, pauseBackground.getPosition().y * 1.20),
		sf::Vector2f(buttonSize),
		sf::Color::White,
		sf::Color(143, 137, 137),
		Textures::GetInstance().GetTexture("button1"));

	saveMenuButton.setLabel("Save", 30, sf::Color(0, 0, 0, 150));
	saveMenuButton.setCallback([=]()
		{
			if(!loadMenu)
			{
				saveMenu = !saveMenu;
				loadMenu = false;
				particleCount = 0;
			}
		});
	saveMenuButton.centreLabel({ saveMenuButton.getButtonPos().x, saveMenuButton.getButtonPos().y - 5 });
	buttons.push_back(saveMenuButton);
	//
	//
	//

	Button mainMenuButton(
		sf::Vector2f(pauseBackground.getPosition().x, pauseBackground.getPosition().y * 1.40),
		sf::Vector2f(buttonSize),
		sf::Color::White,
		sf::Color(143, 137, 137),
		Textures::GetInstance().GetTexture("button1"));

	mainMenuButton.setLabel("Main Menu",  30, sf::Color(0, 0, 0, 150));
	mainMenuButton.setCallback([=]()
		{
			Game::currentState = GameState::MENU;
		});
	mainMenuButton.centreLabel({ mainMenuButton.getButtonPos().x, mainMenuButton.getButtonPos().y - 5 });
	buttons.push_back(mainMenuButton);

	// 
	//
	//


	// Saves
	Button save1Button(
		sf::Vector2f(saveBackground.getPosition().x, saveBackground.getPosition().y * 0.9),
		sf::Vector2f(200, 25),
		sf::Color::White,
		sf::Color(143, 137, 137),
		Textures::GetInstance().GetTexture("button1"));

	save1Button.setLabel("Save 1",  25, sf::Color(0, 0, 0, 150));
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

	Button save2Button(
		sf::Vector2f(saveBackground.getPosition().x, saveBackground.getPosition().y),
		sf::Vector2f(200, 25),
		sf::Color::White,
		sf::Color(143, 137, 137),
		Textures::GetInstance().GetTexture("button1"));

	save2Button.setLabel("Save 2", 25, sf::Color(0, 0, 0, 150));
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

	Button save3Button(
		sf::Vector2f(saveBackground.getPosition().x, saveBackground.getPosition().y * 1.1),
		sf::Vector2f(200, 25),
		sf::Color::White,
		sf::Color(143, 137, 137),
		Textures::GetInstance().GetTexture("button1"));

	save3Button.setLabel("Save 3", 25, sf::Color(0, 0, 0, 150));
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

}

void PauseMenu::Render(sf::RenderWindow& window)
{
	window.draw(pauseBackground);
	particleSystem.draw(window);

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


	sf::Color randomColor(rand() % 256, rand() % 256, rand() % 256, 255);
	float randomSize = static_cast<float>(rand() % 5 + 2);

	if (delay.getElapsedTime().asMilliseconds() > 300 && particleCount < MAX_PARTICLES)
	{
		delay.restart();
		particleCount++;
		//particleSystem.addParticle(pauseBackground.getPosition(), Global::GetRandomVector() * 0.2f, randomColor, randomSize, 3);
		particleSystem.AddSpriteParticle(pauseBackground.getPosition(), Global::GetRandomVector() * 0.2f, randomColor, Textures::GetInstance().GetTexture("coin"), 600, 0.1f, 3);
	}

    particleSystem.Update();
}

void PauseMenu::HandleEvents(sf::Event& event)
{
	for (Button& button : buttons)
	{
		button.handleEvent(event);
	}

	if (saveMenu)
	{
		for (Button& button : saveButtons)
		{
			button.handleEvent(event);
		}
	}
	if (loadMenu)
	{
		for (Button& button : loadButtons)
		{
			button.handleEvent(event);
		}
	}
}

void PauseMenu::SetupSave()
{
}

