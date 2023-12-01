#include <iostream>
#include "Game.h"

Game::Game() :
    m_window{ sf::VideoMode{ Global::S_WIDTH, Global::S_HEIGHT, 32U }, "The Big One" },
    m_exitGame{ false },
    /*textures(),*/
    view(m_window, gameView, hudView),
    hud(m_window, m_font),
    warrior(m_window, gameView),
    archer(m_window)
    
{
    Init();
}
Game::~Game()
{}
void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const float fps{ 60.0f };
    sf::Time timePerFrame = sf::seconds(1.0f / fps);
    while (m_window.isOpen())
    {
        ProcessEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            ProcessEvents(); 
            Update(timePerFrame);
        }
        Render();
    }
}

void Game::ProcessEvents()
{
    sf::Event newEvent;
    while (m_window.pollEvent(newEvent))
    {
        if (sf::Event::Closed == newEvent.type)
        {
            m_exitGame = true;
            
        }
        if (sf::Event::KeyPressed == newEvent.type)
        {
            ProcessKeys(newEvent);
        }
        if (sf::Event::MouseButtonPressed == newEvent.type || sf::Event::MouseWheelScrolled == newEvent.type)
        {
            ProcessMouseDown(newEvent);
            
        }
        if (sf::Event::MouseButtonReleased == newEvent.type)
        {
            ProcessMouseUp(newEvent);
        }

        switch (currentState)
        {
        case MENU:
            mainMenu.HandleEvents(newEvent, m_window);
            break;
        case GAME:
            hud.HandleEvents(newEvent);
            view.handleInput(newEvent);
            break;
        case PAUSED:
            break;
        default:
            break;
        }
       
       
    }
}
void Game::ProcessKeys(sf::Event t_event)
{
    if (sf::Keyboard::Escape == t_event.key.code){m_exitGame = true;}
    if (sf::Keyboard::Q == t_event.key.code) { Save(); }
    if (sf::Keyboard::W == t_event.key.code) { Load(); }
   
}
void Game::ProcessMouseDown(sf::Event t_event)
{
    if (sf::Mouse::Left == t_event.key.code)
    {
        sf::Vector2i currentCell = Global::GetCurrentCell(m_window, gameView);
        tiles[currentCell.x][currentCell.y].SetShop();
    } 
    if (sf::Mouse::Right == t_event.key.code)
    {
    }
}
void Game::ProcessMouseUp(sf::Event t_event)
{
    if (sf::Mouse::Left == t_event.key.code)
    {
        warrior.MouseUp(m_window);
    }
}
void Game::Init()
{
   // m_window.setMouseCursorGrabbed(true);
   // State::currentState = GAME;
    srand(time(nullptr));
    m_font.loadFromFile("./assets/fonts/Flinton.otf");
    mainMenu.Init(m_window, m_font);
    tiles = new Tile * [Global::ROWS_COLUMNS];

    for (int i = 0; i < Global::ROWS_COLUMNS; i++) 
    {
        tiles[i] = new Tile[Global::ROWS_COLUMNS];
    }
    elapsedTime = incomeTimer.getElapsedTime();
    InitTiles();
    hud.Init();
}

void Game::Save()
{
    std::string xPos = std::to_string(warrior.GetSprite().getPosition().x);
    std::string yPos = std::to_string(warrior.GetSprite().getPosition().y);
    std::string coinsString = std::to_string(ResourceManagement::GetCoins());
    std::string shopsString = std::to_string(ResourceManagement::GetShops());

    // Open file to write
    std::ofstream file("saveFile.txt");

    if (file.is_open()) 
    {
        // Saving the values to the file                                                                      
        file << "X: " << xPos << "\n";
        file << "Y: " << yPos << "\n";
        file << "Coins: " << coinsString << "\n";
        file << "Shops: " << shopsString << "\n";

        // Loop through map of tiles and save the tileType
        for (int row = 0; row < Global::ROWS_COLUMNS; row++) 
        {
            for (int col = 0; col < Global::ROWS_COLUMNS; col++) 
            {
                file << "Tile[" << row << "][" << col << "]: " << tiles[row][col].GetType() << "\n";
            }
        }

        // Loop through map of tiles and check what kind of tile they are

        // Close the file
        file.close();
        std::cout << "Saved Data:\n";
        std::cout << "X: " << xPos << "\n";
        std::cout << "Y: " << yPos << "\n";
        std::cout << "Coins: " << coinsString << "\n";
        std::cout << "Shops: " << shopsString << "\n";
    }
    else 
    {
        std::cerr << "Error opening the file!" << std::endl;
    }
}

