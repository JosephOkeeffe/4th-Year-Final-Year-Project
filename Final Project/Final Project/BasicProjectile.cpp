#include "BasicProjectile.h"

BasicProjectile::BasicProjectile(sf::Texture& texture, sf::Vector2f startPos, sf::Vector2f targetPos, float _speed, float _range, float _scale)
{
    startPosition = startPos;
    targetPosition = targetPos;
    speed = _speed;
    range = _range;

    body.setTexture(texture);
    body.setPosition(startPosition);
    body.setScale(_scale, _scale);
}

void BasicProjectile::Update()
{
    Projectile::Update();

    sf::Vector2f direction = Global::Normalize(targetPosition - startPosition);
    body.move(direction * speed);
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14;
    body.setRotation(angle - 90);
    
}

