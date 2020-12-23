#include "Menu.h"
/**
 * @brief Construct a new Menu object
 * 
 * @param window 
 */
Menu::Menu(sf::RenderWindow *window) {
    m_window = window;
    m_isActive = true;
    m_changeToGameState = false;

    m_buttonFont.loadFromFile("fonts/8bitwonder.ttf");
    m_backgroundTexture.loadFromFile("pics/menubg.png");

    singleplayerButton = new Button(sf::Vector2f(100.f, 200.f), sf::Vector2f(600.f, 100.f), sf::Color(0.f, 204.f, 102.f, 100.f), sf::Color::White, 30, "S I N G L E P L A Y E R", m_buttonFont);
    m_exitButton = new Button(sf::Vector2f(100.f, 500.f), sf::Vector2f(600.f, 100.f), sf::Color(0.f, 204.f, 102.f, 100.f), sf::Color::White, 30, "E X I T", m_buttonFont);

    m_rectSGB = singleplayerButton->getRectangle();
    m_textSGB = singleplayerButton->getText();

    m_rectEB = m_exitButton->getRectangle();
    m_textEB = m_exitButton->getText();

    m_background.setTexture(m_backgroundTexture);
    m_background.setOrigin(m_background.getGlobalBounds().width / 2.f, m_background.getGlobalBounds().height / 2.f);
    m_background.setScale(8.52f, 8.52f);
    m_background.setPosition(m_window->getSize().x / 2.f, m_window->getSize().y / 2.f);

}

/**
 * @brief if the state is active
 * 
 * @return true, if is active
 * @return false otherwise
 */
bool Menu::getIsActive() {
    return m_isActive;
}

/**
 * @brief sets the m_isActive variable to newIsActive
 * 
 * @param newIsActive 
 */
void Menu::setIsActive(bool newIsActive) {
    m_isActive = newIsActive;
}

/**
 * @brief returns if state should be changed to gamestate or not
 * 
 * @return true, if should be changed to gamestate
 * @return false otherwise
 */
bool Menu::getChangeToGameState() {
    return m_changeToGameState;
}

/**
 * @brief sets new value for m_changeToGameState
 * 
 * @param changeToGameState 
 */
void Menu::setChangeToGameState(const bool &changeToGameState) {
    m_changeToGameState = changeToGameState;
}

/**
 * @brief handles sf::Event events
 * 
 */
void Menu::handleEvents() {
    sf::Event event;
    //this window is a different window
    while (m_window->pollEvent(event)) {
            
        // Close window: exit
        if (event.type == sf::Event::Closed)
            m_window->close();

        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (singleplayerButton->isPressed(event.mouseButton.x, event.mouseButton.y) == true) {
                    m_changeToGameState = true;
                } else if (m_exitButton->isPressed(event.mouseButton.x, event.mouseButton.y) == true) {
                    m_window->close();
                }
            }
        }
    }
}

/**
 * @brief renders menu
 * 
 */
void Menu::render() {
    // Clear screen
    m_window->clear(sf::Color::White);
    
    m_window->draw(m_background);

    //draw items here
    m_window->draw(m_rectSGB);
    m_window->draw(m_textSGB);
    m_window->draw(m_rectEB);
    m_window->draw(m_textEB);

    // Update the window
    m_window->display();
}