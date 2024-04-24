#ifndef BASIC_PROJECTILE_H
#define BASIC_PROJECTILE_H

#include "ProjectileFactory.h"

class BasicProjectile : public Projectile 
{
public:
    BasicProjectile(sf::Texture& texture, sf::Vector2f startPos, sf::Vector2f targetPos, float _speed, float _range, float _scale);

    void Update() override;

private:


};

#endif
