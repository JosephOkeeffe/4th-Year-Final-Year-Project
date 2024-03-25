#include "Suckler.h"

Suckler::Suckler(int _id)
{
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
	
}

void Suckler::Update()
{
	Enemy::Update();

	if (hasMerged && !mergeComplete)
	{
		body.setTexture(Textures::GetInstance().GetTexture("big-suckler"));
		body.setTextureRect(sf::IntRect{ 0, 0, 218 , 208 });
		body.setOrigin(body.getTextureRect().width / 2, body.getTextureRect().height / 2);
		mergeComplete = true;
		enemyType = BIG_SUCKLER;
	}

	if (enemyType == SUCKLER_FEMALE && enemyType != BIG_SUCKLER)
	{

		if(target != nullptr && !target->hasMerged)
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
		
	}
	
	
	
}
