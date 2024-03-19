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
	AnimateArcher();

	if (GetSelected())
	{
		SetCurrentState(IDLE);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		Attack();
		
		
	}

	for (Projectile& projectile : projectiles)
	{
		projectile.Update();

		if (projectile.IsOutOfRange(100))
		{
			projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
		}
	}


}

void Archer::Draw()
{
	for (Projectile& projectile : projectiles)
	{
		projectile.Draw(*GameManager::GetWindow());
	}
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

	if (GetCurrentState(ATTACKING) && m_frameNo == amountOfSprites - 1)
	{
		Projectile projectile(Textures::GetInstance().GetTexture("blast"), body.getPosition(), { 200,200 }, 1);

		projectiles.push_back(projectile);
	}
	
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


void Archer::AnimateArcher()
{
	Animate(currentFrameX, currentFrameY, textureWidth, textureHeight, body, amountOfSprites);
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


}

void Archer::Attack()
{
	m_frameNo = 0;
	SetCurrentState(ATTACKING);
}

sf::Sprite& Archer::GetSprite()
{
	return body;
}
