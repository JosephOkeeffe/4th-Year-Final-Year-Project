#include "Archer.h"
#include "Globals.h"

Archer::Archer()
{
	textureRect = { 0,0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("archer"), body, textureRect);
	animationSpeed = 0.04;
	body.setScale(1.5, 1.5);
	characterType = ARCHER;

	blast.setRadius(10);
	blast.setTexture(&Textures::GetInstance().GetTexture("blast"));
	
}

void Archer::Update()
{
	// IF DEAD
	if (GetCurrentState(DEAD) && m_frameNo != amountOfSprites - 1)
	{
		
		Animate(currentFrameX, currentFrameY, textureWidth, textureHeight, body, amountOfSprites);
		
	}

	if (!GetCurrentState(DEAD))
	{
		Characters::Update();
		CheckAnimationState();
		if (!GetCurrentState(ATTACKING))
		{
			Animate(currentFrameX, currentFrameY, textureWidth, textureHeight, body, amountOfSprites);
		}

		if (GetSelected())
		{
			SetCurrentState(IDLE);
		}

		if (GetCurrentState(ATTACKING))
		{
			if (!isChargingUp)
			{
				blast.setRadius(0);
				isChargingUp = true;
				reloadTimer.restart();
				SoundManager::GetInstance().PlaySound("kamehameha", 20, false);
			}
			else
			{
				sf::Vector2f randomVelocity((rand() % 5 - 2) * 2.0f, (rand() % 5 - 2) * 2.0f);
				particleSystem.addParticle(blast.getPosition(), Global::GetRandomVector(), sf::Color::Blue, 3, 1);
				float radius = blast.getRadius();
				radius += 0.1;
				blast.setRadius(radius);
				blast.rotate(radius);
				blast.setOrigin(blast.getRadius(), blast.getRadius());
			}
			

			if (body.getScale().x < 0)
			{
				blast.setPosition(body.getPosition().x - 30, body.getPosition().y);
			}
			else
			{
				blast.setPosition(body.getPosition().x + 30, body.getPosition().y);
			}
		}
		else
		{
			SoundManager::GetInstance().StopSound("kamehameha");
			blast.setPosition(-5000, -5000);
			blast.setRadius(10);
			reloadTimer.restart();
			isChargingUp = false;
		}

		if (canShoot)
		{
			if(closestEnemy != nullptr)
			{
				Attack(closestEnemy->body.getPosition());
			}
			else
			{
				Attack(closestEnemyBase);
			}
		}

		if (reloadTimer.getElapsedTime().asSeconds() > reloadDelay)
		{
			canShoot = true;
			reloadTimer.restart();
		}
	}
}

void Archer::Draw()
{
	Characters::Draw();
	if(GetCurrentState(ATTACKING))
	{
		GameManager::GetWindow()->draw(blast);
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
		body.setTextureRect(sf::IntRect(m_frameNo * startX, startY, spriteWidth, spriteHeight));
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
		body.setTextureRect(sf::IntRect(0, 160, 35, 47));
	}
	else if (GetCurrentState(DEAD))
	{
		amountOfSprites = 6;
		currentFrameX = 50;
		currentFrameY = 102;
		textureHeight = 52;
		textureWidth = 50;
	}
}

void Archer::Attack(sf::Vector2f target)
{

	if (body.getScale().x > 1)
	{
		projectiles.push_back(factory.CreateHomingProjectile(Textures::GetInstance().GetTexture("blast"), Textures::GetInstance().GetTexture("blast-trail"), 
			0.3, { body.getPosition().x + 30, body.getPosition().y - 10 }, target, 1, detectionRadius + 10, 1.5));
	}
	else
	{
		projectiles.push_back(factory.CreateHomingProjectile(Textures::GetInstance().GetTexture("blast"), Textures::GetInstance().GetTexture("blast-trail"), 
			0.3, { body.getPosition().x - 30 , body.getPosition().y - 10 }, target, stats.GetAttackSpeed(), detectionRadius + 10, -1.5));
	}

	blast.setRadius(0);
	canShoot = false;
	isChargingUp = false;
	reloadTimer.restart();
	
}

sf::Sprite& Archer::GetSprite()
{
	return body;
}
