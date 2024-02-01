#include <iostream>
#include "Game.h"
#include <filesystem>
#include "BuildingUI.h"

std::string savePath = "";
std::string loadGameDataPath = "";
std::string loadTilesDataPath = "";
bool saveGame = false;
bool loadSave = false;

//sf::View* GameObject::gameView = nullptr;
std::vector<Buildings*> Game::buildings;

Game::Game() :
    m_window{ sf::VideoMode{ Global::S_WIDTH, Global::S_HEIGHT, 32U }, "The Big One" },
    m_exitGame{ false },
    view(m_window, gameView, hudView)
{
    GameObject::SetWindow(m_window);
    GameObject::SetView(gameView);
    // I NEED TO PASS THE TILES INTO GAME OBJECT SOMEHOW
    // CREATE MAP OF TILES AND SPRITES
    // TO DO: Only allow mine to be placed on GOld ore
    // Only allow one building to be placed on a tile
    Init();
    GameObject::SetTiles(tiles);
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
    HUD::Init(m_window, m_font);
    BuildingUI::Init();

    CreateBase(basePos);
    CreateArcher({ 300, 400 });
    CreateWarrior({ 350, 400 });
    CreateWarrior({ 400, 400 });
    // stay in same position but move to the leader
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
            ProcessKeyPress(newEvent);
        }
        if (sf::Event::KeyReleased == newEvent.type)
        {
            ProcessKeyRelease(newEvent);
        }
        if (sf::Event::MouseButtonPressed == newEvent.type || sf::Event::MouseWheelScrolled == newEvent.type)
        {
            ProcessMousePress(newEvent);
        }
        if (sf::Event::MouseButtonReleased == newEvent.type)
        {
            ProcessMouseRelease(newEvent);
        }
        if (sf::Event::MouseMoved == newEvent.type)
        {
            if (isDragging)
            {
                endDragPos = Global::GetWindowMousePos(m_window, gameView);
                dragRect.setPosition(std::min(startDragPos.x, endDragPos.x), std::min(startDragPos.y, endDragPos.y));
                dragRect.setFillColor(sf::Color(0, 0, 200, 100));
                dragRect.setSize(sf::Vector2f(std::abs(startDragPos.x - endDragPos.x), std::abs(startDragPos.y - endDragPos.y)));
            }
        }

        switch (currentState)
        {
        case MENU:
            mainMenu.HandleEvents(newEvent, m_window);
            break;
        case GAME:
            HUD::HandleEvents(newEvent, m_window);

            if (HUD::currentUnitSelected == HUD::WARRIOR)
            {
                CreateWarrior({ basePos.x + 50, basePos.y + 150 });
                HUD::ChangeUnitSelected(HUD::NO_UNIT);
                for (Buildings* object : buildings)
                {
                    object->DeselectBuilding();
                }
            }
            else if (HUD::currentUnitSelected == HUD::ARCHER)
            {
                CreateArcher({ basePos.x + 50, basePos.y + 150 });
                HUD::ChangeUnitSelected(HUD::NO_UNIT);
                for (Buildings* object : buildings)
                {
                    object->DeselectBuilding();
                }
            }

            if (HUD::currentBuildingSelected == HUD::MINE)
            {
                CreateMine(Global::GetMousePos(m_window));
                HUD::ChangeBuildingSelected(HUD::NO_BUILDING);
                for (Buildings* object : buildings)
                {
                    object->DeselectBuilding();
                }
            }

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
void Game::ProcessKeyPress(sf::Event t_event)
{
    if (sf::Keyboard::Escape == t_event.key.code)
    {
        m_exitGame = true;
    }
    if (sf::Keyboard::Q == t_event.key.code)
    {
        MakeFormation();
    }
    if (sf::Keyboard::W == t_event.key.code)
    {
        CreateMine({600,600});
    }
    if (sf::Keyboard::Enter == t_event.key.code) 
    { 
        currentState = PAUSED; 
    }
}
void Game::ProcessKeyRelease(sf::Event t_event)
{
    if (sf::Keyboard::Q == t_event.key.code)
    {
        for (Characters* temp : units)
        {
           /* if (temp != units[0] && !temp->isMoving)
            {
                if (units[0]->body.getScale().x < 0)
                {
                    temp->FlipSprite();
                }
                else if (units[0]->body.getScale().x > 0)
                {
                    temp->FlipSprite();
                }

            }*/
        }
    }
}
void Game::ProcessMousePress(sf::Event t_event)
{
    if (sf::Mouse::Left == t_event.key.code)
    {
        sf::Vector2i currentCell = Global::GetCurrentCell(m_window, gameView);
        std::cout << currentCell.x << ", " << currentCell.y << "\n";
       // tiles[currentCell.x][currentCell.y].SetShop();
        if (!BuildingUI::isActive)
        {
            isDragging = true;
            startDragPos = Global::GetWindowMousePos(m_window, gameView);
        }
    } 
    if (sf::Mouse::Right == t_event.key.code)
    {
    }
}
void Game::ProcessMouseRelease(sf::Event t_event)
{
    if (sf::Mouse::Left == t_event.key.code)
    {
        for (GameObject* object : gameObjects)
        {
            object->MouseRelease();
        }
        for (Buildings* temp : buildings)
        {
            //if(!temp->CheckIfPlaced())
           // temp->isSelected = false;
           // selectedUnits.clear();
        }

        SelectUnits();
    }
    if (sf::Mouse::Right == t_event.key.code)
    {
        for (Characters* temp : units)
        {
            temp->isSelected = false;
            selectedUnits.clear();
        }
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

        for (Buildings* object : buildings)
        {
            object->Draw();
        }
        for (Characters* object : units)
        {
            object->Draw();
        }
       /* for (GameObject* object : gameObjects)
        {
            object->Draw();
        }*/

        if (isDragging)
        {
            m_window.draw(dragRect);
        }

        BuildingUI::Draw(m_window);
        view.SetHudView();
        HUD::Render(m_window);
        break;
    case PAUSED:
        for (int row = 0; row < Global::ROWS_COLUMNS; row++)
        {
            for (int col = 0; col < Global::ROWS_COLUMNS; col++)
            {
                tiles[row][col].Render(m_window);
            }
        }
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
        ManageTimers();

        AlignFormationFacingDirection();

        ChangeThingsDependingOnTileType();

        for (GameObject* object : gameObjects)
        {
            object->Update();
            ClearFog(object->detectionCircle);
        }

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

    //jsonData["X"] = warrior.GetSprite().getPosition().x;
    //jsonData["Y"] = warrior.GetSprite().getPosition().y;

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

    std::ifstream file(loadGameDataPath);

    if (file.is_open())
    {
        nlohmann::json jsonData;
        file >> jsonData;
        file.close();

        sf::Vector2f warriorLoadedPos;
        warriorLoadedPos.x = jsonData["X"];
        warriorLoadedPos.y = jsonData["Y"];
       // warrior.SetPosition(warriorLoadedPos);

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
   // if (tiles[row][col].GetTileType() == SHOP) { return;}
   
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

   // tempPos.x = static_cast<int>(warrior.tileDetectionCircle.getPosition().x / Global::CELL_SIZE);
   // tempPos.y = static_cast<int>(warrior.tileDetectionCircle.getPosition().y / Global::CELL_SIZE);

    if (tiles[tempPos.x][tempPos.y].GetTileType() == NONE)
    {
       // warrior.currentMoveSpeed = warrior.defaultMoveSpeed;
    }
    else if (tiles[tempPos.x][tempPos.y].GetTileType() == PATH)
    {
        //warrior.currentMoveSpeed = warrior.defaultMoveSpeed * 2;
    }
    else if (tiles[tempPos.x][tempPos.y].GetTileType() == OBSTACLE)
    {
        //warrior.currentMoveSpeed = warrior.defaultMoveSpeed / 2;
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

void Game::ManageTimers()
{
    elapsedTime = incomeTimer.getElapsedTime();

    if (elapsedTime.asSeconds() >= 5.0f)
    {
        ResourceManagement::AddCoins(ResourceManagement::GetShops());
        incomeTimer.restart();
    }
}

void Game::CreateWarrior(sf::Vector2f pos)
{
    Warrior* newWarrior = new Warrior;
    newWarrior->SetPosition(pos);

    units.push_back(newWarrior);
    gameObjects.push_back(newWarrior);
}

void Game::CreateArcher(sf::Vector2f pos)
{
    Archer* newArcher = new Archer;
    newArcher->SetPosition(pos);

    units.push_back(newArcher);
    gameObjects.push_back(newArcher);
}

void Game::SelectUnits()
{
    for (Characters* temp : units)
    {
        if (dragRect.getGlobalBounds().intersects(temp->body.getGlobalBounds()))
        {
            temp->SelectCharacter();
            selectedUnits.push_back(temp);
        }
    }
    isDragging = false;
    dragRect.setSize({ 0, 0 });
}

void Game::MakeFormation()
{
    Characters* leader = nullptr;

    for (Characters* temp : units)
    {
        if (temp->isSelected)
        {
            leader = temp;
            break;
        }
    }

    if (leader != nullptr)
    {
        float xPosLeader = leader->body.getPosition().x;
        float yPosLeader = leader->body.getPosition().y;

        float xOffset = -50;
        float yOffset = -50;

        int i = -1;
        for (Characters* temp : units) 
        {
            temp->isMoving = true;
            temp->isFormationMoving = true;
            if (temp->isSelected) 
            {
                if (temp != leader)
                {
                    ++i;

                    if (i == 0)
                    {
                        yOffset = -50;

                    }
                    else if (i == 1)
                    {
                        yOffset = 0;
                    }
                    else if (i == 2)
                    {
                        yOffset = 50;
                    }
                    temp->targetPosition = { xPosLeader + xOffset, yPosLeader + yOffset };


                    if (i == 2)
                    {
                        xOffset -= 50.0f;
                        i = -1;
                    }
                }
                else
                {
                    temp->targetPosition = { xPosLeader, yPosLeader};
                }
            }
       
        }
    }

}

void Game::AlignFormationFacingDirection()
{
    for (Characters* temp : units)
    {
        if (temp != units[0] && temp->isFormationMoving && !temp->isMoving)
        {
            if (temp->body.getScale().x != units[0]->body.getScale().x)
            {
                temp->FlipSprite();
            }
            temp->isFormationMoving = false;
        }
    }
}

void Game::CreateBase(sf::Vector2f pos)
{
    int x = pos.x / Global::CELL_SIZE;
    int y = pos.y / Global::CELL_SIZE;

    float newX = (tiles[x][y].tile.getPosition().x + Global::CELL_SIZE / 2) - 2;
    float newY = (tiles[x][y].tile.getPosition().y + Global::CELL_SIZE / 2) - 20;
    sf::Vector2f newPos = { newX, newY };
    Base* newBase = new Base(newPos);
    newBase->PlaceBuilding();
    
    buildings.push_back(newBase);
    gameObjects.push_back(newBase);
   
}

void Game::CreateMine(sf::Vector2f pos)
{
    int x = pos.x / Global::CELL_SIZE;
    int y = pos.y / Global::CELL_SIZE;

    float newX = (tiles[x][y].tile.getPosition().x + Global::CELL_SIZE / 2);
    float newY = (tiles[x][y].tile.getPosition().y + Global::CELL_SIZE / 2);
    sf::Vector2f newPos = { newX, newY };
    Mine* newMine = new Mine(newPos);
    mines.push_back(newMine);
    buildings.push_back(newMine);
    gameObjects.push_back(newMine);
}

void Game::ClearFog(sf::CircleShape radius)
{
    for (int row = 0; row < Global::ROWS_COLUMNS; row++)
    {
        for (int col = 0; col < Global::ROWS_COLUMNS; col++)
        {
           
            if (radius.getGlobalBounds().intersects(tiles[row][col].tile.getGlobalBounds()))
            {
                tiles[row][col].DiscoverTile();
            }
        }
    }
}


