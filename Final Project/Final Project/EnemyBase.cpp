#include "EnemyBase.h"
#include "SoundManager.h"

EnemyBase::EnemyBase(sf::Vector2f pos, Item itemNeeded) : itemRequired(itemNeeded), isOpen(false), isDestroyed(false), itemNeededAmount(1)
{
	Init(pos);
}

void EnemyBase::Init(sf::Vector2f pos)
{
	body.setTexture(Textures::GetInstance().GetTexture("enemy-base"));
	body.setScale(1.8, 1.4);
	body.setPosition({ pos.x + body.getGlobalBounds().width / 2, pos.y + body.getGlobalBounds().height / 4 });
	body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);


	sf::Color colour = sf::Color::White;
	colour.a = 220;

	itemRequiredSprite.setTexture(&Textures::GetInstance().GetTexture(itemRequired.GetTextureName()));
	itemRequiredSprite.setPosition({pos.x + 15, pos.y - 60});
	itemRequiredSprite.setSize({ 30, 30 });
	itemRequiredSprite.setOrigin(itemRequiredSprite.getSize().x / 2, itemRequiredSprite.getSize().y / 2);
	itemRequiredSprite.setFillColor(colour);

	itemRequiredText.setFont(Global::font);
	itemRequiredText.setCharacterSize(24);
	itemRequiredText.setString( "x" + std::to_string(itemRequired.GetQuantity()));
	itemRequiredText.setPosition({ itemRequiredSprite.getPosition().x - 35,  itemRequiredSprite.getPosition().y - 15 });
	itemRequiredText.setOutlineThickness(1);
	itemRequiredText.setOutlineColor(sf::Color::Black);
	itemRequiredText.setFillColor(colour);


	sf::Vector2i cellPos = Global::ConvertPositionToCell(pos);

	GameManager::tiles[cellPos.x][cellPos.y].SetTileType(TILE_USED_UP);
	

}

void EnemyBase::Update()
{
	body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
	itemRequiredText.setString("x" + std::to_string(itemRequired.GetQuantity()));

	sf::Vector2i cellPos = Global::ConvertPositionToCell(body.getPosition());

	GameManager::tiles[cellPos.x][cellPos.y].SetTileType(TILE_USED_UP);

	if (stats.GetCurrentHealth() <= 0)
	{
		DestroyBase();
	}

	if (itemRequired.GetQuantity() <= 0 && !isOpen)
	{
		isOpen = true;
	}

	if (body.getColor() == sf::Color::Red && redTimer.getElapsedTime().asSeconds() > 0.3)
	{
		body.setColor(sf::Color::White);
	}
}

void EnemyBase::Draw(sf::RenderWindow& window)
{
	window.draw(body);

	if (!isOpen)
	{
		window.draw(itemRequiredSprite);
		window.draw(itemRequiredText);
	}
}

void EnemyBase::TakeDamage(int damage)
{

	SoundManager::GetInstance().PlaySound("building-hit", 40, false);

	if(!isDestroyed)
	{
		stats.LoseHealth(damage);
		body.setColor(sf::Color::Red);
		redTimer.restart();
	}
}

void EnemyBase::DestroyBase()
{
	isDestroyed = true;
	body.setTexture(Textures::GetInstance().GetTexture("enemy-base-destroyed"));
	sf::Color colour = sf::Color::White;
	colour.a = 220;
	body.setColor(colour);
	GameManager::enemyBasesLeftAlive--;
}

