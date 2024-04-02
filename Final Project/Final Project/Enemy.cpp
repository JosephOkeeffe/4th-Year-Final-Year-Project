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

	int x = body.getPosition().x / Global::CELL_SIZE;
	int y = body.getPosition().y / Global::CELL_SIZE;

	wanderTimer.restart();
}

void Enemy::Draw()
{
	GameManager::GetWindow()->draw(body);

	if (!GetCurrentState(DEAD))
	{
		stats.DisplayHealthBar(*GameManager::GetWindow(), { body.getPosition().x, body.getPosition().y - 50 });
		particleSystem.draw(*GameManager::GetWindow());
		GameManager::GetWindow()->draw(enemyDetectionCircle);
		GameManager::GetWindow()->draw(wanderCircle);

		
		  
		for (Projectile* projectile : projectiles)
		{
			projectile->Draw(*GameManager::GetWindow());
		}
	}
}

// TO DO
// Miner and Oil Man done...hazmat man NOT DONE- Fix up and copy from others, make him die
// Enemy has a few more radius'
// If female - Search for male in certain radius - If found, move in that direction
// Search for good guys - If found, move in that direction
// Enemies can destroy buildings
// Do something with resocures
// Level up - Enemeis spawn at certain levels, players can get xp when they kill bad guys
// Invenotry maybe
// End game screen 
// Once enemy is there, wait and observe in smaller radius
// If nothing of interest is there, move to another random point in radius
// Make better UI that shows things all the time , resources, buildings etc
 
void Enemy::Update()
{

	if (stats.GetCurrentHealth() <= 0 && !GetCurrentState(DEAD))
	{
		ChangeStateToDead();
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

		if(GetCurrentState(IDLE) && wanderTimer.getElapsedTime().asSeconds() > 10)
		{
			StartWandering();
		}

		ProjectilesCollideWithPlayerUnits();
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
		}
	}
}

void Enemy::StartWandering()
{
	ChangeState(MOVING);
	int tilesInRadius = wanderRadius / Global::CELL_SIZE;
	sf::Vector2i cellPos = Global::ConvertPositionToCell(body.getPosition());
	startTile = &GameManager::tiles[cellPos.x][cellPos.y];
	int randX = randX = (rand() % (2 * tilesInRadius + 1)) - tilesInRadius;
	int randY = randY = (rand() % (2 * tilesInRadius + 1)) - tilesInRadius;

	while (cellPos.x + randX < 1 || cellPos.y + randY < 1)
	{
		randX = (rand() % (2 * tilesInRadius + 1)) - tilesInRadius;
		randY = (rand() % (2 * tilesInRadius + 1)) - tilesInRadius;
	}
	cellPos.x += randX;
	cellPos.y += randY;
	std::cout << "X: " << cellPos.x << ", Y: " << cellPos.y << "\n";
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

	for (Characters* unit : GameManager::aliveUnits)
	{
		if (IsCharacterWithinRadius(unit->body))
		{
			anyCharacterWithinRadius = true;
		}
	}

	if (!GetCurrentState(MERGING))
	{
		if (anyCharacterWithinRadius)
		{
			ChangeState(ATTACKING);
		}
		else
		{
			if (!GetCurrentState(MOVING))
			{
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
void Enemy::TakeDamage(int damage)
{
	std::cout << "Current Health: " << stats.GetCurrentHealth() << "\n";
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

