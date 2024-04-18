#include "SoundManager.h"

std::unordered_map<std::string, sf::SoundBuffer*> SoundManager::mSounds;

SoundManager::SoundManager()
{
    LoadSound("shot", "./ assets/sounds/shot.ogg");
}

bool SoundManager::LoadSound(const std::string& name, const std::string& filename)
{
    sf::SoundBuffer* buffer = new sf::SoundBuffer();
    if (!buffer->loadFromFile(filename))
    {
        delete buffer;
        return false;
    }
    mSounds[name] = buffer;
    return true;
}

void SoundManager::PlaySound(const std::string& name)
{
    auto it = mSounds.find(name);

    if (it != mSounds.end())
    {
        sf::Sound sound(*it->second);
        sound.play();
    }
}