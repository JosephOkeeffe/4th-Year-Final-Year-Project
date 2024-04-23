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
			//Game::currentState = GAME;
			Game::ChangeGameState(GameState::GAME);
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

			std::filesystem::path currentPath = std::filesystem::current_path();
			if (GameManager::currentLevel == 1)
			{
				savePath = (currentPath / "../../Saves/" / Global::customGameData1).string();
			}
			else if (GameManager::currentLevel == 2)
			{
				savePath = (currentPath / "../../Saves/" / Global::customGameData2).string();
			}
			else if (GameManager::currentLevel == 3)
			{
				savePath = (currentPath / "../../Saves/" / Global::customGameData3).string();
			}
			
			saveGame = true;
			//Game::currentState = GAME;
			Game::ChangeGameState(GameState::GAME);


			particleCount = 0;
			
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
			//Game::currentState = GameState::MENU;
			Game::ChangeGameState(GameState::MENU);
		});
	mainMenuButton.centreLabel({ mainMenuButton.getButtonPos().x, mainMenuButton.getButtonPos().y - 5 });
	buttons.push_back(mainMenuButton);

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
}

void PauseMenu::SetupSave()
{
}

