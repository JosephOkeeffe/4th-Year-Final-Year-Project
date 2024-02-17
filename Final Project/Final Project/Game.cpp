#include "Game.h"

std::string savePath = "";
std::string loadGameDataPath = "";
std::string loadTilesDataPath = "";
sf::Font Global::font;
bool saveGame = false;
bool loadSave = false;

Game::Game() :
    m_window{ sf::VideoMode{ Global::S_WIDTH, Global::S_HEIGHT, 32U }, "The Big One" },
    m_exitGame{ false },
    view(m_window, gameView, hudView)
{
    Global::LoadFont();
    GameManager::SetWindow(m_window);
    GameManager::SetView(gameView);
    GameManager::InitTiles();

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

void Game::Init()
{
    srand(time(nullptr));
    Global::font.loadFromFile("./assets/fonts/Flinton.otf");
    mainMenu.Init(m_window, Global::font);
    pauseMenu.Init(m_window, Global::font);

    elapsedTime = incomeTimer.getElapsedTime();
    HUD::Init(m_window, Global::font);
    BuildingUI::Init();

    CreateHeadquarters(basePos);
    CreateArcher({ 300, 400 });
    CreateWarrior({ 350, 400 });
    CreateWarrior({ 400, 400 });
    CreateWorker({ 450, 400 });
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
                for (Buildings* object : GameManager::buildings)
                {
                    object->DeselectBuilding();
                }
            }
            else if (HUD::currentUnitSelected == HUD::ARCHER)
            {
                CreateArcher({ basePos.x + 50, basePos.y + 150 });
                HUD::ChangeUnitSelected(HUD::NO_UNIT);
                for (Buildings* object : GameManager::buildings)
                {
                    object->DeselectBuilding();
                }
            }
            else if (HUD::currentUnitSelected == HUD::WORKER)
            {
                CreateWorker({ basePos.x + 50, basePos.y + 150 });
                HUD::ChangeUnitSelected(HUD::NO_UNIT);
                for (Buildings* object : GameManager::buildings)
                {
                    object->DeselectBuilding();
                }
            }
            else if (HUD::currentUnitSelected == HUD::OIL_MAN)
            {
                CreateOilMan({ basePos.x + 50, basePos.y + 150 });
                HUD::ChangeUnitSelected(HUD::NO_UNIT);
                for (Buildings* object : GameManager::buildings)
                {
                    object->DeselectBuilding();
                }
            }
            else if (HUD::currentUnitSelected == HUD::HAZMAT_MAN)
            {
                CreateHazmatMan({ basePos.x + 50, basePos.y + 150 });
                HUD::ChangeUnitSelected(HUD::NO_UNIT);
                for (Buildings* object : GameManager::buildings)
                {
                    object->DeselectBuilding();
                }
            }

            // Buildings

            if (HUD::currentBuildingSelected == HUD::MINE)
            {
                CreateGoldMine();
                HUD::ChangeBuildingSelected(HUD::NO_BUILDING);
                for (Buildings* object : GameManager::buildings)
                {
                    object->DeselectBuilding();
                }
            }

            if (HUD::currentBuildingSelected == HUD::OIL_REFINERY)
            {
                CreateOilExtractor();
                HUD::ChangeBuildingSelected(HUD::NO_BUILDING);
                for (Buildings* object : GameManager::buildings)
                {
                    object->DeselectBuilding();
                }
            }

            if (HUD::currentBuildingSelected == HUD::URANIUM_EXTRACTOR)
            {
                CreateUraniumExtractor();
                HUD::ChangeBuildingSelected(HUD::NO_BUILDING);
                for (Buildings* object : GameManager::buildings)
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
      
    }
}
void Game::ProcessMousePress(sf::Event t_event)
{
    if (sf::Mouse::Left == t_event.key.code)
    {
        sf::Vector2i currentCell = Global::GetCurrentCell(m_window, gameView);
        std::cout << currentCell.x << ", " << currentCell.y << "\n";
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
        // SOmehow add a way where if unit is selected you cant select enemy
        for (Buildings* building : GameManager::buildings)
        {
            if (selectedUnits.size() == 0)
            {
                building->MouseRelease();
            }
            else
            {
                Display_Text("Selected Unit");
            }
        }

        if (GameManager::buildingToPlace != nullptr)
        {
            // NEed to fix this cant push back if istn vALID
            GameManager::buildingToPlace->MouseRelease();
            GameManager::buildingToPlace->DeselectBuilding();
            if (GameManager::buildingToPlace->CheckIfCanBePlaced(Global::GetCurrentCell(m_window, gameView)))
            {
                GameManager::buildings.push_back(GameManager::buildingToPlace);
                GameManager::buildingToPlace = nullptr;
            }
        }

        for (Characters* character : GameManager::units)
        {
            character->MouseRelease();
            selectedUnits.clear();
        }

        SelectUnits();
    }
    if (sf::Mouse::Right == t_event.key.code)      
    {
        for (Buildings* building : GameManager::buildings)
        {
            building->DeselectBuilding();
        }
        for (Characters* temp : GameManager::units)
        {
            temp->DeselectCharacter();
            selectedUnits.clear();
        }

        if (GameManager::buildingToPlace != nullptr)
        {
         
            GameManager::buildingToPlace = nullptr;
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
                    GameManager::tiles[row][col].Render(m_window);
                }
            }

            for (Buildings* building : GameManager::buildings)
            {
                building->Draw();
            }
            for (Characters* unit : GameManager::units)
            {
                unit->Draw();
            }

            if (isDragging)
            {
                m_window.draw(dragRect);
            }

            if (GameManager::buildingToPlace != nullptr)
            {
               GameManager::buildingToPlace->Draw();
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
                GameManager::tiles[row][col].Render(m_window);
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

        if (GameManager::buildingToPlace != nullptr)
        {
            GameManager::buildingToPlace->Update();
        }
        view.MoveScreen();
        ManageTimers();

        AlignFormationFacingDirection();

        //ChangeThingsDependingOnTileType();

        for (Buildings* building : GameManager::buildings)
        {
            building->Update();
            ClearFog(building->detectionCircle);
        }

        for (Characters* character : GameManager::units)
        {
            character->Update();
            ClearFog(character->detectionCircle);
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

    //jsonData["Coins"] = ResourceManagement::GetCoins();
    //jsonData["Shops"] = ResourceManagement::GetShops();

    for (int row = 0; row < Global::ROWS_COLUMNS; row++)
    {
        for (int col = 0; col < Global::ROWS_COLUMNS; col++)
        {
            jsonData["TileType"][row][col] = GameManager::tiles[row][col].GetTileType();
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
                GameManager::tiles[row][col].SetTileType(static_cast<TileType>(tileType));
            }
        }

        std::cout << "Loaded Game Data:\n";
        std::cout << "X: " << warriorLoadedPos.x << "\n";
        std::cout << "Y: " << warriorLoadedPos.y << "\n";
        std::cout << "Coins: " << coins << "\n";
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
        GameManager::tiles[row][col].SetGrassType(static_cast<GrassType>(type));
        GameManager::tiles[row][col].SetTileType(NONE);

    }
    else if (type >= BRIDGE1 && type <= PATH10)
    {
        GameManager::tiles[row][col].SetGrassType(static_cast<GrassType>(type));
        GameManager::tiles[row][col].SetTileType(PATH);
    }
    else if (type >= WATER1 && type <= WATER13)
    {
        GameManager::tiles[row][col].SetGrassType(static_cast<GrassType>(type));
        GameManager::tiles[row][col].SetTileType(OBSTACLE);
    }
    else if (type >= GOLD_ORE_NODE && type <= OIL_POOL_NODE)
    {
        GameManager::tiles[row][col].SetGrassType(static_cast<GrassType>(type));
        GameManager::tiles[row][col].SetTileType(RESOURCE);
    }
}

//void Game::ChangeThingsDependingOnTileType()
//{
//    sf::Vector2i tempPos;
//
//   // tempPos.x = static_cast<int>(warrior.tileDetectionCircle.getPosition().x / Global::CELL_SIZE);
//   // tempPos.y = static_cast<int>(warrior.tileDetectionCircle.getPosition().y / Global::CELL_SIZE);
//
//    if (GameManager::tiles[tempPos.x][tempPos.y].GetTileType() == NONE)
//    {
//       // warrior.currentMoveSpeed = warrior.defaultMoveSpeed;
//    }
//    else if (GameManager::tiles[tempPos.x][tempPos.y].GetTileType() == PATH)
//    {
//        //warrior.currentMoveSpeed = warrior.defaultMoveSpeed * 2;
//    }
//    else if (GameManager::tiles[tempPos.x][tempPos.y].GetTileType() == OBSTACLE)
//    {
//        //warrior.currentMoveSpeed = warrior.defaultMoveSpeed / 2;
//    }
//}

void Game::ManageTimers()
{
    elapsedTime = incomeTimer.getElapsedTime();

    if (elapsedTime.asSeconds() >= 5.0f)
    {
        incomeTimer.restart();
    }
}

void Game::CreateWarrior(sf::Vector2f pos)
{
    Warrior* newWarrior = new Warrior;
    newWarrior->SetPosition(pos);

    GameManager::units.push_back(newWarrior);
}

void Game::CreateArcher(sf::Vector2f pos)
{
    Archer* newArcher = new Archer;
    newArcher->SetPosition(pos);

    GameManager::units.push_back(newArcher);
}

void Game::CreateWorker(sf::Vector2f pos)
{
    Worker* newWorker = new Worker;
    newWorker->SetPosition(pos);

    GameManager::units.push_back(newWorker);
}

void Game::CreateOilMan(sf::Vector2f pos)
{
    OilMan* newOilMan = new OilMan;
    newOilMan->SetPosition(pos);

    GameManager::units.push_back(newOilMan);
}

void Game::CreateHazmatMan(sf::Vector2f pos)
{
    HazmatMan* newHazmatMan = new HazmatMan;
    newHazmatMan->SetPosition(pos);

    GameManager::units.push_back(newHazmatMan);
}

void Game::SelectUnits()
{
    for (Characters* temp : GameManager::units)
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

    for (Characters* temp : GameManager::units)
    {
        if (temp->characterType == temp->ARCHER || temp->characterType == temp->WARRIOR)
        {
            if (temp->GetSelected())
            {
                leader = temp;
                break;
            }
        }
    }

    if (leader != nullptr)
    {
        float xPosLeader = leader->body.getPosition().x;
        float yPosLeader = leader->body.getPosition().y;

        float xOffset = -50;
        float yOffset = -50;

        int i = -1;
        for (Characters* temp : GameManager::units)
        {
            if(temp->characterType == temp->ARCHER || temp->characterType == temp->WARRIOR)
            {
                temp->SetCurrentState(temp->MOVING);
                temp->isFormationMoving = true;
                if (temp->GetSelected())
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
                        temp->targetPosition = { xPosLeader, yPosLeader };
                    }
                }
            }
       
        }
    }

}

