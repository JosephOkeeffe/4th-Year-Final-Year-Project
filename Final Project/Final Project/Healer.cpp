#include "Healer.h"
#include "Globals.h"

Healer::Healer()
{
	textureRect = { 0,currentFrameY, textureWidth, textureHeight };
	Init(Textures::GetInstance().GetTexture("healer"), body, textureRect);
	animationSpeed = 0.07;
	body.setScale(1.5, 1.5);
	characterType = HEALER;

	healBlast.setRadius(10);
	healBlast.setFillColor(sf::Color(255,255,255, 150));
	healBlast.setTexture(&Textures::GetInstance().GetTexture("heal"));

	detectionRadius = 400;
	InitDetectionCircle(detectionRadius);

}

void Healer::Update()
{
	if (GetCurrentState(DEAD))
	{
		body.setTextureRect(sf::IntRect(0, 227, 50, 52));
	}

	if (!GetCurrentState(DEAD))
	{
		Characters::Update();
		CheckAnimationState();

		if (GetCurrentState(ATTACKING))
		{
			if (m_frameNo == 0)
			{
				isHealChargingUp = true;
				
				Display_Text("Starting!");
			}
			else if (m_frameNo == amountOfSprites - 1)
			{
				
			}
		}
		if ((GetCurrentState(ATTACKING) && m_frameNo == amountOfSprites - 1) && isHealChargingUp && canAnimate && delayBetweenHealsTimer.getElapsedTime().asSeconds() > healDelay)
		{
			isHealChargingUp = false;
			canAnimate = false;
			Heal();
			healTimer.restart();
			delayBetweenHealsTimer.restart();

		}

		if (!canAnimate && healTimer.getElapsedTime().asSeconds() > healDelay)
		{
			canAnimate = true;
			delayBetweenHealsTimer.restart();
			healTimer.restart();
		}

		if (canAnimate)
		{
			Animate(currentFrameX, currentFrameY, textureWidth, textureHeight, body, amountOfSprites);
		}

		if (GetSelected())
		{
			canAnimate = true;
			SetCurrentState(IDLE);
		}

		if (GetCurrentState(ATTACKING))
		{
			if (isHealChargingUp)
			{
				float radius = healBlast.getRadius();
				float rotation = 0;
				radius += 0.8;
				rotation += 0.2;
				healBlast.setRadius(radius);
				healBlast.rotate(rotation);
				healBlast.setPosition(body.getPosition().x - 20, body.getPosition().y);
				healBlast.setOrigin(healBlast.getRadius(), healBlast.getRadius());
			}
			else
			{
				healBlast.setRadius(0);
			}

		}
		else
		{
			//SoundManager::GetInstance().StopSound("kamehameha");
       
		}

	}
}

void Healer::Draw()
{
	Characters::Draw();
	if (GetCurrentState(ATTACKING))
	{
		GameManager::GetWindow()->draw(healBlast);
	}
}

void Healer::Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites)
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

void Healer::CheckAnimationState()
{
	// Idle - 0, 173 46,  52
// Selected - 0, 124 61, 49
// Healing - 0, 58, 70, 64
// Walking - 0, 0,  48, 57
// Dead - 0, 227, 51, 45

	if (GetCurrentState(IDLE) && !isMovingIntoFormation)
	{
		if (GetSelected())
		{
			amountOfSprites = 4;
			currentFrameX = 61;
			currentFrameY = 124;
			textureWidth = 61;
			textureHeight = 49;
		}
		else
		{
			amountOfSprites = 4;
			currentFrameX = 46;
			currentFrameY = 173;
			textureWidth = 46;
			textureHeight = 52;
		}
	}
	else if (GetCurrentState(MOVING) || isMovingIntoFormation)
	{
		amountOfSprites = 4;
		currentFrameX = 48;
		currentFrameY = 0;
		textureWidth = 48;
		textureHeight = 57;

	}
	else if (GetCurrentState(ATTACKING))
	{
		amountOfSprites = 6;
		currentFrameX = 70;
		currentFrameY = 58;
		textureWidth = 70;
		textureHeight = 64;
	}


	if (GetCurrentState(ATTACKING))
	{
		animationSpeed = 0.04;
	}
	else
	{
		animationSpeed = 0.07;
	}
}

void Healer::Heal()
{
	for (Characters* unit : GameManager::aliveUnits)
	{
		if (unit == this)
		{
			stats.GainHealth(2);
		}
		else
		{
			if (unit->body.getGlobalBounds().intersects(healBlast.getGlobalBounds()))
			{
				unit->stats.GainHealth(unit->stats.GetMaxHealth());
			}
		}
	}

}

sf::Sprite& Healer::GetSprite()
{
	return body;
}
