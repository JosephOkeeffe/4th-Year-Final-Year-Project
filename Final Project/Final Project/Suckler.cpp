#include "Suckler.h"
Suckler::Suckler(int _id)
{
	srand(time(nullptr));

	id = _id;

	if (id % 2 == 0)
	{
		Init(Textures::GetInstance().GetTexture("suckler"));
		enemyType = SUCKLER_MALE;
	}
	else
	{
		Init(Textures::GetInstance().GetTexture("suckler2"));
		enemyType = SUCKLER_FEMALE;
	}

	body.setScale(0.4, 0.4);
	shieldTimer.restart();
	
}

void Suckler::Update()
{
	if (stats.GetHealth() <= 0 && !GetCurrentState(DEAD))
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

	if (!GetCurrentState(DEAD))
	{
		Enemy::Update();

		if (hasMerged && !mergeComplete)
		{
			Merge();
		}

		if (enemyType == SUCKLER_FEMALE && enemyType != BIG_SUCKLER)
		{
			if (target != nullptr && !target->hasMerged)
			{
				MoveTowardsMergingTarget();
			}

		}

		if (shieldTimer.getElapsedTime().asSeconds() > shieldFireRate)
		{
			shieldTimer.restart();
			if (rand() % chanceToSpawnShield == 0)
			{
				ShootShield();
			}
		}

		for (Projectile* projectile : projectiles)
		{
			projectile->centrePosition = { body.getPosition().x - 10, body.getPosition().y - 10 };
			projectile->Update();

			if (projectile->IsOutOfRange(projectile->body.getPosition(), projectile->startPosition))
			{
				projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
			}
		}
	}
}

void Suckler::Merge()
{
	mergeComplete = true;
	enemyType = BIG_SUCKLER;
	body.setTexture(Textures::GetInstance().GetTexture("big-suckler"));
	body.setTextureRect(sf::IntRect{ 0, 0, 218 , 208 });
	body.setOrigin(body.getTextureRect().width / 2, body.getTextureRect().height / 2);
	projectiles.clear();
}

void Suckler::MoveTowardsMergingTarget()
{
	sf::Vector2f direction = targetPos - body.getPosition();
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (magnitude != 0)
	{
		direction /= magnitude;
	}

	float movementSpeed = 0.2f;
	body.move(direction * movementSpeed);

	float rotationSpeed = 1.0f;
	float rotationAngle = 1.0f * rotationSpeed;
	body.rotate(rotationAngle);
}

void Suckler::ShootSpit()
{
	sf::Vector2f targetPos = { 600, 600 };
	int offset = 100;

	int randomOffsetX = rand() % (2 * offset + 1) - offset;
	int randomOffsetY = rand() % (2 * offset + 1) - offset;

	targetPos.x += randomOffsetX;
	targetPos.y += randomOffsetY;

	projectiles.push_back(factory.CreateBasicProjectile(Textures::GetInstance().GetTexture("spit"), body.getPosition(), targetPos, 1, 500, 0.5));
}

void Suckler::ShootShield()
{
	if (enemyType == BIG_SUCKLER)
	{
		projectiles.push_back(factory.CreateShieldProjectile(Textures::GetInstance().GetTexture("shield"), { body.getPosition().x - 10, body.getPosition().y - 10 }, 1, 0.2, 75));
	}
	else
	{
		projectiles.push_back(factory.CreateShieldProjectile(Textures::GetInstance().GetTexture("shield"), { body.getPosition().x - 10, body.getPosition().y - 10 }, 1, 0.2, 50));
	}
}
