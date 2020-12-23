#ifndef LIFE_H
#define LIFE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Life {
    public:
        Life(const float &currentLife, const float &maxLife, const sf::Vector2f &position, const sf::Vector2f &size);
        void setCurrentLife(const float &currentLife);
        void setMaxLife(const float &maxLife);
        void setPosition(const sf::Vector2f &position);
        void setLifeSize();
        std::vector<sf::RectangleShape> getRectangles();
    private:
        sf::RectangleShape m_rectangleBackground;
        sf::RectangleShape m_rectangleDisplayLife; //this rectangle is displayed on top of the other one
        float m_currentLife;
        float m_maxLife;

};

#endif