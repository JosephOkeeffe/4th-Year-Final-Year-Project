
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>

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
        position += velocity;

        if (type == 1)
        {
            // Shrink over time
            size -= 0.1f;
            if (size < 0)
            {
                size = 0;
            }
        }
        else if (type == 2)
        {
            // Change color over time
            color.g += 1;
            color.b += 2;
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
            // Rotate
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
            size -= 0.1f;
            color.a -= 5;
        }
    }

    virtual void draw(sf::RenderWindow& window) const
    {
        sf::CircleShape particleShape(size);
        particleShape.setPosition(position);
        particleShape.setFillColor(color);
        window.draw(particleShape);
    }
};

class SpriteParticle : public Particle
{
public:
    sf::Sprite sprite;

    SpriteParticle(const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Texture& tex, float particleScale, int particleType)
        : Particle(pos, vel, sf::Color::White, particleScale, particleType), sprite(tex)
    {
        sprite.setPosition(pos);
        sprite.setScale(particleScale, particleScale); 
    }

    void update() override
    {
        Particle::update();
        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow& window) const override
    {
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

    void addSpriteParticle(const sf::Vector2f& position, const sf::Vector2f& velocity, const sf::Texture& texture, float size, int type)
    {
        spriteParticles.emplace_back(SpriteParticle(position, velocity, texture, size, type));
    }

    void update()
    {
        particles.erase(
            std::remove_if(particles.begin(), particles.end(),
                [](const Particle& particle) {
                    return particle.size <= 0 || particle.color.a <= 0;
                }),
            particles.end());

        spriteParticles.erase(
            std::remove_if(spriteParticles.begin(), spriteParticles.end(),
                [](const SpriteParticle& particle) {
                    return particle.size <= 0 || particle.color.a <= 0;
                }),
            spriteParticles.end());

        for (auto& particle : particles)
        {
            particle.update();
        }

        for (auto& spriteParticle : spriteParticles)
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

        for (const auto& spriteParticle : spriteParticles)
        {
            spriteParticle.draw(window);
        }
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
