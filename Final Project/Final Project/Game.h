#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Grid.h"
#include "GameView.h"
#include "Textures.h"
#include "Warrior.h"

class Game
{
public:
    Game();
    ~Game();

    void run();

private:

    void ProcessEvents();
    void ProcessKeys(sf::Event t_event);
    void ProcessMouse(sf::Event t_event);
    void Update(sf::Time t_deltaTime);
    void Render();
    void Init();

    sf::RenderWindow m_window;
    sf::Font m_font;
    bool m_exitGame;

    Textures textures;
    Grid grid;
    GameView gameView{ m_window };

    Warrior warrior;

};

#endif