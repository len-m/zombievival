#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Life.h"
#include <memory>

class Player {
    public:
        Player(const float &maxLife);
        void move(const sf::Vector2f &speed, const float &deltaTime);
        void setRotation(const float &angle);
        sf::Sprite getSprite();
        sf::Vector2f getPosition();
        bool getOnKnockback();
        void setOnKnockback(const bool &onKnockback);
        void setKnockbackAngle(const float &knockbackAngle);
        float getKnockbackAngle();
        void updateLife();
        std::vector<sf::RectangleShape> getLifeRectangles();
        float getCurrentLife();
        void setCurrentLife(const float &currentLife);
        void setMaxLife(const float &maxLife);
        float getMaxLife();
    private:
        std::shared_ptr<Life> m_life;
        float m_maxLife;
        float m_currentLife;
        float m_knockbackAngle;
        bool m_onKnockback;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Vector2f m_position;
};

#endif