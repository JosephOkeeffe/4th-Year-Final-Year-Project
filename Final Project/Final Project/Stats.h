#pragma once
#include <SFML/Graphics.hpp>

class Stats
{
public:
    // MAYBE DO SKILL TREE
    Stats(int maxHealth, int dmg, float attackSpeed)
    {
        level = 1;
        knockBackDistance = 20;
        SetCurrentXP(0);
        SetXPNeededForNextLevel(10);
        SetMaxHealth(maxHealth);
        SetCurrentHealth(maxHealth);
        SetDamage(dmg);
        SetAttackSpeed(attackSpeed);

        InitSprites();
    }

    void InitSprites();
    void Draw(sf::RenderWindow& window);
    void DisplayAllStats(sf::RenderWindow& window, sf::Vector2f pos);
    void DisplayTextStats(sf::RenderWindow& window, sf::Vector2f pos);
    void DisplayHealthBar(sf::RenderWindow& window, sf::Vector2f pos);
    void DisplayXPBar(sf::RenderWindow& window, sf::Vector2f pos);
    void DrawStatBar(sf::RenderWindow& window, const std::string& label, int currentStat, int maxStat, const sf::Color& color, float xPosition, float yPosition);

    sf::Text text;
    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape xpBar;
    sf::RectangleShape xpBarBackground;

    void LevelUp()
    {
        level++;
        SetXPNeededForNextLevel(GetCurrentXP() + 10);
        SetCurrentXP(0);
    }

    void IncreaseXP(int newXP)
    {
        currentXP += newXP;
        if (GetCurrentXP() >= xpNeededForNextLevel)
        {
            LevelUp();
        }
    }

    void GainHealth(int healthToGain)
    {
        currentHealth += healthToGain;
        if (currentHealth > MAX_HEALTH)
        {
            currentHealth = MAX_HEALTH;
        }
    }

    void LoseHealth(int healthToLose)
    {
        currentHealth -= healthToLose;
    }

    void SetCurrentXP(int newXP)
    {
        currentXP = newXP;
    }

    void SetXPNeededForNextLevel(int newXPNeeded)
    {
        xpNeededForNextLevel = newXPNeeded;
    }

    void SetCurrentHealth(int newHealth)
    {
        currentHealth = newHealth;
    }

    void SetMaxHealth(int newMaxHealth)
    {
        MAX_HEALTH = newMaxHealth;
    }

    void SetDamage(int newDamage)
    {
        damage = newDamage;
    }

    void SetAttackSpeed(float newAttackSpeed)
    {
        attackSpeed = newAttackSpeed;
    }

    int GetLevel()
    {
        return level;
    }
    int GetCurrentXP()
    {
        return currentXP;
    }
    int GetXPNeededForNextLevel()
    {
        return xpNeededForNextLevel;
    }
    int GetCurrentHealth()
    {
        return currentHealth;
    }
    int GetMaxHealth()
    {
        return MAX_HEALTH;
    }
    int GetDamage()
    {
        return damage;
    }
    float GetAttackSpeed()
    {
        return attackSpeed;
    }

    float GetKnockback()
    {
        return knockBackDistance;
    }

private:
    int level;
    int currentXP;
    int xpNeededForNextLevel;
    int currentHealth;
    int MAX_HEALTH;
    int damage;
    float attackSpeed;
    float knockBackDistance;
    // Maybe add in some debuffs
};
