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
}

void Archer::Draw()
{
	Characters::Draw();

	if(GetSelected())
	{
		stats.DisplayAllStats(*GameManager::GetWindow(), { body.getPosition().x, body.getPosition().y - body.getLocalBounds().height});
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
			projectiles.push_back(factory.CreateHomingProjectile(Textures::GetInstance().GetTexture("blast"), Textures::GetInstance().GetTexture("blast-trail"), 
				0.3, { body.getPosition().x + 30, body.getPosition().y }, target->body.getPosition(), 1, detectionRadius + 10, 1));
		}
		else
		{
			projectiles.push_back(factory.CreateHomingProjectile(Textures::GetInstance().GetTexture("blast"), Textures::GetInstance().GetTexture("blast-trail"), 
				0.3, { body.getPosition().x - 30 , body.getPosition().y }, target->body.getPosition(), stats.GetAttackSpeed(), detectionRadius + 10, -1));
		}
		reloadTimer.restart();
	}
}

sf::Sprite& Archer::GetSprite()
{
	return body;
}
