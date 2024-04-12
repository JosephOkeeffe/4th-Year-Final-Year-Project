#include "Enemy.h"

void Enemy::Init(sf::Texture& _texture)
{
	srand(time(nullptr));

	body.setTexture(_texture);
	body.setOrigin(body.getTextureRect().width / 2, body.getTextureRect().height / 2);

	enemyDetectionCircle.setRadius(detectionRadius);
	enemyDetectionCircle.setOrigin(detectionRadius, detectionRadius);
	enemyDetectionCircle.setPosition(body.getPosition());
	enemyDetectionCircle.setFillColor(sf::Color(255, 255, 255, 100));
	enemyDetectionCircle.setOutlineThickness(1);
	enemyDetectionCircle.setOutlineColor(sf::Color(255, 0, 0, 255));

	wanderCircle.setRadius(wanderRadius);
	wanderCircle.setOrigin(wanderRadius, wanderRadius);
	wanderCircle.setPosition(body.getPosition());
	wanderCircle.setFillColor(sf::Color(0, 255, 0, 50));
	wanderCircle.setOutlineThickness(1);
	wanderCircle.setOutlineColor(sf::Color(0, 255, 0, 255));

	itemDropSprite.setSize({ 30, 30 });
	itemDropSprite.setFillColor(sf::Color::White);
	itemDropSprite.setOrigin(itemDropSprite.getSize().x / 2, itemDropSprite.getSize().y / 2);

	int x = body.getPosition().x / Global::CELL_SIZE;
	int y = body.getPosition().y / Global::CELL_SIZE;

	shader.InitShader("GlowShader.frag");

	wanderTimer.restart();
}

void Enemy::Draw()
{
	GameManager::GetWindow()->draw(body);

	if (!GetCurrentState(DEAD))
	{
		stats.DisplayHealthBar(*GameManager::GetWindow(), { body.getPosition().x, body.getPosition().y - 50 });
		particleSystem.draw(*GameManager::GetWindow());


		for (Projectile* projectile : projectiles)
		{
			projectile->Draw(*GameManager::GetWindow());
		}
	}
	else
	{
		if (!isItemCollected)
		{
			GameManager::GetWindow()->draw(itemDropSprite, &shader.GetShader());
		}
	}
}

// TO DO
// // SOUNDS
// USE GIPHY FOR GIFS
// SAVE GAME
// End game screen 
// Make better UI that shows things all the time , resources, buildings etc
// ENEMY IDEAS - Enemy hits player and converts them into bad guy (spawn enem,y on position of dead good guy)
// IDEAS - Debuffs


void Enemy::Update()
{
	if (stats.GetCurrentHealth() <= 0 && !GetCurrentState(DEAD))
	{
		ChangeStateToDead();
		GetRandomItemFromDropTable();
	}

	if (GetCurrentState(DEAD) && !isItemCollected)
	{
		shader.Update();

		for (Enemy* temp : GameManager::enemies)
		{
			// Bug with items merging into one
			if (temp == this || !temp->GetCurrentState(DEAD)) { continue; }

			if (itemDropSprite.getGlobalBounds().intersects(temp->itemDropSprite.getGlobalBounds()))
			{
				itemDropSprite.setPosition(itemDropSprite.getPosition().x - 25, itemDropSprite.getPosition().y - 25);
				temp->itemDropSprite.setPosition(temp->itemDropSprite.getPosition().x + 25, temp->itemDropSprite.getPosition().y + 25);
			}
		}

		UnitsCanCollectItemDrop();
	}

	if (!GetCurrentState(DEAD))
	{
		currentTilePos = Global::ConvertPositionToCell(body.getPosition());
		currentTile = &GameManager::tiles[currentTilePos.x][currentTilePos.y];

		enemyDetectionCircle.setPosition(body.getPosition());
		wanderCircle.setPosition(body.getPosition());
		CheckIfAnythingIsWithinRadius();
		UpdateStates();
		particleSystem.Update();

		if (body.getColor() == sf::Color::Red && redTimer.getElapsedTime().asSeconds() > 0.3)
		{
			body.setColor(sf::Color::White);
		}

		if (GetCurrentState(MOVING) && !path.empty())
		{
			Move();
		}
		else if (GetCurrentState(MOVING) && path.empty())
		{
			ChangeState(IDLE);
		}

		if (GetCurrentState(IDLE) && wanderTimer.getElapsedTime().asSeconds() > 10)
		{
			std::vector<sf::Vector2f> unitsToMove = GetUnitsToMoveTowardsWithinWanderRadius();
			std::vector<sf::Vector2f> mergeTargets = GetMergeTargetsToMoveTowardsWithinWanderRadius();
			std::vector<sf::Vector2f> buildings = GetBuildingsToMoveTowardsWithinWanderRadius();

			pointsOfInterest.insert(pointsOfInterest.end(), unitsToMove.begin(), unitsToMove.end());
			pointsOfInterest.insert(pointsOfInterest.end(), mergeTargets.begin(), mergeTargets.end());
			pointsOfInterest.insert(pointsOfInterest.end(), buildings.begin(), buildings.end());


			if (pointsOfInterest.size() > 0)
			{
				MoveTowardsPointOfInterest();
				pointsOfInterest.clear();
			}
			else
			{
				StartWandering();
			}					
			
		}

		ProjectilesCollideWithPlayerUnits();
		ProjectilesCollideWithPlayerBuildings();
		
	}
}

