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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		Projectile projectile(Textures::GetInstance().GetTexture("coin"), body.getPosition(), { 200,200 });

		projectiles.push_back(projectile);
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
	Characters::Draw();

	for (Projectile& projectile : projectiles)
	{
		projectile.Draw(*GameManager::GetWindow());
	}

	if(GetSelected())
	{
		stats.DisplayStats(*GameManager::GetWindow());
	}
}

void Archer::AnimateArcher()
{
	Animate(currentFrameX, currentFrameY * textureHeight, textureWidth, textureHeight, body, amountOfSprites);
}

void Archer::CheckAnimationState()
{

	if (GetCurrentState(IDLE) && !isMovingIntoFormation)
	{
		currentFrameY = 0;
		textureHeight = 50;
	}
	else if (GetCurrentState(MOVING) || isMovingIntoFormation)
	{
		currentFrameY = 2;
		textureHeight = 52;
	}
	else if (GetCurrentState(ATTACKING))
	{
		currentFrameY = 3;
	}
	else if (GetCurrentState(DEAD))
	{
		currentFrameY = 4;
	}


}

sf::Sprite& Archer::GetSprite()
{
	return body;
}
