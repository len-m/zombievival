#ifndef Trap_H
#define Trap_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Animation.h"

class Trap {
    public:
        Trap(const sf::Texture &trapTexture, const sf::Texture &outlineTexture, const float &currentTime);
        sf::Sprite getSprite();
        void setTrap();
        bool getIsTrap();
        void setPosition(const sf::Vector2f &position);
        std::vector<std::shared_ptr<Enemy>> getAlreadyTrappedEnemies();
        void addTrappedEnemy(std::shared_ptr<Enemy> &enemy);
        bool isAlreadyTrapped(std::shared_ptr<Enemy> &enemy);
        void updateAnimation(const float &currentTime);
        std::vector<sf::RectangleShape> getLifeRectangles();
        void setCurrentLife(const float &currentLife);
        float getCurrentLife();
    private:
        std::vector<std::shared_ptr<Enemy>> m_alreadyTrapped;
        sf::Sprite m_sprite;
        sf::Texture m_trapTexture;
        bool m_isTrap; //not trap at first, only outline
        std::unique_ptr<Animation> m_animation;
        sf::Vector2f m_position;
        std::unique_ptr<Life> m_life;
        float m_currentLife;
};

#endif