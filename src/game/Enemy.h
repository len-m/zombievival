#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <Math.h>
#include "Life.h"

class Enemy {
    public:
        Enemy(const sf::Vector2f &spawnPosition, const sf::Texture &texture, const float &maxLife, const int &type);
        sf::Sprite getSprite();
        sf::Vector2f getPosition();
        void move(const sf::Vector2f &speed, const float &deltaTime);
        void setRotation(const float &angle);
        float getAngle();
        void setAngle(const float &angle);
        float getCurrentLife();
        void setCurrentLife(const float &currentLife);
        void updateLife();
        std::vector<sf::RectangleShape> getLifeRectangles();
        void setCanMove(const bool &canMove);
        bool getCanMove();
        void setIsTrapped(const bool &isTrapped);
        bool getIsTapped();
        int getType();
    private:
        int m_type;
        bool m_isTrapped;
        bool m_canMove;
        std::shared_ptr<Life> m_life;
        sf::Texture m_texture;
        float m_angle;
        float m_maxLife;
        float m_currentLife;
        sf::Sprite m_sprite;
        sf::Vector2f m_spawnPosition;
}; 

#endif