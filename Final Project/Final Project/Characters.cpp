#include "Characters.h"
#include "Globals.h"
#include <iostream>
#include "SoundManager.h"

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

void Characters::Update()
{
	if (!GetCurrentState(DEAD))
	{
		if (GetCurrentState(MOVING) && !path.empty())
		{
			MoveCharacter();
		}

		if (isMovingIntoFormation && isPartOfFormation)
		{
			MoveIntoFormation();
		}

		UpdateDetectionCircle();
		ChangeSpeedDependingOnTiles();
		particleSystem.Update();

		if (characterType == ARCHER || characterType == WARRIOR || characterType == HEALER)
		{
			if (GameManager::aliveEnemies.size() < 1)
			{
				if (!GetCurrentState(MOVING))
				{
					//if (characterType == HEALER && isHealChargingUp)
					//{
						SetCurrentState(IDLE);
					//}
					detectionCircle.setFillColor(sf::Color(255, 255, 255, 100));
				}
			}
			else
			{
				FindClosestEnemy();
				StartAttackingClosestEnemy();
				StartAttackingEnemyBase();
				ProjectilesCollideWithEnemies();
				ProjectilesCollideWithEnemyBase();
			}
		}

		if (!isWorking)
		{
			if (GetSelected())
			{
				sf::Vector2f randomVelocity((rand() % 5 - 2) * 2.0f, (rand() % 5 - 2) * 2.0f);
				particleSystem.addParticle(tileDetectionCircle.getPosition(), randomVelocity, sf::Color::Yellow, 3, 1);

				int x = body.getPosition().x / Global::CELL_SIZE;
				int y = body.getPosition().y / Global::CELL_SIZE;

				startTile = &GameManager::tiles[x][y];
			}
		}

		if (body.getColor() == sf::Color::Red && redTimer.getElapsedTime().asSeconds() > 0.3)
		{
			body.setColor(sf::Color::White);
		}

		UpdateProjectiles();
	}

	if (stats.GetCurrentHealth() <= 0 && !GetCurrentState(DEAD))
	{
		ChangeStateToDead();
	}

	if (closestEnemy == nullptr && !GetCurrentState(ATTACKING))
	{
		projectiles.clear();
	}
}

void Characters::MouseRelease()
{
	sf::Vector2f mousePos = Global::GetWindowMousePos(*GameManager::GetWindow(), *GameManager::GetView());
	sf::Vector2i cellPos = Global::GetCurrentCell(*GameManager::GetWindow(), *GameManager::GetView());
	if (cellPos.x < 0 || cellPos.y < 0) { return; }

	if (isSelected)
	{
		SoundManager::GetInstance().PlaySound("confirm", 50, false);
		SetCurrentState(MOVING);
		goalTile = &GameManager::tiles[cellPos.x][cellPos.y];

		if (characterType == ARCHER || characterType == WARRIOR || characterType == HEALER)
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
	if (GetCurrentState(DEAD))
	{
		GameManager::GetWindow()->draw(body);
	}
	else
	{
		if(!isWorking)
		{
			stats.DisplayHealthBar(*GameManager::GetWindow(), { body.getPosition().x, body.getPosition().y - 50 });
		}

		for (Projectile* projectile : projectiles)
		{
			projectile->Draw(*GameManager::GetWindow());
		}

		particleSystem.draw(*GameManager::GetWindow());
		GameManager::GetWindow()->draw(body);		
	}


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

	if (walkingTrailTimer.getElapsedTime().asSeconds() > 0.3)
	{
		MakeWalkingTrail();
	}

	DeselectCharacter();

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
			SetCurrentState(IDLE);
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
		SoundManager::GetInstance().PlaySound("select", 50, false);
		body.setColor(sf::Color(200, 50, 50));
		isSelected = true;
	}
}

void Characters::DeselectCharacter()
{
	body.setColor(sf::Color::White);
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
			if (characterType == HEALER)
			{
				if(isHealChargingUp)
				{
					SetCurrentState(IDLE);
				}
			}
			else
			{
				SetCurrentState(IDLE);
			}
			
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

void Characters::StartAttackingEnemyBase()
{
	if (!GetSelected() && !GetCurrentState(MOVING))
	{
		for (EnemyBase* enemyBase : GameManager::enemyBases)
		{
			if (IsEnemyInAttackRadius(enemyBase->body) && enemyBase->isOpen && !enemyBase->isDestroyed)
			{
				SetCurrentState(ATTACKING);
				closestEnemyBase = enemyBase->body.getPosition();

				if (enemyBase->body.getPosition().x < body.getPosition().x && body.getScale().x > 1 ||
					enemyBase->body.getPosition().x > body.getPosition().x && body.getScale().x < 1)
				{
					FlipSprite();
				}
			}
		}
	}
}

void Characters::TakeDamage(int damage)
{
	stats.LoseHealth(damage);
	body.setColor(sf::Color::Red);
	redTimer.restart();

	std::vector<std::string> hurtSounds;
	hurtSounds.push_back("hurt1");
	hurtSounds.push_back("hurt2");
	hurtSounds.push_back("hurt3");
	hurtSounds.push_back("hurt4");
	hurtSounds.push_back("hurt5");
	hurtSounds.push_back("hurt6");

	SoundManager::GetInstance().PlayRandomSound(hurtSounds, 70, false);

	for (int i = 0; i < 10; i++)
	{
		particleSystem.AddSpriteParticle(body.getPosition(), Global::GetRandomVector() * 2.0f, sf::Color::White, Textures::GetInstance().GetTexture("blood"), 20, 0.2, 1);
	}
}

void Characters::ApplyKnockback(sf::Vector2f knockbackDirection, float knockbackDistance)
{
	float length = sqrt(knockbackDirection.x * knockbackDirection.x + knockbackDirection.y * knockbackDirection.y);

	if (length != 0)
	{
		knockbackDirection.x /= length;
		knockbackDirection.y /= length;
	}

	body.move(knockbackDirection * knockbackDistance);
}
void Characters::UpdateProjectiles()
{
	for (Projectile* projectile : projectiles)
	{
		projectile->Update();

		if (projectile->IsOutOfRange(projectile->body.getPosition(), projectile->startPosition))
		{
			projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
		}
	}
}
void Characters::ProjectilesCollideWithEnemies()
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

void Characters::ProjectilesCollideWithEnemyBase()
{
	for (EnemyBase* enemyBase : GameManager::enemyBases)
	{
		if (!IsEnemyInAttackRadius(enemyBase->body) || enemyBase->isDestroyed || !enemyBase->isOpen)
		{
			continue;
		}

		for (Projectile* projectile : projectiles)
		{
			// If projectle hits enemy 
			if (projectile->body.getGlobalBounds().intersects(enemyBase->body.getGlobalBounds()))
			{
				sf::Vector2f knockbackDirection = projectile->CalculateMovementVector();

				enemyBase->TakeDamage(stats.GetDamage());
				projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
			}
		}
	}
}

void Characters::MakeWalkingTrail()
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

void Characters::ChangeStateToDead()
{
	SetCurrentState(DEAD);
	sf::Color colour = sf::Color::White;
	colour.a = 150;
	isSelected = false;
	isWorking = false;
	m_frameNo = 0;


	GameManager::aliveUnits.erase(std::remove(GameManager::aliveUnits.begin(), GameManager::aliveUnits.end(), this), GameManager::aliveUnits.end());
	body.setOrigin(body.getTextureRect().width / 2, body.getTextureRect().height / 2);
	body.setColor(colour);
	projectiles.clear();
	particleSystem.clearParticles();
	return;
}

void Characters::SetPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}






