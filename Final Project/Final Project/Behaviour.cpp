#include "Behaviour.h"

sf::Vector2f Behaviour::Normalise(sf::Vector2f vector)
{
    sf::Vector2f normalised = { 0.0f, 0.0f };
    float length = VectorLength(vector);

    if (length == 0.0f)
        return vector;

    normalised.x = vector.x / length;
    normalised.y = vector.y / length;

    return normalised;
}

float Behaviour::VectorLength(sf::Vector2f vector)
{
    float vLength = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    return vLength;
}

sf::Vector2f Behaviour::GetDirectionFacing(sf::Vector2f targetPos, sf::Vector2f currentPos)
{
    return targetPos - currentPos;
}

sf::Vector2f Behaviour::AngleToVector(float angle)
{
    sf::Vector2f vector;
    vector.x = cos(angle * (3.14159265 / 180));
    vector.y = sin(angle * (3.14159265 / 180));
    return vector;
}

SteeringOutput Behaviour::WanderBehaviour(sf::Sprite& sprite)
{
    SteeringOutput steeringOutput;

    float wanderRadius = 0.5f;
    float wanderDistance = 0.5f;
    float m_wanderAngle = 1;

    float angleChange = (std::rand() % 360) * 0.5f;

    m_wanderAngle += angleChange;

    sf::Vector2f circleCenter = sprite.getPosition() + Normalise(sprite.getPosition()) * wanderDistance;

    sf::Vector2f targetPosition = circleCenter + sf::Vector2f(std::cos(m_wanderAngle), std::sin(m_wanderAngle)) * wanderRadius;

    sf::Vector2f desiredLinear = targetPosition - sprite.getPosition();
    float desiredAngular = 0.0f;


    steeringOutput.linear = desiredLinear;
    steeringOutput.angular = desiredAngular;


    return steeringOutput;
}

SteeringOutput Behaviour::SeekBehaviour(sf::Vector2f& targetPos, sf::Sprite& sprite)
{
    SteeringOutput steeringOutput;
    float maxAcceleration = 0.001f;
    // Linear
    steeringOutput.linear = targetPos - sprite.getPosition();
    Normalise(steeringOutput.linear);
    steeringOutput.linear *= maxAcceleration;

    // Angular
    sf::Vector2f direction = steeringOutput.linear;
    float angle = atan2(direction.y, direction.x) * 180 / 3.14159265;
    steeringOutput.angular = angle;

    return steeringOutput;
}

