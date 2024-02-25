#include "Enemy.h"

Enemy::Enemy()
{
	body.setTexture(Textures::GetInstance().GetTexture("enemy"));

	body.setTextureRect(textureRect);
	body.setOrigin(body.getTextureRect().width / 2, body.getTextureRect().height / 2);
	body.setScale(1.2, 1.2);

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
	CheckState();
	Animate();

	for (int row = 0; row < Global::ROWS_COLUMNS; row++)
	{
		for (int col = 0; col < Global::ROWS_COLUMNS; col++)
		{
			if (GameManager::tiles[row][col].GetTileType() != TileType::OBSTACLE)
			{

			}
		}
	}

	bool anyCharacterWithinRadius = false;

	for (Characters* unit : GameManager::units)
	{
		if (IsCharacterWithinRadius(unit->body))
		{
			anyCharacterWithinRadius = true;
		}
	}

	if (anyCharacterWithinRadius)
	{
		state = ATTACKING;
		detectionCircle.setFillColor(sf::Color(255, 0, 0, 100)); 
	}
	else
	{
		state = IDLE; 
		detectionCircle.setFillColor(sf::Color(255, 255, 255, 100));
	}
}

void Enemy::Animate()
{
	int playerAnimation = m_frameNo;

	if (state == DEAD && m_frameNo == 5)
	{}
	else
	{
		m_frameValue += animationSpeed;
		m_frameNo = static_cast<int>(m_frameValue);
		m_frameNo = m_frameNo % amountOfSprites;
	}

	if (playerAnimation != m_frameNo)
	{
		body.setTextureRect(sf::IntRect(m_frameNo * currentFrameX, currentFrameY, textureWidth, textureHeight));
	}
}

bool Enemy::IsCharacterWithinRadius(const sf::Sprite& target)
{
	float dx = body.getPosition().x - target.getPosition().x;
	float dy = body.getPosition().y - target.getPosition().y;
	float distance = std::hypot(dx, dy);

	return (distance <= detectionRadius);
}

void Enemy::SetPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void Enemy::CheckState()
{
	switch (state)
	{
	case Enemy::IDLE:
		currentFrameX = 36;
		currentFrameY = 0;
		textureWidth = 36;
		textureHeight = 68;
		amountOfSprites = 7;
		break;
	case Enemy::WALKING:
		currentFrameX = 59;
		currentFrameY = 69;
		textureWidth = 59;
		textureHeight = 72;
		amountOfSprites = 4;
		animationSpeed = 0.03;
		break;
	case Enemy::THINKING:
		currentFrameX = 27;
		currentFrameY = 144;
		textureWidth = 27;
		textureHeight = 68;
		amountOfSprites = 5;
		animationSpeed = 0.05;
		break;
	case Enemy::ATTACKING:
		currentFrameX = 68;
		currentFrameY = 214;
		textureWidth = 68;
		textureHeight = 89;
		amountOfSprites = 4;
		animationSpeed = 0.05;
		break;
	case Enemy::DEAD:
		currentFrameX = 50;
		currentFrameY = 304;
		textureWidth = 50;
		textureHeight = 68;
		amountOfSprites = 6;
		animationSpeed = 0.05;
		break;
	default:
		break;
	}
}

