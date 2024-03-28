#include "Warrior.h"
#include "Globals.h"

Warrior::Warrior()
{
	textureRect = { 0, 0, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("warrior"), body, textureRect);
	characterType = WARRIOR;
}

void Warrior::Update()
{
	Characters::Update();
	CheckAnimationState();
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, body, amountOfSprites);

	if (GetSelected())
	{
		SetCurrentState(IDLE);
	}

	if (GetCurrentState(ATTACKING) && reloadTimer.getElapsedTime().asSeconds() > reloadDelay)
	{
		Attack(closestEnemy);
	}
}

void Warrior::Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites)
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

void Warrior::AnimateWarrior()
{
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, body, amountOfSprites);
}

void Warrior::CheckAnimationState()
{
	if (GetCurrentState(IDLE) && !isMovingIntoFormation)
	{
		currentFrameY = 0;
	}
	else if (GetCurrentState(MOVING) || isMovingIntoFormation)
	{
		currentFrameY = 2;
	}
	else if (GetCurrentState(ATTACKING))
	{
		currentFrameY = 3;
	}
	else if (GetCurrentState(DEAD))
	{
		currentFrameY = 4;
	}

	if (GetCurrentState(ATTACKING))
	{
		animationSpeed = 0.08;
	}
	else
	{
		animationSpeed = 0.2;
	}
}

// Bug with warrior shooting to the right?
// Fix reload delay
void Warrior::Attack(Enemy* target)
{
	if (m_frameNo == amountOfSprites - 1)
	{
		if (body.getScale().x > 1)
		{
			projectiles.push_back(factory.CreateBasicProjectile(Textures::GetInstance().GetTexture("flaming-sword"),
				{ body.getPosition().x + 30, body.getPosition().y }, target->body.getPosition(), stats.GetAttackSpeed(), detectionRadius + 10, 0.3));
		}
		else
		{
			projectiles.push_back(factory.CreateBasicProjectile(Textures::GetInstance().GetTexture("flaming-sword"),
				{ body.getPosition().x - 30 , body.getPosition().y }, target->body.getPosition(), stats.GetAttackSpeed(), detectionRadius + 10, -0.3));
		}
		reloadTimer.restart();
	}
}

sf::Sprite& Warrior::GetSprite()
{
	return body;
}

sf::Vector2f& Warrior::GetPos()
{
	sf::Vector2f pos = body.getPosition();
	return pos;
}
