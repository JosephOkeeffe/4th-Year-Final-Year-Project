#include "HomingProjectile.h"
#include <cmath>

HomingProjectile::HomingProjectile(sf::Texture& texture, sf::Vector2f startPos, sf::Vector2f targetPos, float _speed, float _range, float _scale)
{
    startPosition = startPos;
    targetPosition = targetPos;
    speed = _speed;
    range = _range;
    scale = _scale;

    //float yScale = (scale < 1) ? (scale * -1) : scale;

    body.setTexture(texture);
    body.setPosition(startPos);
    body.setScale(scale, scale);
    body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
    direction = Global::Normalize(targetPos - startPos);

}

void HomingProjectile::Update()
{
    Projectile::Update();
    particleSystem.AddSpriteParticle(body.getPosition(), { 0,0 }, sf::Color::White, Textures::GetInstance().GetTexture("blast-trail"), 200, 0.3, 7);
    sf::Vector2f targetDirection = Global::Normalize(targetPosition - body.getPosition());
    

    if (timer.getElapsedTime().asSeconds() > homingDelay)
    {
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

        if (scale < 0)
        {
           // rotationSpeed = -1.5f; 
        }

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
    else
    {
        if (scale > 0)
        {
            body.move(speed, 0);
        }
        else
        {
            body.move(-speed, 0);

        }
    }


}


//void HomingProjectile::Draw(sf::RenderWindow& window)
//{
//
//}