void Enemy::UpdateStates()
{
	if (GetCurrentState(IDLE))
	{
		enemyDetectionCircle.setFillColor(sf::Color(255, 255, 255, 100));
	}
	else if (GetCurrentState(MOVING))
	{

	}
	else if (GetCurrentState(MERGING))
	{
	}
	else if (GetCurrentState(ATTACKING))
	{
		enemyDetectionCircle.setFillColor(sf::Color(255, 0, 0, 100));
	}
	else if (GetCurrentState(DEAD))
	{

	}
}

bool Enemy::GetCurrentState(CurrentState checkState)
{
	if (state == checkState)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::ChangeState(CurrentState newState)
{
	state = newState;
}

void Enemy::SetPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void Enemy::Move()
{
	float length = 0;

	if (walkingTrailTimer.getElapsedTime().asSeconds() > 0.3)
	{
		MakeWalkingTrail();
	}

	targetPosition = path.front()->tile.getPosition();
	targetPosition.x += pathFindingXOffset;
	targetPosition.y += pathFindingYOffset;

	direction = targetPosition - body.getPosition();
	length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length != 0)
	{
		direction /= length;
		float angle = std::atan2(direction.y, direction.x) * 180 / Global::PI;
		body.setRotation(angle + 90);
	}

	if (length > 5)
	{
		velocity = direction * currentMoveSpeed;
		body.move(velocity);
	}
	else
	{
		path.erase(path.begin());

		if (!path.empty())
		{
			targetPosition = path.front()->tile.getPosition();
		}
		else
		{
			ChangeState(IDLE);
			wanderTimer.restart();
		}
	}
}

void Enemy::MoveTowardsPointOfInterest()
{
	ChangeState(MOVING);

	float closestDistance = std::numeric_limits<float>::max();
	sf::Vector2f closestVector;
	int randomOffset = 3;

	for (sf::Vector2f targets : pointsOfInterest)
	{
		float currentDistance = Global::Distance(body.getPosition(), targets);
		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			closestVector = targets;
		}
	}

	sf::Vector2i startPos = Global::ConvertPositionToCell(body.getPosition());
	startTile = &GameManager::tiles[startPos.x][startPos.y];

	float randX = Global::GetRandomNumber(-randomOffset, randomOffset);
	float randY = Global::GetRandomNumber(-randomOffset, randomOffset);

	sf::Vector2i endPos = Global::ConvertPositionToCell(closestVector);

	while (endPos.x + randX < 1 || endPos.y + randY < 1)
	{
		randX = Global::GetRandomNumber(-randomOffset, randomOffset);
		randY = Global::GetRandomNumber(-randomOffset, randomOffset);
	}

	endPos.x += randX;
	endPos.y += randY;


	goalTile = &GameManager::tiles[endPos.x][endPos.y];

	path = GameManager::FindPath(startTile, goalTile, false);
}

