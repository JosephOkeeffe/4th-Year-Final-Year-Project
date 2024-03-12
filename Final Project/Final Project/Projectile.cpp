#include "Projectile.h"

#include <SFML/Graphics.hpp>

Projectile::Projectile(sf::Texture& texture, sf::Vector2f startPosition, sf::Vector2f targetPosition)
{
    startPos = startPosition;
    body.setTexture(texture);
    body.setPosition(startPosition);
    direction = Global::Normalize(targetPosition - startPos);
    speed = 1.0f; // Adjust the speed as needed
}

void Projectile::Update()
{
    sf::Vector2f movement = direction * speed;
    body.move(movement);
}

void Projectile::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

bool Projectile::IsOutOfRange(float range)
{
    return GetDistanceTraveled() > range;
}

float Projectile::GetDistanceTraveled()
{
    return std::sqrt(pow(body.getPosition().x - startPos.x, 2) + pow(body.getPosition().y - startPos.y, 2));
}

