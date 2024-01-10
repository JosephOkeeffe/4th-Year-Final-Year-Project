#include <iostream>
#include "Game.h"
#include <filesystem>

std::string savePath = "";
std::string loadGameDataPath = "";
std::string loadTilesDataPath = "";
bool saveGame = false;
bool loadSave = false;

Game::Game() :
    m_window{ sf::VideoMode{ Global::S_WIDTH, Global::S_HEIGHT, 32U }, "The Big One" },
    m_exitGame{ false },
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
            pauseMenu.HandleEvents(newEvent, m_window);
            break;
        default:
            break;
        }
    }
}
void Game::ProcessKeys(sf::Event t_event)
{
    if (sf::Keyboard::Escape == t_event.key.code){m_exitGame = true;}
    if (sf::Keyboard::Q == t_event.key.code) { SaveJSON(); }
    if (sf::Keyboard::W == t_event.key.code) { LoadJSON(); }
    if (sf::Keyboard::E == t_event.key.code) { LoadTilesJSON(); }
    if (sf::Keyboard::Enter == t_event.key.code) { currentState = PAUSED; }
}
void Game::ProcessMouseDown(sf::Event t_event)
{
    if (sf::Mouse::Left == t_event.key.code)
    {
        sf::Vector2i currentCell = Global::GetCurrentCell(m_window, gameView);
        std::cout << currentCell.x << ", " << currentCell.y << "\n";
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
    srand(time(nullptr));
    m_font.loadFromFile("./assets/fonts/Flinton.otf");
    mainMenu.Init(m_window, m_font);
    pauseMenu.Init(m_window, m_font);
    tiles = new Tile * [Global::ROWS_COLUMNS];

    for (int i = 0; i < Global::ROWS_COLUMNS; i++) 
    {
        tiles[i] = new Tile[Global::ROWS_COLUMNS];
    }
    elapsedTime = incomeTimer.getElapsedTime();
    InitTiles();
    hud.Init();
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
        for (int row = 0; row < Global::ROWS_COLUMNS; row++)
        {
            for (int col = 0; col < Global::ROWS_COLUMNS; col++)
            {
                tiles[row][col].Render(m_window);
            }
        }
        warrior.DrawWarrior(m_window);
        archer.DrawArcher(m_window);
        pauseMenu.Render(m_window);

        break;
    default:
        break;
    }
    m_window.display();
}

void Game::Update(sf::Time t_deltaTime)
{
    if (m_exitGame) { m_window.close(); }

    switch (currentState)
    {
    case MENU:
        break;
    case GAME:

        if (loadSave)
        {
            LoadJSON();
        }
        if (saveGame)
        {
            SaveJSON();
        }

        view.MoveScreen();
        ManageTimer();

        if (ResourceManagement::isPlacingShop)
        {
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
                    if (row == currentCellPos.x && col == currentCellPos.y) 
                    {
                        continue;
                    }

                    if (tiles[row][col].GetTileType() != TileType::SHOP) 
                    {
                        tiles[row][col].ResetTexture();
                    }
                }
            }
        }

        ChangeThingsDependingOnTileType();

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

void Game::SaveJSON()
{
    std::filesystem::path currentPath = std::filesystem::current_path();

    nlohmann::json jsonData;

    jsonData["X"] = warrior.GetSprite().getPosition().x;
    jsonData["Y"] = warrior.GetSprite().getPosition().y;

    jsonData["Coins"] = ResourceManagement::GetCoins();
    jsonData["Shops"] = ResourceManagement::GetShops();

    for (int row = 0; row < Global::ROWS_COLUMNS; row++)
    {
        for (int col = 0; col < Global::ROWS_COLUMNS; col++)
        {
            jsonData["TileType"][row][col] = tiles[row][col].GetTileType();
        }
    }

    std::ofstream file(savePath);

    if (file.is_open())
    {
        file << std::setw(4) << jsonData << std::endl;

        file.close();
        std::cout << "Saved Data:\n" << jsonData.dump(4) << std::endl;
    }
    else
    {
        std::cerr << "Error saving the game data file!" << std::endl;
    }
    saveGame = false;
}

