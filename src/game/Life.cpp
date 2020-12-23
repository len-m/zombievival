#include "Life.h"
/**
 * @brief Construct a new Life object
 * 
 * @param currentLife
 * @param maxLife
 * @param position 
 * @param size size of the life sf::Rectangles
 */
Life::Life(const float &currentLife, const float &maxLife, const sf::Vector2f &position, const sf::Vector2f &size) {
    m_currentLife = currentLife;
    m_maxLife = maxLife;
    m_rectangleBackground.setSize(size);
    m_rectangleBackground.setOrigin(m_rectangleBackground.getGlobalBounds().width / 2.f, m_rectangleBackground.getGlobalBounds().height / 2.f);
    m_rectangleBackground.setPosition(position);
    m_rectangleBackground.setFillColor(sf::Color(255.f, 230.f, 230.f, 170.f));

    m_rectangleDisplayLife.setPosition(
        (m_rectangleBackground.getGlobalBounds().left) + (1.f / 10.f * m_rectangleBackground.getSize().y),
        (m_rectangleBackground.getGlobalBounds().top) + (1.f / 10.f * m_rectangleBackground.getSize().y)
    );

    m_rectangleDisplayLife.setSize(sf::Vector2f(
        (m_currentLife / m_maxLife) * (m_rectangleBackground.getSize().x - (2 * (1.f / 10.f * m_rectangleBackground.getSize().y))),
        (8.f / 10.f) * m_rectangleBackground.getSize().y
    ));

    m_rectangleDisplayLife.setFillColor(sf::Color(255.f, 51.f, 51.f, 170.f));
}

/**
 * @brief set currentLife var
 * 
 * @param currentLife 
 */
void Life::setCurrentLife(const float &currentLife) {
    m_currentLife = currentLife;
}

/**
 * @brief sets maxLife var
 * 
 * @param maxLife 
 */
void Life::setMaxLife(const float &maxLife) {
    m_maxLife = maxLife;
}

/**
 * @brief set the position of the sf::Rectangles
 * 
 * @param position 
 */
void Life::setPosition(const sf::Vector2f &position) {
    m_rectangleBackground.setPosition(position);
    m_rectangleDisplayLife.setPosition(
        (m_rectangleBackground.getGlobalBounds().left) + (1.f / 10.f * m_rectangleBackground.getSize().y),
        (m_rectangleBackground.getGlobalBounds().top) + (1.f / 10.f * m_rectangleBackground.getSize().y)
    );
}

/**
 * @brief set the size of the sf::Rectangles
 * 
 */
void Life::setLifeSize() {
    m_rectangleDisplayLife.setSize(sf::Vector2f(
        (m_currentLife / m_maxLife) * (m_rectangleBackground.getSize().x - (2 * (1.f / 10.f * m_rectangleBackground.getSize().y))),
        (8.f / 10.f) * m_rectangleBackground.getSize().y
    ));
}

/**
 * @brief returns the sf::Rectangles as a vector
 * 
 * @return std::vector<sf::RectangleShape> 
 */
std::vector<sf::RectangleShape> Life::getRectangles() {
    std::vector<sf::RectangleShape> rectangles;
    rectangles.push_back(m_rectangleBackground);
    rectangles.push_back(m_rectangleDisplayLife);
    return rectangles;
}