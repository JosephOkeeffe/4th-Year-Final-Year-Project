#include "Characters.h"
#include "Globals.h"
#include <iostream>

void Characters::Init(sf::Texture& _texture, sf::Sprite& sprite, sf::IntRect& textureSize)
{
	srand(time(nullptr));

	sprite.setTexture(texture);
	sprite.setTextureRect(textureSize);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setScale(2, 2);

	textureRect = textureSize;
	body.setTexture(_texture);

	InitDetectionCircle(detectionRadius);
}

// TO DO
// Then enemies attacking player
// Then enemies moving
// Formations - changed radius to the centre of the whole formation, get the distance, get the average and make a new formation radius
void Characters::Update()
{
	if (GetCurrentState(MOVING) && !path.empty())
	{
		MoveCharacter();
	}

	if (isMovingIntoFormation && isPartOfFormation)
	{
		MoveIntoFormation();
	}

	ChangeSelectedColour();
	UpdateDetectionCircle();

	if (!isWorking)
	{
		if (GetSelected())
		{
			sf::Vector2f randomVelocity((rand() % 5 - 2) * 2.0f, (rand() % 5 - 2) * 2.0f);
			particleSystem.addParticle(tileDetectionCircle.getPosition(), randomVelocity, sf::Color::Yellow, 3, 1);
			particleSystem.Update();

			int x = body.getPosition().x / Global::CELL_SIZE;
			int y = body.getPosition().y / Global::CELL_SIZE;

			startTile = &GameManager::tiles[x][y];
		}
		else
		{
			if (!GetCurrentState(MOVING))
			{
				particleSystem.clearParticles();
			}
		}
	}

	if (GameManager::aliveEnemies.size() < 1)
	{
		if (!GetCurrentState(MOVING))
		{
			SetCurrentState(IDLE);
			detectionCircle.setFillColor(sf::Color(255, 255, 255, 100));
		}
	}
	else
	{

		FindClosestEnemy();
		StartAttackingClosestEnemy();
		DetectProjectileCollision();
	}

	for (Projectile* projectile : projectiles)
	{
		projectile->Update();

		if (projectile->IsOutOfRange(projectile->body.getPosition(), projectile->startPosition))
		{
			projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
		}
	}
}

void Characters::MouseRelease()
{
	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
	sf::Vector2i cellPos = Global::GetCurrentCell(*GameManager::GetWindow(), *GameManager::GetView());
	if (isSelected)
	{
		SetCurrentState(MOVING);
		goalTile = &GameManager::tiles[cellPos.x][cellPos.y];

		if (characterType == ARCHER || characterType == WARRIOR)
		{
			path = GameManager::FindPath(startTile, goalTile, false);
		}
		else
		{
			path = GameManager::FindPath(startTile, goalTile, true);
		}
	}


	
	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		SelectCharacter();
	}
}

void Characters::Draw()
{
	for (Projectile* projectile : projectiles)
	{
		projectile->Draw(*GameManager::GetWindow());
	}

	particleSystem.draw(*GameManager::GetWindow());
	GameManager::GetWindow()->draw(detectionCircle);
	GameManager::GetWindow()->draw(body);


}

void Characters::InitDetectionCircle(int radius)
{
	detectionCircle.setRadius(radius);
	detectionCircle.setOrigin(radius, radius);
	detectionCircle.setPosition(body.getPosition());
	detectionCircle.setFillColor(sf::Color::Transparent);
	detectionCircle.setOutlineThickness(1);
	detectionCircle.setOutlineColor(sf::Color(255, 0, 0, 255));

	tileDetectionCircle.setRadius(tileDetectionRadius);
	tileDetectionCircle.setOrigin(tileDetectionRadius, tileDetectionRadius);
	tileDetectionCircle.setFillColor(sf::Color(255, 0, 0, 50));
}

void Characters::UpdateDetectionCircle()
{
	detectionCircle.setPosition(body.getPosition());
	tileDetectionCircle.setPosition(body.getPosition().x, body.getPosition().y + 30);
}

void Characters::MoveCharacter()
{
	float length = 0;
	DeselectCharacter();
	particleSystem.addParticle(body.getPosition(), { 0,0 }, sf::Color::Black, 3, 2);
	particleSystem.Update();

	targetPosition = path.front()->tile.getPosition();
	targetPosition.x += pathFindingXOffset;
	targetPosition.y += pathFindingYOffset;

	direction = targetPosition - body.getPosition();
	length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length != 0)
	{
		direction /= length;
	}

	FlipSpriteWithDirection(direction, body);

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
			currentState = IDLE;
		}
	}

}

void Characters::MoveIntoFormation()
{
	sf::Vector2f direction = targetPosition - body.getPosition();
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance > 1.0f)
	{
		direction /= distance;

		velocity = direction * currentMoveSpeed;
		body.move(velocity);
		FlipSpriteWithDirection(direction, body);
	}
	else
	{
		body.setPosition(targetPosition);
		isMovingIntoFormation = false;		
	}
}

void Characters::SelectCharacter()
{
	if (HUD::currentState == HUD::NONE)
	{
		isSelected = true;
	}
}

void Characters::DeselectCharacter()
{
	isSelected = false;
}

