// ProjectileFactory.h
#ifndef PROJECTILE_FACTORY_H
#define PROJECTILE_FACTORY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Globals.h"
#include "ParticleSystem.h"
#include "Textures.h"


class Projectile 
{
public:

    sf::Sprite body;
    sf::Vector2f startPosition = { -100, -100 };
    sf::Vector2f targetPosition = { -100, -100 };
    sf::Vector2f centrePosition = { -100, -100 };
    sf::Vector2f previousPosition = { -100, -100 };
    sf::Vector2f direction = { -100, -100 };
    float speed = 1;
    float range = 200;
    float scale = 1;
    ParticleSystem particleSystem;


    virtual void Update()
    {
        previousPosition = body.getPosition();
        particleSystem.AddSpriteParticle(body.getPosition(), { 0,0 }, sf::Color::White, Textures::GetInstance().GetTexture("blast-trail"), 200, 0.3, 7);
    }
    virtual void Draw(sf::RenderWindow& window)
    {
        particleSystem.draw(window);
        window.draw(body);        
    }

    bool IsOutOfRange( sf::Vector2f currentPos, sf::Vector2f startPos)
    {
        float distanceTravelled = GetDistanceTraveled(currentPos, startPos);
        return distanceTravelled > range;
    }

    float GetDistanceTraveled(sf::Vector2f currentPos, sf::Vector2f startPos)
    {
        return std::sqrt(pow(currentPos.x - startPos.x, 2) + pow(currentPos.y - startPos.y, 2));
    }

    sf::Vector2f CalculateMovementVector() 
    {
        return body.getPosition() - previousPosition;
    }


};

class ProjectileFactory 
{
public:
    ProjectileFactory();
    ~ProjectileFactory();

    Projectile* CreateBasicProjectile(sf::Texture& texture, sf::Vector2f startPos, sf::Vector2f targetPos, float _speed, float _range, float _scale);
    Projectile* CreateHomingProjectile(sf::Texture& texture, sf::Vector2f startPos, sf::Vector2f targetPos, float _speed, float _range, float _scale);
    Projectile* CreateShieldProjectile(sf::Texture& texture, sf::Vector2f startPos,float _speed, float scale, float _radius);

private:
    std::vector<Projectile*> m_projectiles;
};

#endif
