#include <SFML/Graphics.hpp>
#include "Globals.h"

class Projectile
{
public:
    Projectile(sf::Texture& texture, sf::Vector2f startPosition, sf::Vector2f targetPosition);
    void Update();

    void Draw(sf::RenderWindow& window);

    bool IsOutOfRange(float range);

    float GetDistanceTraveled();

    bool operator==(const Projectile& other) const
    {
        return this->body.getPosition() == other.body.getPosition();
    }

private:
    sf::Sprite body;
    sf::Vector2f startPos;
    sf::Vector2f direction;
    float speed;
};