void Characters::Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites)
{
	int playerAnimation = m_frameNo;
	
	m_frameValue += animationSpeed;
	m_frameNo = static_cast<int>(m_frameValue);
	m_frameNo = m_frameNo % amountOfSprites;
	

	if (playerAnimation != m_frameNo)
	{
		body.setTextureRect(sf::IntRect(m_frameNo * startX, startY, spriteWidth, spriteHeight));
	}
}

void Characters::ChangeSpeedDependingOnTiles()
{
	sf::Vector2i tempPos;

	tempPos.x = static_cast<int>(tileDetectionCircle.getPosition().x / Global::CELL_SIZE);
	tempPos.y = static_cast<int>(tileDetectionCircle.getPosition().y / Global::CELL_SIZE);

	if (GameManager::tiles[tempPos.x][tempPos.y].GetTileType() == NONE)
	{
		currentMoveSpeed = defaultMoveSpeed;
	}
	else if (GameManager::tiles[tempPos.x][tempPos.y].GetTileType() == PATH)
	{
		currentMoveSpeed = defaultMoveSpeed * 1.5;
	}
}

bool Characters::GetSelected()
{
	return isSelected;
}

void Characters::ChangeSelectedColour()
{
	if (GetSelected())
	{
		body.setColor(sf::Color(200, 50, 50));
	}
	else
	{
		body.setColor(sf::Color::White);
	}
}

bool Characters::IsEnemyInAttackRadius(sf::Sprite& target)
{
	float dx = body.getPosition().x - target.getPosition().x;
	float dy = body.getPosition().y - target.getPosition().y;
	float angle = atan2(dy, dx) * 180 / Global::PI;

	float distance = std::hypot(dx, dy);

	if (distance <= detectionRadius)
	{
		detectionCircle.setFillColor(sf::Color(255, 0, 0, 100)); 
		return true;
	}
	else
	{
		detectionCircle.setFillColor(sf::Color(255, 255, 255, 100));
		return false;
	}
}

void Characters::FlipSpriteWithDirection(sf::Vector2f& direction, sf::Sprite& sprite)
{

	if (direction.x < 0)
	{
		sprite.setScale(-std::abs(sprite.getScale().x), sprite.getScale().y);
	}
	else
	{
		sprite.setScale(std::abs(sprite.getScale().x), sprite.getScale().y);
	}
}

void Characters::FlipSprite()
{
	sf::Vector2f currentScale = body.getScale();

	body.setScale(currentScale.x * -1, currentScale.y);
}

bool Characters::GetCurrentState(State stateToCheck)
{
	return currentState == stateToCheck;
}

void Characters::SetCurrentState(State stateToChange)
{
	currentState = stateToChange;
}

void Characters::FindClosestEnemy()
{
	closestEnemy = nullptr;
	closestEnemyDistance = INT_MAX; 

	bool anyEnemyInRadius = false;
	for (Enemy* enemy : GameManager::aliveEnemies)
	{
		if (IsEnemyInAttackRadius(enemy->body))
		{
			float distance = Global::Distance(enemy->body.getPosition(), body.getPosition());
			anyEnemyInRadius = true;

			if (closestEnemy != nullptr && closestEnemy->GetCurrentState(closestEnemy->DEAD))
			{
				closestEnemy = nullptr;
			}

			if (distance < closestEnemyDistance || closestEnemy == nullptr)
			{
				closestEnemyDistance = distance;
				closestEnemy = enemy;
			}
		}
		else if (!GetCurrentState(MOVING))
		{
			SetCurrentState(IDLE);
		}
	}

	if (!anyEnemyInRadius)
	{
		closestEnemy = nullptr;
		closestEnemyDistance = INT_MAX;
	}
}


void Characters::StartAttackingClosestEnemy()
{
	if (!GetSelected() && !GetCurrentState(MOVING))
	{
		if (closestEnemy == nullptr || !IsEnemyInAttackRadius(closestEnemy->body)) { return; }

		SetCurrentState(ATTACKING);

		if (closestEnemy->body.getPosition().x < body.getPosition().x && body.getScale().x > 1 ||
			closestEnemy->body.getPosition().x > body.getPosition().x && body.getScale().x < 1)
		{
			FlipSprite();
		}
	}
}

void Characters::DetectProjectileCollision()
{
	for (Enemy* enemy : GameManager::aliveEnemies)
	{
		if (!IsEnemyInAttackRadius(enemy->body))
		{
			continue;
		}

		for (Projectile* projectile : projectiles)
		{
			// If projectle hits enemy 
			if (projectile->body.getGlobalBounds().intersects(enemy->body.getGlobalBounds()))
			{
				sf::Vector2f knockbackDirection = projectile->CalculateMovementVector();

				enemy->TakeDamage(stats.GetDamage());
				enemy->ApplyKnockback(knockbackDirection, stats.GetKnockback());

				projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
			}

			// If projectle hits enemy shield projectile
			if (enemy->projectiles.size() > 0)
			{
				for (Projectile* enemyProjectile : enemy->projectiles)
				{
					if (enemyProjectile->tag != "shield") { continue; }

					if (projectile->body.getGlobalBounds().intersects(enemyProjectile->body.getGlobalBounds()))
					{
						projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
						enemy->projectiles.erase(std::remove(enemy->projectiles.begin(), enemy->projectiles.end(), enemyProjectile), enemy->projectiles.end());
					}
				}
			}

		}
	}
}

void Characters::SetPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}






