//#include <SFML/Audio.hpp>
//#include <unordered_map>
//#include <string>
//#include <iostream>
// 
//
//class SoundManager 
//{
//public:
//
//    static void Init();
//    static bool LoadSound(const std::string& name, const std::string& filename);
//
//    static void PlaySound(const std::string& name);
//
//private:
//    static std::unordered_map<std::string, sf::SoundBuffer*> mSounds;
//};
//

#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <iostream>

class SoundManager
{
public:
    static SoundManager& GetInstance();

    void SetupSounds();
    void PlaySound(const std::string& soundName, int volume, bool isLooped);
    void PauseSound(const std::string& soundName);
    void PauseAllSound();
    void StopSound(const std::string& soundName);
    void StopAllSound();
    void ResumeAllSound();
    void PlayRandomSound(const std::vector<std::string>& soundNames, int volume, bool isLooped);

private:
    SoundManager();

    std::map<std::string, sf::SoundBuffer> soundBufferMap;

    sf::SoundBuffer menuMusicBuffer;
    sf::SoundBuffer backgroundMusicBuffer;

    sf::SoundBuffer enemyAttack1Buffer;
    sf::SoundBuffer enemyAttack2Buffer;
    sf::SoundBuffer enemyAttack3Buffer;

    sf::SoundBuffer hurt1Buffer;
    sf::SoundBuffer hurt2Buffer;
    sf::SoundBuffer hurt3Buffer;
    sf::SoundBuffer hurt4Buffer;
    sf::SoundBuffer hurt5Buffer;
    sf::SoundBuffer hurt6Buffer;

    sf::SoundBuffer enemyHurt1Buffer;
    sf::SoundBuffer enemyHurt2Buffer;
    sf::SoundBuffer enemyHurt3Buffer;

    sf::SoundBuffer kamehamehaBuffer;
    sf::SoundBuffer swordBuffer;

    sf::SoundBuffer buildingHitBuffer;
    sf::SoundBuffer unlockBuffer;

    sf::SoundBuffer openInventoryBuffer;
    sf::SoundBuffer closeInventoryBuffer;

    sf::SoundBuffer loseSoundBuffer;
    sf::SoundBuffer winSoundBuffer;

    sf::SoundBuffer selectBuffer;
    sf::SoundBuffer confirmBuffer;




    std::vector<sf::Sound> soundPool;

    int MAX_SOUND_INSTANCES = 30;

};


