#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation {
    public:
        Animation(const sf::Texture &texture, const sf::Vector2i &spriteSize, const float &animationTime, const float &animationWait, const float &currentTime);
        sf::Sprite getSprite();
        void update(const float &currentTime);
    private:
        float m_timePassed;
        sf::Sprite m_sprite;
        sf::IntRect m_spriteRect;
        sf::Texture m_texture;
        sf::Vector2i m_spriteSize;
        float m_animationTime; //the time every sprite has
        float m_animationWait; //waiting after whole animation
};

#endif