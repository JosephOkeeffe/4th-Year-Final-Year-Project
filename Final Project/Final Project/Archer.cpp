#include "Archer.h"
#include "Globals.h"

Archer::Archer()
{
	textureRect = { 0,0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("archer"), body, textureRect);
	animationSpeed = 0.04;
	body.setScale(1.5, 1.5);
	characterType = ARCHER;
}

void Archer::Update()
{
	Characters::Update();
	CheckAnimationState();
	Animate(currentFrameX, currentFrameY, textureWidth, textureHeight, body, amountOfSprites);

	if (GetSelected())
	{
		SetCurrentState(IDLE);
	}

	if (GetCurrentState(ATTACKING) &&  reloadTimer.getElapsedTime().asSeconds() > reloadDelay)
	{
		Attack(closestEnemy);
	}

	//if (GameManager::aliveEnemies.size() < 1)
	//{
	//	if (!GetCurrentState(MOVING))
	//	{
	//		SetCurrentState(IDLE);
	//		detectionCircle.setFillColor(sf::Color(255, 255, 255, 100));
	//	}
	//}
	//else
	//{
	//	// Picks closest enemy
	//	bool anyEnemyInRadius = false;
	//	for (Enemy* enemy : GameManager::aliveEnemies)
	//	{
	//		if (IsEnemyInAttackRadius(enemy->body))
	//		{
	//			float distance = Global::Distance(enemy->body.getPosition(), body.getPosition());
	//			anyEnemyInRadius = true;

	//			if (closestEnemy != nullptr && closestEnemy->GetCurrentState(closestEnemy->DEAD))
	//			{
	//				closestEnemy = nullptr;
	//			}

	//			if (distance < closestEnemyDistance || closestEnemy == nullptr)
	//			{
	//				closestEnemyDistance = distance;
	//				closestEnemy = enemy;
	//			}
	//		}
	//		else if (!GetCurrentState(MOVING))
	//		{
	//			SetCurrentState(IDLE);      
	//		}
	//	}

	//	if (!anyEnemyInRadius)
	//	{
	//		closestEnemy = nullptr;
	//	}
	//	//  turnn them red
	//	// Then enemies attacking player
	//	// Then enemies moving

	//	if (!GetSelected() && !GetCurrentState(MOVING))
	//	{
	//		if (closestEnemy == nullptr || !IsEnemyInAttackRadius(closestEnemy->body)) 
	//		{ 
	//			return; 
	//		}
	//		SetCurrentState(ATTACKING);

	//		if (closestEnemy->body.getPosition().x < body.getPosition().x && body.getScale().x > 1)
	//		{
	//			FlipSprite();
	//		}
	//		else if (closestEnemy->body.getPosition().x > body.getPosition().x && body.getScale().x < 1)
	//		{
	//			FlipSprite();
	//		}

	//		if (reloadTimer.getElapsedTime().asSeconds() > reloadDelay)
	//		{
	//			Attack(closestEnemy);
	//		}
	//	}


	//	for (Enemy* enemy : GameManager::aliveEnemies)
	//	{
	//		if (!IsEnemyInAttackRadius(enemy->body))
	//		{
	//			continue;
	//		}

	//		for (Projectile* projectile : projectiles)
	//		{
	//			if (projectile->body.getGlobalBounds().intersects(enemy->body.getGlobalBounds()))
	//			{
	//				sf::Vector2f knockbackDirection = projectile->CalculateMovementVector();

	//				enemy->TakeDamage(stats.GetDamage());
	//				enemy->ApplyKnockback(knockbackDirection, stats.GetKnockback());

	//				projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
	//			}

	//			// If projectle hits enemy projectile
	//			if (enemy->projectiles.size() > 0)
	//			{
	//				for (Projectile* enemyProjectile : enemy->projectiles)
	//				{
	//					if (projectile->body.getGlobalBounds().intersects(enemyProjectile->body.getGlobalBounds()))
	//					{
	//						projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
	//						enemy->projectiles.erase(std::remove(enemy->projectiles.begin(), enemy->projectiles.end(), enemyProjectile), enemy->projectiles.end());
	//					}
	//				}
	//			}

	//		}
	//	}
	//}

	//for (Projectile* projectile : projectiles)
	//{
	//	projectile->Update();

	//	if (projectile->IsOutOfRange(projectile->body.getPosition(), projectile->startPosition))
	//	{
	//		projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
	//	}
	//}
}

void Archer::Draw()
{
	Characters::Draw();

	if(GetSelected())
	{
		stats.DisplayStats(*GameManager::GetWindow(), { body.getPosition().x, body.getPosition().y - body.getLocalBounds().height});
	}
}

void Archer::Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites)
{
	int playerAnimation = m_frameNo;
	m_frameValue += animationSpeed;
	m_frameNo = static_cast<int>(m_frameValue);
	m_frameNo = m_frameNo % amountOfSprites;
	
	if (playerAnimation != m_frameNo)
	{
		if (GetCurrentState(ATTACKING) && m_frameNo == amountOfSprites - 1)
		{
			body.setTextureRect(sf::IntRect(m_frameNo * startX, startY, spriteWidth + 56, spriteHeight));
		}
		else
		{
			body.setTextureRect(sf::IntRect(m_frameNo * startX, startY, spriteWidth, spriteHeight));
		}
		
	}
}

void Archer::CheckAnimationState()
{

	if (GetCurrentState(IDLE) && !isMovingIntoFormation)
	{
		amountOfSprites = 5;
		currentFrameX = 35;
		currentFrameY = 1;
		textureHeight = 50;
		textureWidth = 35;
	}
	else if (GetCurrentState(MOVING) || isMovingIntoFormation)
	{
		amountOfSprites = 2;
		currentFrameX = 35;
		currentFrameY = 51;
		textureHeight = 52;
		textureWidth = 35;
	}
	else if (GetCurrentState(ATTACKING))
	{
		amountOfSprites = 3; 
		currentFrameX = 38;
		currentFrameY = 160;
		textureWidth = 38;
	}
	else if (GetCurrentState(DEAD))
	{
		currentFrameY = 4;
	}

	if (GetCurrentState(ATTACKING))
	{
		animationSpeed = 0.01;
	}
	else
	{
		animationSpeed = 0.04;
	}
}

void Archer::Attack(Enemy* target)
{
	if (m_frameNo == amountOfSprites - 1)
	{
		if (body.getScale().x > 1)
		{
			projectiles.push_back(factory.CreateHomingProjectile(Textures::GetInstance().GetTexture("blast"), { body.getPosition().x + 30, body.getPosition().y }, target->body.getPosition(), 1, detectionRadius + 10, 1));
		}
		else
		{
			projectiles.push_back(factory.CreateHomingProjectile(Textures::GetInstance().GetTexture("blast"), { body.getPosition().x - 30 , body.getPosition().y }, target->body.getPosition(), stats.GetAttackSpeed(), detectionRadius + 10, -1));
		}
		reloadTimer.restart();
	}
}

sf::Sprite& Archer::GetSprite()
{
	return body;
}
