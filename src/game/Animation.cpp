#include "Animation.h"
/**
 * @brief Construct a new Animation object
 * 
 * @param texture spritesheet to be animated
 * @param spriteSize size of each sprite in the spritesheet
 * @param animationTime the time to wait in seconds inbetween every sprite
 * @param animationWait the time to wait in seconds after a full animation cycle
 * @param currentTime the amount of time that the game class has been running in seconds
 */
Animation::Animation(const sf::Texture &texture, const sf::Vector2i &spriteSize, const float &animationTime, const float &animationWait, const float &currentTime) {
    m_texture = texture;
    m_spriteSize = spriteSize;
    m_spriteRect = sf::IntRect(0, 0, m_spriteSize.x, m_spriteSize.y);
    m_animationTime = animationTime;
    m_animationWait = animationWait;
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(m_spriteRect);
    m_timePassed = currentTime;
}

/**
 * @brief return the current sprite
 * 
 * @return sf::Sprite 
 */
sf::Sprite Animation::getSprite() {
    return m_sprite;
}

/**
 * @brief updates the current sprite
 * 
 * @param currentTime 
 */
void Animation::update(const float &currentTime) {
    //move the spriteRect
    if (currentTime >= m_timePassed) {
        if (m_spriteRect.left + m_spriteSize.x == m_texture.getSize().x) {
            //check if end of column aswell
            if (m_spriteRect.top + m_spriteSize.y == m_texture.getSize().y) {
                //go to first sprite
                m_spriteRect = sf::IntRect(0, 0, m_spriteSize.x, m_spriteSize.y);
                m_timePassed = currentTime + m_animationWait;
            } else {
                //go to start of next line
                m_spriteRect = sf::IntRect(0, m_spriteRect.top + m_spriteSize.y, m_spriteSize.x, m_spriteSize.y);
                m_timePassed = currentTime + m_animationTime;
            }
        } else {
            //move to next position
            m_spriteRect = sf::IntRect(m_spriteRect.left + m_spriteSize.x, m_spriteRect.top, m_spriteSize.x, m_spriteSize.y);
            m_timePassed = currentTime + m_animationTime;
        }
    }
    m_sprite.setTextureRect(m_spriteRect);
}