#include <SFML/Graphics.hpp>
#include "ProjectileFactory.h"

class HomingProjectile : public Projectile
{
public:
    HomingProjectile(sf::Texture& texture, sf::Vector2f startPosition, sf::Vector2f targetPosition, float _speed, float _range, float _scale);

    void Update() override;

    bool operator==(const HomingProjectile& other) const
    {
        return this->body.getPosition() == other.body.getPosition();
    }

    sf::Clock timer;
    float homingDelay = 0.5;
};
