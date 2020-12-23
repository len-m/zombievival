#ifndef MENU_H
#define MENU_H

#include "../Button.h"

class Menu {
    public:
        Menu(sf::RenderWindow *window);
        void handleEvents();
        void render();
        bool getIsActive();
        void setIsActive(bool newIsActive);
        bool getChangeToGameState();
        void setChangeToGameState(const bool &changeToGameState);
    private:
        bool m_isActive;
        bool m_changeToGameState;
        Button *singleplayerButton;
        Button *m_exitButton;
        sf::Texture m_backgroundTexture;
        sf::Sprite m_background;
        sf::RectangleShape m_rectSGB;
        sf::RectangleShape m_rectEB;
        sf::Font m_buttonFont;
        sf::Text m_textSGB;
        sf::Text m_textEB;
        sf::RenderWindow *m_window;
};

#endif