void Game::Load() 
{
    std::ifstream file("saveFile.txt");

    if (file.is_open()) 
    {
        // Character Positions
        std::string xPos;
        std::getline(file, xPos);
        float x = std::stof(xPos.substr(xPos.find(":") + 1));

        std::string yPos;
        std::getline(file, yPos);
        float y = std::stof(yPos.substr(yPos.find(":") + 1));

        sf::Vector2f warriorLoadedPos = { x, y };
        warrior.SetPosition(warriorLoadedPos);

        // Resources
        std::string coinsString;
        std::getline(file, coinsString);
        float coins = std::stof(coinsString.substr(coinsString.find(":") + 1));

        std::string shopsString;
        std::getline(file, shopsString);
        float shops = std::stof(shopsString.substr(shopsString.find(":") + 1));

        // Tiles
        for (int row = 0; row < Global::ROWS_COLUMNS; row++)
        {
            for (int col = 0; col < Global::ROWS_COLUMNS; col++) 
            {
                std::string tileInfo;
                std::getline(file, tileInfo);
                int tileType = std::stoi(tileInfo.substr(tileInfo.find(":") + 1));
                tiles[row][col].SetType(static_cast<TileType>(tileType));
            }
        }

        ResourceManagement::ResetAndLoad(coins, shops);

        file.close();

        std::cout << "Loaded Data:\n";
        std::cout << "X: " << warriorLoadedPos.x << "\n";
        std::cout << "Y: " << warriorLoadedPos.y << "\n";
        std::cout << "Coins: " << coins << "\n";
        std::cout << "Shops: " << shops << "\n";
        std::cout << "Tiles Loaded\n";
    }
    else
    {
        std::cerr << "Error opening the file!" << std::endl;
    }
}


void Game::InitTiles()
{
    for (int row = 0; row < Global::ROWS_COLUMNS; row++)
    {
        for (int col = 0; col < Global::ROWS_COLUMNS; col++)
        {
            sf::Vector2f temp = { static_cast<float>(row * Global::CELL_SIZE), static_cast<float>(col * Global::CELL_SIZE) };
            tiles[row][col].Init(temp);
        }
    }
}

void Game::ManageTimer()
{
    elapsedTime = incomeTimer.getElapsedTime();

    if (elapsedTime.asSeconds() >= 5.0f)
    {
        ResourceManagement::AddCoins(ResourceManagement::GetShops());
        std::cout << "Current Shops: " << ResourceManagement::GetShops() << "\n";
        incomeTimer.restart();
    }
}


void Game::Render()
{
    m_window.clear(sf::Color::Black);

    switch (currentState)
    {
    case MENU:
        mainMenu.Render(m_window);
        break;
    case GAME:
        // Game
        view.SetGameView();
        for (int row = 0; row < Global::ROWS_COLUMNS; row++)
        {
            for (int col = 0; col < Global::ROWS_COLUMNS; col++)
            {
                tiles[row][col].Render(m_window);
            }
        }

        warrior.DrawWarrior(m_window);
        archer.DrawArcher(m_window);

        // HUD
        view.SetHudView();
        hud.Render(m_window);
        break;
    case PAUSED:
        break;
    default:
        break;
    }

   



    m_window.display();
}

void Game::Update(sf::Time t_deltaTime)
{
    if (m_exitGame){m_window.close();}

    switch (currentState)
    {
    case MENU:
        break;
    case GAME:
        view.MoveScreen();
        ManageTimer();

        if (ResourceManagement::isPlacingShop)
        {
            //sf::Vector2i oldPos = Global::GetCurrentCell(m_window);
            sf::Vector2f currentMousePos = Global::GetWindowMousePos(m_window, gameView);
            sf::Vector2i currentCellPos = Global::GetCurrentCell(m_window, gameView);

            if (currentMousePos.x >= 0 && currentMousePos.x < Global::ROWS_COLUMNS * Global::CELL_SIZE &&
                currentMousePos.y >= 0 && currentMousePos.y < Global::ROWS_COLUMNS * Global::CELL_SIZE)
            {
                tiles[currentCellPos.x][currentCellPos.y].Hover(Textures::GetInstance().GetTexture("shop"));
            }
            for (int row = 0; row < Global::ROWS_COLUMNS; row++)
            {
                for (int col = 0; col < Global::ROWS_COLUMNS; col++)
                {
                    if (tiles[row][col].GetType() == TileType::NONE)
                    {
                        if (row != currentCellPos.x
                            || col != currentCellPos.y)
                        {
                            tiles[row][col].ResetTexture();
                        }
                    }
                }
            }

        }
        warrior.Update(m_window);
        archer.Update(m_window);
        warrior.CalculateAngle(warrior.GetSprite(), archer.GetSprite());
        break;
    case PAUSED:

        break;
    default:
        break;
    }


}