void Enemy::StartWandering()
{
	ChangeState(MOVING);

	sf::Vector2i cellPos = Global::ConvertPositionToCell(body.getPosition());
	startTile = &GameManager::tiles[cellPos.x][cellPos.y];

	// Getting the tiles in the wander radius
	int tilesInRadius = wanderRadius / Global::CELL_SIZE;

	// Getting a random tile to move to within the radius
	int randX = randX = (rand() % (2 * tilesInRadius + 1)) - tilesInRadius;
	int randY = randY = (rand() % (2 * tilesInRadius + 1)) - tilesInRadius;

	while (cellPos.x + randX < 1 || cellPos.y + randY < 1 || 
		   cellPos.x + randX > Global::ROWS_COLUMNS - 1 || cellPos.y + randY > Global::ROWS_COLUMNS - 1)
	{
		randX = (rand() % (2 * tilesInRadius + 1)) - tilesInRadius;
		randY = (rand() % (2 * tilesInRadius + 1)) - tilesInRadius;
	}
	// making the goal tile that random tile
	cellPos.x += randX;
	cellPos.y += randY;
	goalTile = &GameManager::tiles[cellPos.x][cellPos.y];
	path = GameManager::FindPath(startTile, goalTile, false);

	wanderTimer.restart();
}

bool Enemy::IsCharacterWithinRadius(sf::Sprite& target)
{
	float dx = body.getPosition().x - target.getPosition().x;
	float dy = body.getPosition().y - target.getPosition().y;
	float distance = std::hypot(dx, dy);

	return (distance <= detectionRadius);
}

void Enemy::CheckIfAnythingIsWithinRadius()
{
	bool anyCharacterWithinRadius = false;
	float stateChangeDelay = 0.5f;

	for (Characters* unit : GameManager::aliveUnits)
	{
		if (IsCharacterWithinRadius(unit->body))
		{
			anyCharacterWithinRadius = true;
			if(isReadyToAttack)
			{
				isReadyToAttack = false;
				attackingStateChangeTimer.restart();
			}
		}
	}

	for (Buildings* building : GameManager::buildings)
	{
		if (IsCharacterWithinRadius(building->body))
		{
			anyCharacterWithinRadius = true;
			if (isReadyToAttack)
			{
				isReadyToAttack = false;
				attackingStateChangeTimer.restart();
			}
		}
	}

	if (!GetCurrentState(MERGING))
	{
		if (anyCharacterWithinRadius )
		{
			if (attackingStateChangeTimer.getElapsedTime().asSeconds() > stateChangeDelay)
			{
				ChangeState(ATTACKING);
			}
		}
		else
		{
			if (!GetCurrentState(MOVING))
			{
				isReadyToAttack = true;
				ChangeState(IDLE);
			}
		}
	}
}

std::vector<Characters*> Enemy::GetUnitsWithinRadius()
{
	bool anyCharacterWithinRadius = false;
	std::vector<Characters*> unitsInRadius;

	for (Characters* unit : GameManager::aliveUnits)
	{
		if (IsCharacterWithinRadius(unit->body))
		{
			unitsInRadius.push_back(unit);
			anyCharacterWithinRadius = true;
		}
	}

	return unitsInRadius;
}

Characters* Enemy::FindClosestEnemy()
{
	float closestDistance = std::numeric_limits<float>::max();
	Characters* closest = nullptr;

	sf::Vector2f enemyPosition = body.getPosition();

	for (Characters* unit : GetUnitsWithinRadius())
	{
		float distance = std::sqrt(std::pow(unit->body.getPosition().x - enemyPosition.x, 2) + std::pow(unit->body.getPosition().y - enemyPosition.y, 2));

		if (distance < closestDistance)
		{
			closestDistance = distance;
			closest = unit;
		}
	}

	return closest;
}

Buildings* Enemy::FindClosestBuilding()
{
	float closestDistance = std::numeric_limits<float>::max();
	Buildings* closest = nullptr;

	sf::Vector2f buildingPosition = body.getPosition();

	for (Buildings* building : GameManager::buildings)
	{
		float distance = std::sqrt(std::pow(building->body.getPosition().x - buildingPosition.x, 2) + std::pow(building->body.getPosition().y - buildingPosition.y, 2));

		if (distance < closestDistance)
		{
			closestDistance = distance;
			closest = building;
		}
	}

	return closest;
}

std::vector<sf::Vector2f> Enemy::GetUnitsToMoveTowardsWithinWanderRadius()
{
	std::vector<sf::Vector2f> unitsInRadius;

	sf::Vector2f currentPos = body.getPosition();
	sf::Vector2f targetPos;
	float distance;

	for (Characters* unit : GameManager::aliveUnits)
	{
		targetPos = unit->body.getPosition();
		distance = Global::Distance(currentPos, targetPos);

		if (distance <= wanderRadius)
		{
			unitsInRadius.push_back(unit->body.getPosition());
		}
	}

	return unitsInRadius;
}