void Game::LoadJSON()
{
    //loadTilesDataPath = (currentPath / "../../Saves/GameData.json").string();
    std::ifstream file(loadGameDataPath);

    if (file.is_open())
    {
        nlohmann::json jsonData;
        file >> jsonData;
        file.close();

        sf::Vector2f warriorLoadedPos;
        warriorLoadedPos.x = jsonData["X"];
        warriorLoadedPos.y = jsonData["Y"];
        warrior.SetPosition(warriorLoadedPos);

        float coins = jsonData["Coins"];
        float shops = jsonData["Shops"];

        for (int row = 0; row < Global::ROWS_COLUMNS; row++)
        {
            for (int col = 0; col < Global::ROWS_COLUMNS; col++)
            {
                int tileType = jsonData["TileType"][row][col];
                tiles[row][col].SetTileType(static_cast<TileType>(tileType));
            }
        }
        ResourceManagement::ResetAndLoad(coins, shops);

        std::cout << "Loaded Game Data:\n";
        std::cout << "X: " << warriorLoadedPos.x << "\n";
        std::cout << "Y: " << warriorLoadedPos.y << "\n";
        std::cout << "Coins: " << coins << "\n";
        std::cout << "Shops: " << shops << "\n";
    }
    else
    {
        std::cerr << "Error loading game data file!" << std::endl;
    }

    LoadTilesJSON();
    loadSave = false;
}

void Game::LoadTilesJSON()
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::ifstream file(loadTilesDataPath);

    if (file.is_open())
    {
        nlohmann::json jsonData;
        file >> jsonData;
        file.close();

        for (int row = 0; row < Global::ROWS_COLUMNS; row++)
        {
            for (int col = 0; col < Global::ROWS_COLUMNS; col++)
            {
                int grassType = jsonData["GrassType"][row][col];

                FixLoadedGrass(grassType, row, col);
            }
        }
        std::cout << "Tiles Loaded\n";
    }
    else
    {
        std::cerr << "Error loading the tiles data file!" << std::endl;
    }
}

void Game::FixLoadedGrass(int type, int row, int col)
{
    if (tiles[row][col].GetTileType() == SHOP) { return;}
   
    if (type <= MOUNTAINS)
    {
        tiles[row][col].SetGrassType(static_cast<GrassType>(type));
        tiles[row][col].SetTileType(NONE);

    }
    else if (type >= BRIDGE1 && type <= PATH10)
    {
        tiles[row][col].SetGrassType(static_cast<GrassType>(type));
        tiles[row][col].SetTileType(PATH);
    }
    else if (type >= WATER1 && type <= WATER13)
    {
        tiles[row][col].SetGrassType(static_cast<GrassType>(type));
        tiles[row][col].SetTileType(OBSTACLE);
    }
}

void Game::ChangeThingsDependingOnTileType()
{
    sf::Vector2i tempPos;

    tempPos.x = static_cast<int>(warrior.tileDetectionCircle.getPosition().x / Global::CELL_SIZE);
    tempPos.y = static_cast<int>(warrior.tileDetectionCircle.getPosition().y / Global::CELL_SIZE);

    if (tiles[tempPos.x][tempPos.y].GetTileType() == NONE)
    {
        warrior.currentMoveSpeed = warrior.defaultMoveSpeed;
    }
    else if (tiles[tempPos.x][tempPos.y].GetTileType() == PATH)
    {
        warrior.currentMoveSpeed = warrior.defaultMoveSpeed * 2;
    }
    else if (tiles[tempPos.x][tempPos.y].GetTileType() == OBSTACLE)
    {
        warrior.currentMoveSpeed = warrior.defaultMoveSpeed / 2;
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
        incomeTimer.restart();
    }
}


