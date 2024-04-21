#include "SoundManager.h"
#include <filesystem>

SoundManager& SoundManager::GetInstance()
{
    static SoundManager instance;
    return instance;
}

SoundManager::SoundManager()
{
    SetupSounds();
}

void SoundManager::SetupSounds()
{
    shotBuffer.loadFromFile("./assets/sounds/shot.ogg");
    backgroundBuffer.loadFromFile("./assets/sounds/game-background.ogg");
    mumbleBuffer.loadFromFile("./assets/sounds/Mumble.ogg");

    hurt1Buffer.loadFromFile("./assets/sounds/hurt1.ogg");
    hurt2Buffer.loadFromFile("./assets/sounds/hurt2.ogg");
    hurt3Buffer.loadFromFile("./assets/sounds/hurt3.ogg");
    hurt4Buffer.loadFromFile("./assets/sounds/hurt4.ogg");
    hurt5Buffer.loadFromFile("./assets/sounds/hurt5.ogg");
    hurt6Buffer.loadFromFile("./assets/sounds/hurt6.ogg");

    soundBufferMap["shot"] = shotBuffer;
    soundBufferMap["background"] = backgroundBuffer;
    soundBufferMap["mumble"] = mumbleBuffer;

    soundBufferMap["hurt1"] = hurt1Buffer;
    soundBufferMap["hurt2"] = hurt2Buffer;
    soundBufferMap["hurt3"] = hurt3Buffer;
    soundBufferMap["hurt4"] = hurt4Buffer;
    soundBufferMap["hurt5"] = hurt5Buffer;
    soundBufferMap["hurt6"] = hurt6Buffer;

    for (int i = 0; i < MAX_SOUND_INSTANCES; ++i) 
    {
        soundPool.emplace_back();
    }
}

void SoundManager::PlaySound(const std::string& soundName, int volume, bool isLooped)
{
    auto it = soundBufferMap.find(soundName);
    if (it != soundBufferMap.end())
    {
        for (auto& sound : soundPool) 
        {
            if (sound.getStatus() != sf::Sound::Playing)
            {
                sound.setBuffer(it->second);
                sound.setVolume(volume);
                sound.setLoop(isLooped);
                sound.play();
                std::cout << "Playing sound: " << soundName << "\n";
                return;
            }
        }
    }

}

#include <random>

void SoundManager::PlayRandomSound(const std::vector<std::string>& soundNames, int volume, bool isLooped)
{
    if (soundNames.empty()) 
    {
        std::cerr << "Error: Empty vector of sound names!" << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, soundNames.size() - 1);

    int randomIndex = dis(gen);

    std::string randomSoundName = soundNames[randomIndex];

    PlaySound(randomSoundName, volume, isLooped);
}


void SoundManager::PlayBackgroundSound()
{
    backgroundSound.play();
}

