#ifndef ENGINE_H
#define ENGINE_H

#include "menu/Menu.h"
#include "game/Game.h"
#include <time.h>

class Engine {
    public:
        Engine();
        void loop();
    private:
        sf::RenderWindow m_window;

        sf::Clock m_deltaTimeClock;
        float m_deltaTime;
        
        Menu m_menu;
        Game *m_game;
};

#endif