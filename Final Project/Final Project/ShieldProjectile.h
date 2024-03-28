#pragma once
#include <SFML/Graphics.hpp>
#include "ProjectileFactory.h"

class ShieldProjectile : public Projectile 
 {
public:
    ShieldProjectile(sf::Texture& texture, sf::Vector2f startPos, float _speed, float scale, float _radius);

    void Update() override;
    void Draw(sf::RenderWindow& window) override;

    void UpdateCentre(sf::Vector2f centre);

private:
    float radius;
    float angle;
};