// DOes not work
void Game::AlignFormationFacingDirection()
{
    for (Characters* unit : GameManager::units)
    {
        if (unit != GameManager::units[0] && unit->isFormationMoving && unit->currentState!= unit->MOVING)
        {
            if (unit->direction != GameManager::units[0]->direction)
            {
                unit->FlipSprite();
            }
            unit->isFormationMoving = false;
        }
    }
}

void Game::CreateHeadquarters(sf::Vector2f pos)
{
    int x = pos.x / Global::CELL_SIZE;
    int y = pos.y / Global::CELL_SIZE;

    float newX = (GameManager::tiles[x][y].tile.getPosition().x + Global::CELL_SIZE / 2) - 2;
    float newY = (GameManager::tiles[x][y].tile.getPosition().y + Global::CELL_SIZE / 2) - 20;
    sf::Vector2f newPos = { newX, newY };
    Headquarters* newHQ = new Headquarters(newPos);
    newHQ->PlaceBuilding();
    GameManager::headquarters = newHQ;
    GameManager::buildings.push_back(newHQ);
}

void Game::CreateGoldMine()
{
    GoldMine* newGoldMine = new GoldMine({1,1});
    GameManager::buildingToPlace = newGoldMine;
}

void Game::CreateOilExtractor()
{
    OilExtractor* newOilExtractor = new OilExtractor({ 1,1 });
    GameManager::buildingToPlace = newOilExtractor;
}

void Game::CreateUraniumExtractor()
{
    UraniumExtractor* newUraniumExtractor = new UraniumExtractor({ 1,1 });
    GameManager::buildingToPlace = newUraniumExtractor;
}

void Game::ClearFog(sf::CircleShape radius)
{
    for (int row = 0; row < Global::ROWS_COLUMNS; row++)
    {
        for (int col = 0; col < Global::ROWS_COLUMNS; col++)
        {
           
            if (radius.getGlobalBounds().intersects(GameManager::tiles[row][col].tile.getGlobalBounds()))
            {
                GameManager::tiles[row][col].DiscoverTile();
            }
        }
    }
}