std::vector<sf::Vector2f> Enemy::GetMergeTargetsToMoveTowardsWithinWanderRadius()
{
	std::vector<sf::Vector2f> meregTargetsInRadius;

	sf::Vector2f currentPos = body.getPosition();
	sf::Vector2f targetPos;
	float distance;

	// Look for merge if this enemy is female
	if (enemyType == SUCKLER_FEMALE)
	{
		for (Enemy* enemy : GameManager::aliveEnemies)
		{
			// Only look for males to merge with if enemy is female
			if (enemy->enemyType != enemy->SUCKLER_MALE) { continue; }

			targetPos = enemy->body.getPosition();
			distance = Global::Distance(currentPos, targetPos);

			if (distance <= wanderRadius)
			{
				meregTargetsInRadius.push_back(enemy->body.getPosition());
			}

		}
	}

	return meregTargetsInRadius;
}

std::vector<sf::Vector2f> Enemy::GetBuildingsToMoveTowardsWithinWanderRadius()
{
	std::vector<sf::Vector2f> buildingsInRadius;

	sf::Vector2f currentPos = body.getPosition();
	sf::Vector2f targetPos;
	float distance;

	for (Buildings* building : GameManager::buildings)
	{
		targetPos = building->body.getPosition();
		distance = Global::Distance(currentPos, targetPos);

		if (distance <= wanderRadius)
		{
			buildingsInRadius.push_back(building->body.getPosition());
		}
	}

	return buildingsInRadius;
}

void Enemy::TakeDamage(int damage)
{
	stats.LoseHealth(damage);
	body.setColor(sf::Color::Red);
	redTimer.restart();

	for (int i = 0; i < 10; i++)
	{ 
		particleSystem.AddSpriteParticle(body.getPosition(), Global::GetRandomVector() * 2.0f, sf::Color::White, Textures::GetInstance().GetTexture("blood"), 20, 0.2, 1);
	}
}																					 

void Enemy::ApplyKnockback(sf::Vector2f knockbackDirection, float knockbackDistance)
{
	float length = sqrt(knockbackDirection.x * knockbackDirection.x + knockbackDirection.y * knockbackDirection.y);

	if (length != 0)
	{
		knockbackDirection.x /= length;
		knockbackDirection.y /= length;
	}

	body.move(knockbackDirection * knockbackDistance);
}

void Enemy::ProjectilesCollideWithPlayerUnits()
{
	for (Characters* unit : GetUnitsWithinRadius())
	{
		for (Projectile* projectile : projectiles)
		{
			// If projectle hits character 
			if (projectile->body.getGlobalBounds().intersects(unit->body.getGlobalBounds()))
			{
				sf::Vector2f knockbackDirection = projectile->CalculateMovementVector();

				unit->TakeDamage(stats.GetDamage());
				unit->ApplyKnockback(knockbackDirection, stats.GetKnockback());

				projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
			}

			// If projectle hits character shield projectile
			if (unit->projectiles.size() > 0)
			{
				for (Projectile* enemyProjectile : unit->projectiles)
				{
					if (enemyProjectile->tag != "shield") { continue; }

					if (projectile->body.getGlobalBounds().intersects(enemyProjectile->body.getGlobalBounds()))
					{
						projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
						unit->projectiles.erase(std::remove(unit->projectiles.begin(), unit->projectiles.end(), enemyProjectile), unit->projectiles.end());
					}
				}
			}

		}
	}
}

void Enemy::ProjectilesCollideWithPlayerBuildings()
{
	for (Buildings* building : GameManager::buildings)
	{
		for (Projectile* projectile : projectiles)
		{
			// If projectle hits character 
			if (projectile->body.getGlobalBounds().intersects(building->body.getGlobalBounds()))
			{
				sf::Vector2f knockbackDirection = projectile->CalculateMovementVector();

				building->TakeDamage(stats.GetDamage());

				projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
			}
		}
	}
}

