#ifndef ITEMDROP_H
#define ITEMDROP_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <memory>

class ItemDrop {
    public:
        ItemDrop(const sf::Texture &texture, const sf::Vector2i &spriteSize, const sf::Vector2f &position, const float &currentTime, const float &animationTime, const float &animationWait);
        ~ItemDrop();
        sf::Sprite getSprite();
        void update(const float &currentTime);
    private:
        std::shared_ptr<Animation> m_animation;
        sf::Vector2f m_position;
        sf::Sprite m_sprite;
};

#endif