#include "Player.h"
/**
 * @brief Construct a new Player object
 * 
 * @param maxLife the life that the player starts with
 */
Player::Player(const float &maxLife) {
    m_texture.loadFromFile("pics/player5.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
    m_sprite.setScale(5.f, 5.f);
    m_sprite.setPosition(0.f, 0.f);
    m_onKnockback = false;
    m_maxLife = maxLife;
    m_currentLife = m_maxLife;
    m_life.reset(new Life(m_currentLife, m_maxLife, sf::Vector2f(getPosition().x, getPosition().y + 450.f), sf::Vector2f(500.f, 50.f)));
}

/**
 * @brief move the player according to a speed and deltatime
 * 
 * @param speed 
 * @param deltaTime 
 */
void Player::move(const sf::Vector2f &speed, const float &deltaTime) {
    m_sprite.move(speed * deltaTime);
}

/**
 * @brief sets the rotation of the player sprite
 * 
 * @param angle 
 */
void Player::setRotation(const float &angle) {
    m_sprite.setRotation(angle);
}

/**
 * @brief gets the position of the player
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Player::getPosition() {
    return m_sprite.getPosition();
}

/**
 * @brief checks if player is currently being knockbacked or not
 * 
 * @return true, if yes
 * @return false otherwise
 */
bool Player::getOnKnockback() {
    return m_onKnockback;
}

/**
 * @brief sets the variable of m_onKnockback
 * 
 * @param onKnockback 
 */
void Player::setOnKnockback(const bool &onKnockback) {
    m_onKnockback = onKnockback;
}

/**
 * @brief return the angle the player should be knockbacked towards
 * 
 * @return float 
 */
float Player::getKnockbackAngle() {
    return m_knockbackAngle;
}

/**
 * @brief set the angle the player should be knockbacked towards
 * 
 * @param knockbackAngle 
 */
void Player::setKnockbackAngle(const float &knockbackAngle) {
    m_knockbackAngle = knockbackAngle;
}

/**
 * @brief returns the player sprite
 * 
 * @return sf::Sprite 
 */
sf::Sprite Player::getSprite() {
    return m_sprite;
}

/**
 * @brief updates the player life
 * 
 */
void Player::updateLife() {
    m_life->setCurrentLife(m_currentLife);
    m_life->setMaxLife(m_maxLife);
    m_life->setPosition(sf::Vector2f(getPosition().x, getPosition().y + 450.f));
    m_life->setLifeSize();
}

/**
 * @brief returns the life rectangles
 * 
 * @return std::vector<sf::RectangleShape> 
 */
std::vector<sf::RectangleShape> Player::getLifeRectangles() {
    std::vector<sf::RectangleShape> lifeRectangles = m_life->getRectangles();
    return lifeRectangles;
}

/**
 * @brief returns current life of player
 * 
 * @return float 
 */
float Player::getCurrentLife() {
    return m_currentLife;
}

/**
 * @brief sets current life of player to currentLife
 * 
 * @param currentLife 
 */
void Player::setCurrentLife(const float &currentLife) {
    m_currentLife = currentLife;
}

/**
 * @brief set max life of player to maxLife
 * 
 * @param maxLife 
 */
void Player::setMaxLife(const float &maxLife) {
    m_maxLife = maxLife;
}

/**
 * @brief returns max life of player
 * 
 * @return float 
 */
float Player::getMaxLife() {
    return m_maxLife;
}