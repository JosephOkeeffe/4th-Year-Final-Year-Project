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
	GameManager::GetWindow()->draw(detectionCircle);
}

void Enemy::Update()
{
	detectionCircle.setPosition(body.getPosition());

	CheckIfAnythingIsWithinRadius();
	UpdateStates();

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





