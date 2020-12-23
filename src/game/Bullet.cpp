#include "Bullet.h"
/**
 * @brief Construct a new Bullet object
 * 
 * @param speed
 * @param rotation 
 * @param texture 
 */
Bullet::Bullet(const sf::Vector2f &speed, const float &rotation, const sf::Texture &texture) {
    //create the sprite
    m_texture = texture;
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
    m_sprite.setRotation(rotation);
    m_sprite.setPosition(0.f, 0.f);
    m_speed = speed;
}

/**
 * @brief moves the bullet according to deltatime
 * 
 * @param deltaTime 
 */
void Bullet::move(const float &deltaTime) {
    m_sprite.move(m_speed * deltaTime);
}

/**
 * @brief sets the bullet position
 * 
 * @param newBulletPos 
 */
void Bullet::setBulletPos(const sf::Vector2f &newBulletPos) {
    m_sprite.setPosition(newBulletPos);
}

/**
 * @brief returns the bullet position
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Bullet::getPosition() {
    return m_sprite.getPosition();
}

/**
 * @brief returns the sprite
 * 
 * @return sf::Sprite 
 */
sf::Sprite Bullet::getSprite() {
    return m_sprite;
}