#include "Game.h"

std::string savePath = "";
std::string loadGameDataPath = "";
std::string loadTilesDataPath = "";
sf::Font Global::font;
sf::Font Global::tutorialFont;
bool saveGame = false;
bool loadSave = false;
bool Game::isInstructionsOpen = false;
bool Game::isControlsOpen = false;
bool Game::isInventoryOpen = false;

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

    GameManager::itemManager.LoadItemsFromJSON();

    fogTiles = new sf::RectangleShape * [Global::ROWS_COLUMNS];

    for (int i = 0; i < Global::ROWS_COLUMNS; i++)
    {
        fogTiles[i] = new sf::RectangleShape[Global::ROWS_COLUMNS];
    }

    for (int row = 0; row < Global::ROWS_COLUMNS; row++)
    {
        for (int col = 0; col < Global::ROWS_COLUMNS; col++)
        {
            sf::Vector2f temp = { static_cast<float>(row * Global::CELL_SIZE), static_cast<float>(col * Global::CELL_SIZE) };
            fogTiles[row][col].setPosition(temp);
            fogTiles[row][col].setSize({ Global::CELL_SIZE, Global::CELL_SIZE });
            fogTiles[row][col].setFillColor(sf::Color::Black);
        }
    }

   
    SetupClouds();

   // isTutoria

    mainMenu.Init();
    pauseMenu.Init();
    gameUI.Init();
    loseScreen.Init();

    elapsedTime = incomeTimer.getElapsedTime();
    HUD::Init();
    BuildingUI::Init();

    CreateHeadquarters(basePos);

    CreateMiner({ 450, 400 });

    CreateSuckler({ 150, 150 });
    CreateSuckler({ 250, 150 });
    CreateSuckler({ 150, 700 });
    SpawnEnemyBases();

    SetupTutorialPages();
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
        if (sf::Event::MouseButtonPressed == newEvent.type)
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
            mainMenu.HandleEvents(newEvent);
            break;
        case GAME:
            HUD::HandleEvents(newEvent);

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
            else if (HUD::currentUnitSelected == HUD::MINER)
            {
                CreateMiner({ basePos.x + 50, basePos.y + 150 });
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
            pauseMenu.HandleEvents(newEvent);
            break;
        case WIN:
            break;
        case LOSE:
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
        CreateSuckler({ 150, 150 });
    }
    if (sf::Keyboard::E == t_event.key.code)
    {
        currentState = LOSE;
    }
    if (sf::Keyboard::R == t_event.key.code)
    {
        GameManager::inventory.AddItem("Gold", 1);
    }
    if (sf::Keyboard::T == t_event.key.code)
    {
        GameManager::inventory.RemoveItem("Gold", 1);
    }
    if (sf::Keyboard::Enter == t_event.key.code) 
    { 
        currentState = PAUSED; 
    }
}
void Game::ProcessKeyRelease(sf::Event t_event)
{
    if (sf::Keyboard::I == t_event.key.code)
    {
        isInventoryOpen = !isInventoryOpen;
    }
}
void Game::ProcessMousePress(sf::Event t_event)
{
    if (sf::Mouse::Left == t_event.key.code)
    {
        if(isInstructionsOpen)
        {
            tutorialScreen.HandleEvent(t_event, isInstructionsOpen);
        }

        sf::Vector2i currentCell = Global::GetCurrentCell(m_window, gameView);
        std::cout << "X: " << currentCell.x << ", Y: " << currentCell.y << "\n";
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
            GameManager::buildingToPlace->MouseRelease();
            GameManager::buildingToPlace->DeselectBuilding();
            if (GameManager::buildingToPlace->CheckIfCanBePlaced(Global::GetCurrentCell(m_window, gameView)))
            {
                GameManager::buildings.push_back(GameManager::buildingToPlace);
                GameManager::buildingToPlace = nullptr;
            }
        }

        for (Characters* character : GameManager::aliveUnits)
        {

            character->MouseRelease();
            selectedUnits.clear();
        }

        if (isInventoryOpen)
        {
            GameManager::inventory.ProcessMouseRelease(t_event);
        }

        SelectUnits();

        UnlockEnemyBase();

        gameUI.HandleEvent(t_event);

    }


    if (sf::Mouse::Right == t_event.key.code)      
    {
        for (Buildings* building : GameManager::buildings)
        {
            if (building->buildingType != building->HEADQUATERS_BUILDING)
            {
                building->DeselectBuilding();
            }
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

            for (int i = 0; i < totalAmountOfClouds; i++)
            {
                m_window.draw(cloudBackground[i]);
            }

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

            for (Enemy* enemy : GameManager::enemies)
            {
                enemy->Draw();
            }

            for (Characters* unit : GameManager::units)
            {
                unit->Draw();
            }

         /*   for (Spaceship* spaceship : GameManager::spaceships)
            {
                spaceship->Draw(m_window);
            }*/

            if (isDragging)
            {
                m_window.draw(dragRect);
            }

            if (GameManager::buildingToPlace != nullptr)
            {
               GameManager::buildingToPlace->Draw();
            }

            for (Egg* egg : GameManager::eggs)
            {
                egg->Draw(m_window);

            }

            for (EnemyBase* enemyBase : GameManager::enemyBases)
            {
                enemyBase->Draw(m_window);
            }

            BuildingUI::Draw(m_window);

            // FOG - Everything after this will be hidden by the fog
            for (int row = 0; row < Global::ROWS_COLUMNS; row++)
            {
                for (int col = 0; col < Global::ROWS_COLUMNS; col++)
                {
                   m_window.draw(fogTiles[row][col]);
                }
            }
            // FOG - Everything after this will be hidden by the fog

            for (Spaceship* spaceship : GameManager::spaceships)
            {
                spaceship->Draw(m_window);

            }


        view.SetHudView();
        

            if(isInventoryOpen)
            {
                GameManager::inventory.Draw(m_window);
            }

            gameUI.Draw(m_window);
            HUD::Render(m_window);
        break;
    case PAUSED:
        view.SetHudView();
        for (int row = 0; row < Global::ROWS_COLUMNS; row++)
        {
            for (int col = 0; col < Global::ROWS_COLUMNS; col++)
            {
                GameManager::tiles[row][col].Render(m_window);
            }
        }

        pauseMenu.Render(m_window);

        if (isInstructionsOpen)
        {
            tutorialScreen.Draw(m_window);
        }

        break;
    case WIN:

        break;
    case LOSE:
        loseScreen.Draw(m_window);

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
        mainMenu.Update();
        if (isInstructionsOpen)
        {
            tutorialScreen.Update();
        }
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

        for (Enemy* enemy : GameManager::enemies)
        {
            enemy->Update();
        }

        MoveFormationWithLeader();
        for (Formation* formation : GameManager::formations)
        {
            if (formation->leader != nullptr && formation->leader->GetCurrentState(formation->leader->IDLE))
            {
                sf::Vector2f leaderPosition = formation->leader->body.getPosition();

                for (Characters* unit : formation->units)
                {
                    unit->hasFlipped = false;
                }
            }
        }

        MergeEnemies();

        SpawnSpaceships();

        for (EnemyBase* enemyBase : GameManager::enemyBases)
        {
            if(!enemyBase->isDestroyed)
            {
                enemyBase->Update();
            }
        }

        for (Spaceship* spaceship : GameManager::spaceships)
        {
            spaceship->Update();
        }

        for (Egg* egg : GameManager::eggs)
        {
            egg->Update();
        }

        HatchEggs();

        if (isInstructionsOpen)
        {
            tutorialScreen.Update();
        }

        if (GameManager::enemyBasesLeftAlive <= 0)
        {
            Display_Text("WINNER");
        }

        gameUI.Update();

        break;
    case PAUSED:
        if (isInstructionsOpen)
        {
            tutorialScreen.Update();
        }
        break;
    case WIN:
 
        break;
    case LOSE:
        loseScreen.Update();
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
    GameManager::aliveUnits.push_back(newWarrior);
}

void Game::CreateArcher(sf::Vector2f pos)
{
    Archer* newArcher = new Archer;
    newArcher->SetPosition(pos);

    GameManager::units.push_back(newArcher);
    GameManager::aliveUnits.push_back(newArcher);
}

void Game::CreateMiner(sf::Vector2f pos)
{
    Miner* newWorker = new Miner;
    newWorker->SetPosition(pos);

    GameManager::units.push_back(newWorker);
    GameManager::aliveUnits.push_back(newWorker);

}

void Game::CreateOilMan(sf::Vector2f pos)
{
    OilMan* newOilMan = new OilMan;
    newOilMan->SetPosition(pos);

    GameManager::units.push_back(newOilMan);
    GameManager::aliveUnits.push_back(newOilMan);
}

void Game::CreateHazmatMan(sf::Vector2f pos)
{
    HazmatMan* newHazmatMan = new HazmatMan;
    newHazmatMan->SetPosition(pos);

    GameManager::units.push_back(newHazmatMan);
    GameManager::aliveUnits.push_back(newHazmatMan);
}

void Game::CreateSuckler(sf::Vector2f pos)
{
    Suckler* newSuckler = new Suckler(GameManager::enemyID);
    newSuckler->SetPosition(pos);


    GameManager::enemies.push_back(newSuckler);
    GameManager::aliveEnemies.push_back(newSuckler);
    GameManager::enemyID++;
}

void Game::CreateBigSuckler(sf::Vector2f pos)
{
    Suckler* newSuckler = new Suckler(GameManager::enemyID);
    newSuckler->SetPosition(pos);
    newSuckler->Merge();

    GameManager::enemies.push_back(newSuckler);
    GameManager::aliveEnemies.push_back(newSuckler);
    GameManager::enemyID++;
}

void Game::CreateSpaceship()
{
    Spaceship* newSpaceship = new Spaceship();
    GameManager::spaceships.push_back(newSpaceship);
}


void Game::SelectUnits()
{
    for (Characters* temp : GameManager::aliveUnits)
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
    Formation *newFormation = new Formation;

    Characters* leader = nullptr;

    for (Characters* unit : selectedUnits)
    {
        if (unit->characterType == unit->ARCHER || unit->characterType == unit->WARRIOR)
        {
            newFormation->leader = unit;
            leader = unit;
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
        for (Characters* unit : selectedUnits)
        {
            if (unit->characterType == unit->ARCHER || unit->characterType == unit->WARRIOR)
            {
                unit->DeselectCharacter();

                if (unit != leader)
                {
                    ++i;
                    newFormation->units.push_back(unit);
                    unit->isMovingIntoFormation = true;
                    unit->isPartOfFormation = true;

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
                    unit->targetPosition = { xPosLeader + xOffset, yPosLeader + yOffset };
                    unit->distanceFromLeader = { xOffset, yOffset };

                    if (unit->targetPosition == unit->body.getPosition())
                    {
                        unit->DeselectCharacter();
                    }

                    if (i == 2)
                    {
                        xOffset -= 50.0f;
                        i = -1;
                    }
                }
                else
                {
                    leader->targetPosition = { xPosLeader, yPosLeader };
                    leader->DeselectCharacter();
                    leader->SetCurrentState(leader->IDLE);
                }
            }
        }
    }
   GameManager::formations.push_back(newFormation);
}

void Game::MoveFormationWithLeader()
{
    for (Formation* formation : GameManager::formations)
    {
        if (formation->leader != nullptr && formation->leader->GetCurrentState(formation->leader->MOVING))
        {
            sf::Vector2f leaderPosition = formation->leader->body.getPosition();

            for (Characters* unit : formation->units)
            {
                unit->isMovingIntoFormation = true;

                if (!unit->hasFlipped)
                {
                    if (formation->leader->body.getScale().x > 0 && unit->distanceFromLeader.x > 0)
                    {

                        unit->distanceFromLeader *= -1.0f;
                        unit->hasFlipped = true; 
                    }
                    else if (formation->leader->body.getScale().x < 0 && unit->distanceFromLeader.x < 0)
                    {

                        unit->distanceFromLeader *= -1.0f;
                        unit->hasFlipped = true;   
                    }
                }
                unit->targetPosition = leaderPosition + unit->distanceFromLeader;
            }
        }
    }

}

void Game::AlignFormationFacingDirection()
{
    for (Formation* formation : GameManager::formations)
    {
        if (formation->leader != nullptr)
        {
            for (Characters* unit : formation->units)
            {
                if (!unit->isMovingIntoFormation && unit->isPartOfFormation)
                {
                    if (formation->leader->body.getScale().x > 0 && unit->body.getScale().x < 0)
                    {
                        unit->FlipSprite();
                    }
                    else if (formation->leader->body.getScale().x < 0 && unit->body.getScale().x > 0)
                    {
                        unit->FlipSprite();
                    }
                    unit->isMovingIntoFormation = false;
                }
            }

        }

    }
    
}

void Game::HatchEggs()
{
    GameManager::eggs.erase(std::remove_if(GameManager::eggs.begin(), GameManager::eggs.end(),
        [&](Egg* egg)
        {
            if (egg->isReadyToHatch)
            {
                if (egg->eggTier == 1)
                {
                    CreateSuckler(egg->body.getPosition());
                }
                else if (egg->eggTier == 2)
                {
                    // Add another enemy but normal suckler for now - Maybe kamakaze bug who turns your guys into bad guys
                    CreateSuckler(egg->body.getPosition());
                }
                else if (egg->eggTier == 3)
                {
                    // Add another enemy but normal suckler for now - Maybe Gumper
                    CreateSuckler(egg->body.getPosition());
                }
                else if (egg->eggTier == 4)
                {
                    // Add another enemy but normal suckler for now
                    CreateBigSuckler(egg->body.getPosition());
                }
                else if (egg->eggTier == 5)
                {
                    // Add another enemy but normal suckler for now - Maybe Big Gumper
                    CreateSuckler(egg->body.getPosition());
                }
                
                return true;
            }
            return false;
        }), GameManager::eggs.end());

  
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

void Game::CreateEnemyBase(sf::Vector2f pos, Item item)
{
    EnemyBase* newEnemyBase = new EnemyBase(pos, item);
    GameManager::enemyBases.push_back(newEnemyBase);

    sf::Vector2i cellPos = Global::ConvertPositionToCell(pos);
    GameManager::tiles[cellPos.x][cellPos.y].SetTileType(TILE_USED_UP);
    GameManager::enemyBasesLeftAlive++;
}

void Game::SpawnEnemyBases()
{
    Item goldItem = GameManager::itemManager.GetItemByName("Gold");
    Item uraniumItem = GameManager::itemManager.GetItemByName("Uranium");
    Item sucklerHeadItem = GameManager::itemManager.GetItemByName("Suckler Head");
    Item sucklerTentacleItem = GameManager::itemManager.GetItemByName("Suckler Tentacle");
  


    CreateEnemyBase({ 450, 150 }, goldItem );
    CreateEnemyBase({ 250, 150 }, uraniumItem);
    CreateEnemyBase({ 50, 150 }, sucklerHeadItem);
    CreateEnemyBase({ 450, 550 }, sucklerTentacleItem);
}

void Game::SpawnSpaceships()
{
    if (GameManager::spaceShipTimer.getElapsedTime().asSeconds() > spaceShipSpawnDelay)
    {
        CreateSpaceship();
        for (Spaceship* spaceship : GameManager::spaceships)
        {
            spaceship->Init();
        }
        std::cout << GameManager::spaceships.size() << " spaceships in bound \n";
        GameManager::spaceShipTimer.restart();

    }
}


void Game::MergeEnemies()
{
    // Finding Merge
    for (Enemy* x : GameManager::enemies)
    {
        // Skips if its not a merge and skips if it has already startedMerging
        if (x->enemyType != x->SUCKLER_MALE || x->hasFoundMerge) { continue; }

        for (Enemy* y : GameManager::enemies)
        {
            if (y->enemyType != y->SUCKLER_FEMALE || y->hasFoundMerge) { continue; }

            if (x != y)
            {
                if (x->IsCharacterWithinRadius(y->body))
                {
                    x->hasFoundMerge = true;
                    x->ChangeState(x->MERGING);
                    y->hasFoundMerge = true;
                    y->ChangeState(y->MERGING);

                    y->targetPos = x->body.getPosition();
                    y->target = x;

                }
            }
        }
    }

    // Actually merge enemies
    for (Enemy* x : GameManager::enemies)
    {
        if (x->hasMerged) { continue; }

        if (x->target != nullptr)
        {
            sf::Vector2f direction = x->body.getPosition() - x->target->body.getPosition();
            float distance = std::hypot(direction.x, direction.y);

            if (distance < 0.1)
            {
                x->hasMerged = true;
                x->ChangeState(x->IDLE);
                x->target->DeleteEnemy();
                break;
            }
        }
    }


}

void Game::UnlockEnemyBase()
{
    for (EnemyBase* enemyBase : GameManager::enemyBases)
    {
        if (enemyBase->isDestroyed) { continue; }

        for (Characters* character : GameManager::aliveUnits)
        {
            sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());

            if (character->IsEnemyInAttackRadius(enemyBase->body) && enemyBase->body.getGlobalBounds().contains(mousePos))
            {
                std::string itemName = enemyBase->itemRequired.GetName();
                Item* itemInInventory;

                if (GameManager::inventory.GetInventoryItemByName(itemName) != nullptr)
                {
                    itemInInventory = GameManager::inventory.GetInventoryItemByName(itemName);
                    int amount = itemInInventory->GetQuantity();

                    if (amount > 5) { amount = 5; }

                    GameManager::inventory.RemoveItem(itemName, amount);
                    enemyBase->itemRequired.DecreaseQuantity(amount);
                }
            }
        }
    }
}

void Game::ClearFog(sf::CircleShape radius)
{
    sf::Vector2f circleCenter = radius.getPosition();
    float circleRadius = radius.getRadius();

    for (int row = 0; row < Global::ROWS_COLUMNS; row++)
    {
        for (int col = 0; col < Global::ROWS_COLUMNS; col++)
        {
            if (fogTiles[row][col].getFillColor() == sf::Color::Transparent) { continue; }

            sf::Vector2f tileCenter = fogTiles[row][col].getPosition();
            float tileRadius = std::min(fogTiles[row][col].getLocalBounds().width, fogTiles[row][col].getLocalBounds().height) / 2.0f;
            float distance = Global::Distance(circleCenter, tileCenter);

            if (distance <= (circleRadius * 0.7) + tileRadius)
            {
                fogTiles[row][col].setFillColor(sf::Color::Transparent);
            }
            else if (distance <= circleRadius + tileRadius && fogTiles[row][col].getFillColor() != sf::Color::Transparent)
            {
                sf::Color colour = fogTiles[row][col].getFillColor();
                colour.a = 200;
                fogTiles[row][col].setFillColor(colour);
            }
            else if (distance > circleRadius + tileRadius && fogTiles[row][col].getFillColor() != sf::Color::Transparent)
            {
                fogTiles[row][col].setFillColor(sf::Color::Black);
            }
        }
    }
}

void Game::SetupClouds()
{
    float size = (Global::ROWS_COLUMNS * Global::CELL_SIZE) / divider;

    sf::Vector2f topPosition(0, -size);
    sf::Vector2f bottomPosition(0, Global::ROWS_COLUMNS * Global::CELL_SIZE);
    sf::Vector2f leftPosition(-size, 0);
    sf::Vector2f rightPosition(Global::ROWS_COLUMNS * Global::CELL_SIZE, 0);

    sf::Vector2f topLeftPosition(-size, -size);
    sf::Vector2f topRightPosition(Global::ROWS_COLUMNS * Global::CELL_SIZE, -size);
    sf::Vector2f bottomLeftPosition(-size, Global::ROWS_COLUMNS * Global::CELL_SIZE);
    sf::Vector2f bottomRightPosition(Global::ROWS_COLUMNS * Global::CELL_SIZE, Global::ROWS_COLUMNS * Global::CELL_SIZE);

    for (int i = 0; i < totalAmountOfClouds; i++)
    {
        cloudBackground[i].setTexture(&Textures::GetInstance().GetTexture("cloud"));
        cloudBackground[i].setSize({ size, size });

        if (i < divider)
        {
            // Top
            cloudBackground[i].setPosition(i * size, topPosition.y);
        }
        else if (i >= divider && i < divider * 2)
        {
            // Bottom
            cloudBackground[i].setPosition((i - divider) * size, bottomPosition.y);
        }
        else if (i >= divider * 2 && i < divider * 3)
        {
            // Left
            cloudBackground[i].setPosition(leftPosition.x, (i - divider * 2) * size);
        }
        else if (i >= divider * 3 && i < divider * 4)
        {
            // Right
            cloudBackground[i].setPosition(rightPosition.x, (i - divider * 3) * size);
        }
        else if (i == divider * 4)
        {
            // Top Left corner
            cloudBackground[i].setPosition(topLeftPosition);
        }
        else if (i == divider * 4 + 1)
        {
            // Top Right corner
            cloudBackground[i].setPosition(topRightPosition);
        }
        else if (i == divider * 4 + 2)
        {
            // Bottom Left corner
            cloudBackground[i].setPosition(bottomLeftPosition);
        }
        else if (i == divider * 4 + 3)
        {
            // Bottom Right corner
            cloudBackground[i].setPosition(bottomRightPosition);
        }
    }
}

void Game::SetupTutorialPages()
{
    tutorialScreen.AddPage("The Upper-Cliff Valley!",
        "An excting RTS game where you can train units to fight enemies\nCreate buildings to gather resources and\nDefend your base from the enemies!",
        Textures::GetInstance().GetTexture("train-units"));
    tutorialScreen.AddPage("Headquaters",
        "This is your main building in the game\nFrom here, you can train units and create buildings\nIf this gets destroyed you will lose the game\nSo, defend it at all costs!",
        Textures::GetInstance().GetTexture("hq-icon"));
    tutorialScreen.AddPage("Training units",
        "To train units, click on the HQ and select the icon as seen below\nA HUD menu will appear at the bottom\nThen select the unit you want to train",
        Textures::GetInstance().GetTexture("train-units"));
    tutorialScreen.AddPage("Types of units",
        "There are 2 different types of units: Fighters and Workers\nFighters: are used to attack enemies and destroy enemies base\nWorkers: get assigned to buildings to gather resources",
        Textures::GetInstance().GetTexture("warrior-icon"));
    tutorialScreen.AddPage("Creating buildings",
        "You an create buildings the exact same way as units\nBuildings are way to generate resources\n You do this by assigning workers to them",
        Textures::GetInstance().GetTexture("build-hammer"));
    tutorialScreen.AddPage("Types of buildings",
        "There are 3 types of buildings you can create\nGold mines produce gold and miners are assigned to them\nOil extractors produce oil\nReactors produce uranium...who's ranium?\n",
        Textures::GetInstance().GetTexture("mine"));
    tutorialScreen.AddPage("Inventory",
        "There are 3 types of buildings you can create\nGold mines produce gold and miners are assigned to them\nOil extractors produce oil\nReactors produce uranium...who's ranium?\n",
        Textures::GetInstance().GetTexture("Empty"));
    tutorialScreen.AddPage("Formations",
        "There are 3 types of buildings you can create\nGold mines produce gold and miners are assigned to them\nOil extractors produce oil\nReactors produce uranium...who's ranium?\n",
        Textures::GetInstance().GetTexture("Empty"));
    tutorialScreen.AddPage("Types of enemy",
        "There are 3 types of buildings you can create\nGold mines produce gold and miners are assigned to them\nOil extractors produce oil\nReactors produce uranium...who's ranium?\n",
        Textures::GetInstance().GetTexture("suckler"));
    tutorialScreen.AddPage("Enemy Base's",
        "There are 3 types of buildings you can create\nGold mines produce gold and miners are assigned to them\nOil extractors produce oil\nReactors produce uranium...who's ranium?\n",
        Textures::GetInstance().GetTexture("enemy-base"));
    tutorialScreen.AddPage("Spaceships",
        "There are 3 types of buildings you can create\nGold mines produce gold and miners are assigned to them\nOil extractors produce oil\nReactors produce uranium...who's ranium?\n",
        Textures::GetInstance().GetTexture("spaceship-icon"));
}


