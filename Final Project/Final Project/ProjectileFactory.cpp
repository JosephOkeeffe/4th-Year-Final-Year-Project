// ProjectileFactory.cpp
#include "ProjectileFactory.h"
#include "BasicProjectile.h"
#include "HomingProjectile.h"
#include "ShieldProjectile.h"

ProjectileFactory::ProjectileFactory() {}

ProjectileFactory::~ProjectileFactory() 
{
    for (auto projectile : m_projectiles) 
    {
        delete projectile;
    }
}

Projectile* ProjectileFactory::CreateBasicProjectile(sf::Texture& texture, sf::Texture& trailTexture, float trailScale, sf::Vector2f startPos, sf::Vector2f targetPos, float _speed, float _range, float _scale)
{
    BasicProjectile* projectile = new BasicProjectile(texture, startPos, targetPos, _speed, _range, _scale);
    projectile->trailTexture = trailTexture;
    projectile->trailScale = trailScale;
    m_projectiles.push_back(projectile);
    return projectile;
}

Projectile* ProjectileFactory::CreateHomingProjectile(sf::Texture& texture, sf::Texture& trailTexture, float trailScale, sf::Vector2f startPos, sf::Vector2f targetPos, float _speed, float _range, float _scale)
{
    HomingProjectile* projectile = new HomingProjectile(texture, startPos, targetPos, _speed, _range, _scale);
    projectile->trailTexture = trailTexture;
    projectile->trailScale = trailScale;
    m_projectiles.push_back(projectile);
    return projectile;
}

Projectile* ProjectileFactory::CreateShieldProjectile(sf::Texture& texture, sf::Texture& trailTexture, float trailScale, sf::Vector2f startPos, float _speed, float scale, float _radius)
{
    ShieldProjectile* projectile = new ShieldProjectile(texture, startPos, _speed, scale, _radius);
    projectile->trailTexture = trailTexture;
    projectile->trailScale = trailScale;
    projectile->tag = "shield";
    m_projectiles.push_back(projectile);
    return projectile;
}