void Enemy::ChangeStateToDead()
{
	ChangeState(DEAD);
	sf::Color colour = sf::Color::White;
	colour.a = 150;

	if (enemyType == SUCKLER_MALE || enemyType == SUCKLER_FEMALE)
	{
		body.setTexture(Textures::GetInstance().GetTexture("suckler-dead"));
		body.setTextureRect(sf::IntRect{ 0, 0, 144 , 156 });
	}
	else if (enemyType == BIG_SUCKLER)
	{
		body.setTexture(Textures::GetInstance().GetTexture("big-suckler-dead"));
		body.setTextureRect(sf::IntRect{ 0, 0, 218 , 208 });
	}

	GameManager::aliveEnemies.erase(std::remove(GameManager::aliveEnemies.begin(), GameManager::aliveEnemies.end(), this), GameManager::aliveEnemies.end());
	body.setOrigin(body.getTextureRect().width / 2, body.getTextureRect().height / 2);
	body.setColor(colour);
	projectiles.clear();
}

void Enemy::GetRandomItemFromDropTable()
{
	std::vector<std::pair<double, std::string>> itemProbabilities =
	{
		{0.25, "Gold"},
		{0.15, "Oil"},
		{0.10, "Uranium"},
		{0.20, "Suckler Head"},
		{0.15, "Suckler Tentacle"},
		{0.15, "Suckler Spit"},
	};

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0.0, 1.0);

	double randomDrop = dis(gen);
	double cumulativeProbability = 0;

	double totalProbability = 0;

	for (auto& pair : itemProbabilities)
	{
		totalProbability += pair.first;
	}

	for (auto& pair : itemProbabilities)
	{
		cumulativeProbability += pair.first / totalProbability;
		if (randomDrop < cumulativeProbability)
		{
			DropItem(pair.second);
			return;
		}
	}
}



void Enemy::DropItem(std::string& itemName)
{
	Item tempItem = GameManager::itemManager.GetItemByName(itemName);

	int id = tempItem.GetID();
	std::string name = tempItem.GetName();
	int quantity = tempItem.GetQuantity();
	std::string textureName = tempItem.GetTextureName();

	droppedItem = new Item(id, name, quantity, Textures::GetInstance().GetTexture(textureName), textureName);


	/*if (droppedItem == nullptr)
	{
		droppedItem = new Item(tempItem);
	}
	else 
	{
		*droppedItem = tempItem;
	}*/


	int randomQuantity = rand() % 3 + 1;
	droppedItem->IncreaseQuantity(randomQuantity);

	float offsetX = static_cast<float>(rand() % 100 - 50);
	float offsetY = static_cast<float>(rand() % 100 - 50); 

	sf::Vector2f dropPosition = body.getPosition() + sf::Vector2f(offsetX, offsetY);
	itemDropSprite.setTexture(&Textures::GetInstance().GetTexture(droppedItem->GetTextureName()));
	itemDropSprite.setPosition(dropPosition);

	std::cout << droppedItem->GetQuantity() << " " << droppedItem->GetName() << " have dropped \n";

}

void Enemy::UnitsCanCollectItemDrop()
{
	if (droppedItem != nullptr) 
	{
		for (Characters* unit : GameManager::aliveUnits)
		{
			if (unit->body.getGlobalBounds().intersects(itemDropSprite.getGlobalBounds()))
			{
				GameManager::inventory.AddItem(droppedItem->GetName(), droppedItem->GetQuantity());
				isItemCollected = true;
				delete droppedItem;
				return;
			}
		}
	}
}

void Enemy::MakeWalkingTrail()
{
	int randomNumberOffset = 15;
	int loopAmount = 3;
	sf::Vector2f randPosOffset;
	for (int i = 0; i < loopAmount; i++)
	{
		sf::Vector2f randPosOffset; 
		randPosOffset.x = static_cast<float>(Global::GetRandomNumber(-randomNumberOffset, randomNumberOffset));
		randPosOffset.y = static_cast<float>(Global::GetRandomNumber(-randomNumberOffset, randomNumberOffset));

		particleSystem.AddSpriteParticle(body.getPosition() + randPosOffset, (velocity * -1.0f) * 0.5f, sf::Color::White, Textures::GetInstance().GetTexture("suckler-trail"), 50, 0.2, 7);
	}
	walkingTrailTimer.restart();
}

void Enemy::DeleteEnemy()
{
	target = nullptr;
	projectiles.clear();
	toBeDeleted = true;
	GameManager::enemies.erase(std::remove(GameManager::enemies.begin(), GameManager::enemies.end(), this), GameManager::enemies.end());
	GameManager::aliveEnemies.erase(std::remove(GameManager::aliveEnemies.begin(), GameManager::aliveEnemies.end(), this), GameManager::aliveEnemies.end());
}

