#include "Enemy.h"
/**
 * @brief Construct a new Enemy object
 * 
 * @param spawnPosition 
 * @param texture 
 * @param maxLife maximum life of enemy
 * @param type type of enemy
 */
Enemy::Enemy(const sf::Vector2f &spawnPosition, const sf::Texture &texture, const float &maxLife, const int &type) {
    m_texture = texture;
    m_type = type;
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
    m_sprite.setScale(5.f, 5.f);
    m_sprite.setPosition(spawnPosition);
    m_spawnPosition = spawnPosition;
    m_canMove = true;
    m_angle = 0.f;
    m_maxLife = maxLife;
    m_currentLife = m_maxLife;
    m_isTrapped = false;
    m_life.reset(new Life(m_currentLife, m_maxLife, sf::Vector2f(getPosition().x, getPosition().y - 50.f), sf::Vector2f(50.f, 10.f)));
}

/**
 * @brief returns type of enemy
 * 
 * @return int 
 */
int Enemy::getType() {
    return m_type;
}

/**
 * @brief moves the enemy according to deltatime and a speed
 * 
 * @param speed 
 * @param deltaTime 
 */
void Enemy::move(const sf::Vector2f &speed, const float &deltaTime) {
    m_sprite.move(speed * deltaTime);
}

/**
 * @brief gets the angle that the enemy is looking towards
 * 
 * @return float 
 */
float Enemy::getAngle() {
    return m_angle;
}

/**
 * @brief sets the angle variable
 * 
 * @param angle 
 */
void Enemy::setAngle(const float &angle) {
    m_angle = angle;
}

/**
 * @brief rotates the enemy according to an angle
 * 
 * @param angle 
 */
void Enemy::setRotation(const float &angle) {
    m_sprite.setRotation(angle);
}

/**
 * @brief updates the life of the enemy
 * 
 */
void Enemy::updateLife() {
    m_life->setCurrentLife(m_currentLife);
    m_life->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
    m_life->setLifeSize();
}

/**
 * @brief returns a vector of the sf::RectangleShapes that represent the life of the enemy 
 * 
 * @return std::vector<sf::RectangleShape> 
 */
std::vector<sf::RectangleShape> Enemy::getLifeRectangles() {
    std::vector<sf::RectangleShape> lifeRectangles = m_life->getRectangles();
    return lifeRectangles;
}

/**
 * @brief returns the position
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Enemy::getPosition() {
    return m_sprite.getPosition();
}

/**
 * @brief returns the sprite
 * 
 * @return sf::Sprite 
 */
sf::Sprite Enemy::getSprite() {
    return m_sprite;
}

/**
 * @brief returns the current life
 * 
 * @return float 
 */
float Enemy::getCurrentLife() {
    return m_currentLife;
}

/**
 * @brief sets the current life
 * 
 * @param currentLife 
 */
void Enemy::setCurrentLife(const float &currentLife) {
    m_currentLife = currentLife;
}

/**
 * @brief sets the m_canMove variable
 * 
 * @param canMove 
 */
void Enemy::setCanMove(const bool &canMove) {
    m_canMove = canMove;
}

/**
 * @brief gets the m_canMove variable
 * 
 * @return true, if m_canMove is true
 * @return false otherwise
 */
bool Enemy::getCanMove() {
    return m_canMove;
}

/**
 * @brief sets the m_isTrapped variable 
 * 
 * @param isTrapped 
 */
void Enemy::setIsTrapped(const bool &isTrapped) {
    m_isTrapped = isTrapped;
}

/**
 * @brief returns the value of the m_getIsTrapped variable
 * 
 * @return true 
 * @return false 
 */
bool Enemy::getIsTapped() {
    return m_isTrapped;
}