#include "Projectile.h"
#include <cmath>
#include <SFML/Graphics.hpp>

Projectile::Projectile(sf::Texture& texture, sf::Vector2f startPosition, sf::Vector2f targetPosition, float scale)
{
    startPos = startPosition;
    startPos.x = startPosition.x + 80;
    targetPos = targetPosition;
    body.setTexture(texture);
    body.setPosition(startPos);
    body.setScale(scale, scale);
    body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
    direction = Global::Normalize(targetPos - startPos);
    speed = 1.0f;
}

void Projectile::Update()
{
    sf::Vector2f targetDirection = Global::Normalize(targetPos - body.getPosition());
    float angle = atan2(targetDirection.y, targetDirection.x) * 180 / 3.14; 
    float currentRotation = body.getRotation(); 
    float angleRad = currentRotation * 3.14 / 180;
    float rotationDiff = angle - currentRotation;

    if (rotationDiff > 180)
    {
        rotationDiff -= 360;
    }
    else if (rotationDiff < -180)
    {
        rotationDiff += 360;
    }

    float rotationSpeed = 1.5f;

    if (std::abs(rotationDiff) > rotationSpeed)
    {
        if (rotationDiff > 0)
        {
            body.rotate(rotationSpeed);
        }
        else
        {
            body.rotate(-rotationSpeed);
        }
    }
    else
    {
        body.setRotation(angle); 
    }

    sf::Vector2f movementVector = sf::Vector2f(cos(angleRad), sin(angleRad));
    body.move(movementVector.x * speed, movementVector.y * speed); 

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

