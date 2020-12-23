#include "Trap.h"
/**
 * @brief Construct a new Trap object
 * 
 * @param trapTexture texture of trap when placed
 * @param outlineTexture texture of trap before placed
 * @param currentTime the amount of time that the game class has been running in seconds
 */
Trap::Trap(const sf::Texture &trapTexture, const sf::Texture &outlineTexture, const float &currentTime) {
    m_isTrap = false;

    //sprite
    m_sprite.setTexture(outlineTexture);
    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
    m_sprite.setScale(8.f, 8.f);

    //animation
    m_animation.reset(new Animation(trapTexture, sf::Vector2i(33, 33), 0.05f, 2.f, currentTime));

    //life
    m_life.reset(new Life(100.f, 100.f, m_sprite.getPosition(), sf::Vector2f(100.f, 20.f)));
    m_currentLife = 100.f;
}

/**
 * @brief return trap sprite
 * 
 * @return sf::Sprite 
 */
sf::Sprite Trap::getSprite() {
    if (m_isTrap) {
        m_sprite = m_animation->getSprite();

        m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
        m_sprite.scale(8.f, 8.f);
        m_sprite.setPosition(m_position);
    }

    return m_sprite;
}

/**
 * @brief update animation of sprite according to currentTime
 * 
 * @param currentTime 
 */
void Trap::updateAnimation(const float &currentTime) {
    m_animation->update(currentTime);
}

/**
 * @brief sets an outline trap to be a placed trap
 * 
 */
void Trap::setTrap() {
    m_isTrap = true;
    m_sprite = m_animation->getSprite();
    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
    m_sprite.setScale(8.f, 8.f);
}

/**
 * @brief sets the current life of the trap
 * 
 * @param currentLife 
 */
void Trap::setCurrentLife(const float &currentLife) {
    m_currentLife = currentLife;
    m_life->setCurrentLife(currentLife);
    m_life->setLifeSize();
}

/**
 * @brief returns the current life of the trap
 * 
 * @return float 
 */
float Trap::getCurrentLife() {
    return m_currentLife;
}

/**
 * @brief returns what type of trap it is
 * 
 * @return true, if a placed trap
 * @return false, if an outline trap
 */
bool Trap::getIsTrap() {
    return m_isTrap;
}

/**
 * @brief set the position of the trap
 * 
 * @param position 
 */
void Trap::setPosition(const sf::Vector2f &position) {
    m_position = position;
    if (m_isTrap == false) {
        m_sprite.setPosition(m_position);
    }
    m_life->setPosition(m_position);
    
}

/**
 * @brief returns a vector of enemies trapped in trap
 * 
 * @return std::vector<std::shared_ptr<Enemy>> 
 */
std::vector<std::shared_ptr<Enemy>> Trap::getAlreadyTrappedEnemies() {
    return m_alreadyTrapped;
}

/**
 * @brief adds an enemy to the vector of trapped enemies
 * 
 * @param enemy 
 */
void Trap::addTrappedEnemy(std::shared_ptr<Enemy> &enemy) {
    m_alreadyTrapped.push_back(enemy);
}

/**
 * @brief checks if an enemy is trapped
 * 
 * @param enemy 
 * @return true, if enemy is trapped by this trap
 * @return false, if enemy is not trapped by this trap
 */
bool Trap::isAlreadyTrapped(std::shared_ptr<Enemy> &enemy) {
    if (m_alreadyTrapped.size() > 0) {
        for (int i = 0; i < m_alreadyTrapped.size(); i++) {
            if (m_alreadyTrapped[i] == enemy) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief returns the vector of the life rectangles
 * 
 * @return std::vector<sf::RectangleShape> 
 */
std::vector<sf::RectangleShape> Trap::getLifeRectangles() {
    std::vector<sf::RectangleShape> lifeRectangles = m_life->getRectangles();
    return lifeRectangles;
}