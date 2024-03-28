#include "Enemy.h"

void Enemy::Init(sf::Texture& _texture)
{
	body.setTexture(_texture);
	body.setOrigin(body.getTextureRect().width / 2, body.getTextureRect().height / 2);

	detectionCircle.setRadius(detectionRadius);
	detectionCircle.setOrigin(detectionRadius, detectionRadius);
	detectionCircle.setPosition(body.getPosition());
	detectionCircle.setFillColor(sf::Color(255, 255, 255, 100));
	detectionCircle.setOutlineThickness(1);
	detectionCircle.setOutlineColor(sf::Color(255, 0, 0, 255));
}

void Enemy::Draw()
{
	GameManager::GetWindow()->draw(body);

	if (!GetCurrentState(DEAD))
	{
		GameManager::GetWindow()->draw(detectionCircle);

		particleSystem.draw(*GameManager::GetWindow());

		for (Projectile* projectile : projectiles)
		{
			projectile->Draw(*GameManager::GetWindow());
		}
	}
}

void Enemy::Update()
{
	if (!GetCurrentState(DEAD))
	{
		detectionCircle.setPosition(body.getPosition());
		CheckIfAnythingIsWithinRadius();
		UpdateStates();
		particleSystem.Update();

		if (body.getColor() == sf::Color::Red && redTimer.getElapsedTime().asSeconds() > 0.3)
		{
			body.setColor(sf::Color::White);
		}
	}
}

void Enemy::UpdateStates()
{
	if (state == IDLE)
	{
		detectionCircle.setFillColor(sf::Color(255, 255, 255, 100));
	}
	else if (state == WALKING)
	{

	}
	else if (state == MERGING)
	{
	}
	else if (state == ATTACKING)
	{
		detectionCircle.setFillColor(sf::Color(255, 0, 0, 100));
	}
	else if (state == DEAD)
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

void Enemy::CheckIfAnythingIsWithinRadius()
{
	bool anyCharacterWithinRadius = false;

	for (Characters* unit : GameManager::units)
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
			ChangeState(IDLE);
		}
	}
}

bool Enemy::IsCharacterWithinRadius(sf::Sprite& target)
{
	float dx = body.getPosition().x - target.getPosition().x;
	float dy = body.getPosition().y - target.getPosition().y;
	float distance = std::hypot(dx, dy);

	return (distance <= detectionRadius);
}

void Enemy::TakeDamage(int damage)
{
	stats.LoseHealth(damage);
	body.setColor(sf::Color::Red);
	redTimer.restart();

	for (int i = 0; i < 10; i++)
	{
		particleSystem.AddSpriteParticle(body.getPosition(), Global::GetRandomVector() * 2.0f, sf::Color::White, Textures::GetInstance().GetTexture("blast"), 20, 0.3, 1);
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

void Enemy::DeleteEnemy()
{
	target = nullptr;
	projectiles.clear();
	toBeDeleted = true;
	GameManager::enemies.erase(std::remove(GameManager::enemies.begin(), GameManager::enemies.end(), this), GameManager::enemies.end());
	GameManager::aliveEnemies.erase(std::remove(GameManager::aliveEnemies.begin(), GameManager::aliveEnemies.end(), this), GameManager::aliveEnemies.end());
}
