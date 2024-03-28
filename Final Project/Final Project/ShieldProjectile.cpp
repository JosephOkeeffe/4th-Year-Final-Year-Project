#include "ShieldProjectile.h"

ShieldProjectile::ShieldProjectile(sf::Texture& texture, sf::Vector2f startPos, float _speed, float _scale, float _radius)
{
    startPosition = startPos;
    centrePosition = startPos;
    speed = _speed;
    radius = _radius;
    angle = 0;

    body.setTexture(texture);
    body.setScale(_scale, _scale);
    body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
}

void ShieldProjectile::Update() 
{
    // Update the angle based on the speed
    angle += speed;

    // Calculate the new position using polar coordinates
    float x = centrePosition.x + radius * std::cos(angle * 3.14159265359 / 180);
    float y = centrePosition.y + radius * std::sin(angle * 3.14159265359 / 180);
    body.setPosition(x, y);
}

void ShieldProjectile::Draw(sf::RenderWindow& window) 
{
    window.draw(body);
}

void ShieldProjectile::UpdateCentre(sf::Vector2f centre)
{
    centrePosition = centre;
}
