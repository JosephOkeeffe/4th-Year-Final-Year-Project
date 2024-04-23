#include "SoundManager.h"
#include <filesystem>
#include <random>

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
    menuMusicBuffer.loadFromFile("./assets/sounds/menu.ogg");
    soundBufferMap["menu"] = menuMusicBuffer;

    backgroundMusicBuffer.loadFromFile("./assets/sounds/game-background.ogg");
    soundBufferMap["background"] = backgroundMusicBuffer;

    hurt1Buffer.loadFromFile("./assets/sounds/hurt1.ogg");
    soundBufferMap["hurt1"] = hurt1Buffer;

    hurt2Buffer.loadFromFile("./assets/sounds/hurt2.ogg");
    soundBufferMap["hurt2"] = hurt2Buffer;

    hurt3Buffer.loadFromFile("./assets/sounds/hurt3.ogg");
    soundBufferMap["hurt3"] = hurt3Buffer;

    hurt4Buffer.loadFromFile("./assets/sounds/hurt4.ogg");
    soundBufferMap["hurt4"] = hurt4Buffer;

    hurt5Buffer.loadFromFile("./assets/sounds/hurt5.ogg");
    soundBufferMap["hurt5"] = hurt5Buffer;

    hurt6Buffer.loadFromFile("./assets/sounds/hurt6.ogg");
    soundBufferMap["hurt6"] = hurt6Buffer;

    enemyHurt1Buffer.loadFromFile("./assets/sounds/enemy-hurt1.ogg");
    soundBufferMap["enemyHurt1"] = enemyHurt1Buffer;

    enemyHurt2Buffer.loadFromFile("./assets/sounds/enemy-hurt2.ogg");
    soundBufferMap["enemyHurt2"] = enemyHurt2Buffer;

    enemyHurt3Buffer.loadFromFile("./assets/sounds/enemy-hurt3.ogg");
    soundBufferMap["enemyHurt3"] = enemyHurt3Buffer;

    enemyAttack1Buffer.loadFromFile("./assets/sounds/enemy-attack1.ogg");
    soundBufferMap["enemyAttack1"] = enemyAttack1Buffer;

    enemyAttack2Buffer.loadFromFile("./assets/sounds/enemy-attack2.ogg");
    soundBufferMap["enemyAttack2"] = enemyAttack2Buffer;

    enemyAttack3Buffer.loadFromFile("./assets/sounds/enemy-attack3.ogg");
    soundBufferMap["enemyAttack3"] = enemyAttack3Buffer;

    kamehamehaBuffer.loadFromFile("./assets/sounds/kamehameha.ogg");
    soundBufferMap["kamehameha"] = kamehamehaBuffer;

    swordBuffer.loadFromFile("./assets/sounds/sword.ogg");
    soundBufferMap["sword"] = swordBuffer;

    buildingHitBuffer.loadFromFile("./assets/sounds/building-hit.ogg");
    soundBufferMap["building-hit"] = buildingHitBuffer;

    unlockBuffer.loadFromFile("./assets/sounds/unlock.ogg");
    soundBufferMap["unlock"] = unlockBuffer;

    loseSoundBuffer.loadFromFile("./assets/sounds/lose.ogg");
    soundBufferMap["lose"] = loseSoundBuffer;

    winSoundBuffer.loadFromFile("./assets/sounds/win.ogg");
    soundBufferMap["win"] = winSoundBuffer;

    openInventoryBuffer.loadFromFile("./assets/sounds/open.ogg");
    soundBufferMap["open"] = openInventoryBuffer;

    closeInventoryBuffer.loadFromFile("./assets/sounds/close.ogg");
    soundBufferMap["close"] = closeInventoryBuffer;

    selectBuffer.loadFromFile("./assets/sounds/select.ogg");
    soundBufferMap["select"] = selectBuffer;

    confirmBuffer.loadFromFile("./assets/sounds/confirm.ogg");
    soundBufferMap["confirm"] = confirmBuffer;


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

void SoundManager::PauseSound(const std::string& soundName)
{
    auto it = soundBufferMap.find(soundName);
    if (it != soundBufferMap.end())
    {
        for (auto& sound : soundPool)
        {
            if (sound.getStatus() == sf::Sound::Playing && sound.getBuffer() == &it->second)
            {
                sound.pause();
                std::cout << "Paused sound: " << soundName << "\n";
               // return;
            }
        }
    }
}

void SoundManager::PauseAllSound()
{
    for (auto& sound : soundPool)
    {
        if (sound.getStatus() == sf::Sound::Playing)
        {
            sound.pause();
        }
    }
    std::cout << "Paused all sounds\n";
}

void SoundManager::StopSound(const std::string& soundName)
{
    auto it = soundBufferMap.find(soundName);
    if (it != soundBufferMap.end())
    {
        for (auto& sound : soundPool)
        {
            if (sound.getStatus() == sf::Sound::Playing && sound.getBuffer() == &it->second)
            {
                sound.stop();
                std::cout << "Stopped sound: " << soundName << "\n";
            }
        }
    }
}

void SoundManager::StopAllSound()
{
    for (auto& sound : soundPool)
    {
        if (sound.getStatus() == sf::Sound::Playing)
        {
            sound.stop();
        }
    }
    std::cout << "Stopped all sounds\n";
}

void SoundManager::ResumeAllSound()
{
    for (auto& sound : soundPool)
    {
        if (sound.getStatus() == sf::Sound::Paused)
        {
            sound.play();
        }
    }
    std::cout << "Resumed all sounds\n";
}



