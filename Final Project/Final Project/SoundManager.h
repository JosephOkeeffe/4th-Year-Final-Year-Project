#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class SoundManager {
public:

    SoundManager();
    static bool LoadSound(const std::string& name, const std::string& filename);

    static void PlaySound(const std::string& name);

private:
    static std::unordered_map<std::string, sf::SoundBuffer*> mSounds;
};