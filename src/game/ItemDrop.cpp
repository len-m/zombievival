#include "ItemDrop.h"
/**
 * @brief Construct a new Item Drop object
 * 
 * @param texture spritesheet to be animated
 * @param spriteSize size of each sprite in the spritesheet
 * @param position position of the item drop
 * @param currentTime the current time that the game class has been running
 * @param animationTime the time to wait in seconds inbetween every sprite
 * @param animationWait the time to wait in seconds after a full animation cycle
 */
ItemDrop::ItemDrop(const sf::Texture &texture, const sf::Vector2i &spriteSize, const sf::Vector2f &position, const float &currentTime, const float &animationTime, const float &animationWait) {
    m_position = position;
    m_animation.reset(new Animation(texture, spriteSize, animationTime, animationWait, currentTime));
    m_sprite = m_animation->getSprite();

    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
    m_sprite.scale(4.f, 4.f);
    m_sprite.setPosition(m_position);
}

/**
 * @brief updates the animation
 * 
 * @param currentTime 
 */
void ItemDrop::update(const float &currentTime) {
    m_animation->update(currentTime);
}

/**
 * @brief returns the animated sprite
 * 
 * @return sf::Sprite 
 */
sf::Sprite ItemDrop::getSprite() {
    m_sprite = m_animation->getSprite();

    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
    m_sprite.scale(4.f, 4.f);
    m_sprite.setPosition(m_position);

    return m_sprite;
}

ItemDrop::~ItemDrop() {

}