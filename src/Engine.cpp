#include "Engine.h"
/**
 * @brief Construct a new Engine object
 * 
 */
Engine::Engine()
    : m_window(sf::VideoMode(800, 800), "Zombievival", sf::Style::Close),
    m_menu(&m_window) {
    srand(time(NULL));
    m_window.setFramerateLimit(150);
}

/**
 * @brief game and menu loop
 * 
 */
void Engine::loop() {
    while (m_window.isOpen()) {

        m_deltaTime = m_deltaTimeClock.restart().asSeconds();
        //std::cout << deltaTime << std::endl;
        
        if (m_menu.getIsActive() == true) {
            //menu
            m_menu.handleEvents();
            m_menu.render();

        } else if (m_game->getIsActive() == true) {
            //game
            if (m_game->getIsDead()) {
                //the whole population is dead
                m_window.setMouseCursorVisible(true);
                //check for window close
                sf::Event event;
                while (m_window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        m_window.close();
                }
                //m_game->render();
            } else if (m_game->getIsPaused()) {
                
                m_window.setMouseCursorVisible(true);

                sf::Event event;
                while (m_window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        m_window.close();

                    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                        m_game->setIsPaused(false);
                        m_window.setMouseCursorVisible(false);
                    }
                }

            } else {
                m_game->update(m_deltaTime);
                m_game->render();
            
            }
        } else {
            std::cout << "no state is active" << std::endl; //this should never happen
        }

        //state changer
        if(m_menu.getChangeToGameState()) {
            m_menu.setIsActive(false);
            //only change gamestate once
            m_menu.setChangeToGameState(false);
            m_game = new Game(&m_window);
            m_game->setIsActive(true);
            m_window.setMouseCursorVisible(false);
        }
    }
}