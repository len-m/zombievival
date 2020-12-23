#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <math.h>

class Bullet {
    public:
        Bullet(const sf::Vector2f &speed, const float &rotation, const sf::Texture &texture);
        void setBulletPos(const sf::Vector2f &newBulletPos);
        sf::Vector2f getPosition();
        sf::Sprite getSprite();
        void move(const float &deltaTime);
    private:
        sf::Texture m_texture;
        sf::Vector2f m_lifetime;
        sf::Vector2f m_position;
        sf::Vector2f m_speed;
        sf::Sprite m_sprite;
};

#endif