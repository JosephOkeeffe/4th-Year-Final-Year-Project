
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include "Globals.h"

class Particle
{
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float size;
    int type;

    Particle(const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& col, float particleSize, int particleType)
        : position(pos), velocity(vel), color(col), size(particleSize), type(particleType) {}

    virtual void update()
    {
        position += velocity /** 3.0f*/;

        if (type == 1)
        {
            size -= 0.1f;
            if (size < 0)
            {
                size = 0;
            }
        }
        else if (type == 2)
        {
            // Change color over time
            color.r += 0.1;
            color.g += 0.1;
            color.b += 0.1;
            if (color.a > 1)
            {
                color.a -= 2;
            }
        }
        else if (type == 3)
        {
            // Bounce off the walls
            if (position.x < 0 || position.x > 800)
            {
                velocity.x = -velocity.x;
            }
            if (position.y < 0 || position.y > 600)
            {
                velocity.y = -velocity.y;
            }
        }
        else if (type == 4)
        {
            position = sf::Vector2f(
                position.x + std::cos(size) * 2.0f,
                position.y + std::sin(size) * 2.0f);
            size += 0.1f;
        }
        else if (type == 5)
        {
            // Color burst
            color = sf::Color(rand() % 256, rand() % 256, rand() % 256, 255);
            size -= 0.05f;
        }
        else if (type == 6)
        {
            // Expand
            size += 0.2f;
        }
        else if (type == 7)
        {
           // size -= 0.001f;
            if (color.a >= 5)
            {
                color.a -= 5;
            }

           
        }
    }

    virtual void draw(sf::RenderWindow& window) const
    {
        sf::CircleShape particleShape(size);
        particleShape.setPosition(position);
        particleShape.setOrigin(particleShape.getRadius() / 2, particleShape.getRadius() / 2);
        particleShape.setFillColor(color);
        window.draw(particleShape);
    }
};

class SpriteParticle : public Particle
{
public:
    sf::Sprite sprite;
    sf::Vector2f initialPosition;
    int maxDistance;

    SpriteParticle(const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& col, const sf::Texture& tex, int distance, float particleScale, int particleType)
        : Particle(pos, vel, col, particleScale, particleType), sprite(tex), maxDistance(distance)
    {
        initialPosition = pos;
        sprite.setPosition(pos);
        sprite.setColor(col);
        sprite.setScale(particleScale, particleScale); 
    }

    void update() override
    {
        Particle::update();
        sprite.setPosition(position);

        if (Global::Distance(sprite.getPosition(), initialPosition) > maxDistance)
        {
            size = 0;
            color.a = 0;
        }
    }

    void draw(sf::RenderWindow& window)
    {
        sprite.setColor(color);
        window.draw(sprite);
    }
};

class ParticleSystem
{
public:
    ParticleSystem() {}

    void addParticle(const sf::Vector2f& position, const sf::Vector2f& velocity, const sf::Color& color, float size, int type)
    {
        particles.emplace_back(Particle(position, velocity, color, size, type));
    }

    void AddSpriteParticle(const sf::Vector2f& position, const sf::Vector2f& velocity, const sf::Color& col, const sf::Texture& texture, int distance,float size, int type)
    {
        spriteParticles.emplace_back(SpriteParticle(position, velocity, col, texture, distance, size, type));
    }

    void Update()
    {
        RemoveParticles();

        for (Particle& particle : particles)
        {
            particle.update();
        }

        for (SpriteParticle& spriteParticle : spriteParticles)
        {
            spriteParticle.update();
        }
    }

    void draw(sf::RenderWindow& window)
    {
        for (const auto& particle : particles)
        {
            particle.draw(window);
        }

        for (auto& spriteParticle : spriteParticles)
        {
            spriteParticle.draw(window);
        }
    }

    void RemoveParticles()
    {
        particles.erase(
            std::remove_if(particles.begin(), particles.end(),
                [](const Particle& particle) {
                    return particle.size <= 0 || particle.color.a <= 0;
                }),
            particles.end());

        spriteParticles.erase(std::remove_if(spriteParticles.begin(), spriteParticles.end(), [](const SpriteParticle& particle) {return particle.size < -1 || particle.color.a <= 0; }), spriteParticles.end());
    }

    void clearParticles()
    {
        particles.clear();
        spriteParticles.clear();
    }

 

private:
    std::vector<Particle> particles;
    std::vector<SpriteParticle> spriteParticles;
};
