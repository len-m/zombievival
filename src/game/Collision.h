#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include <math.h>

class Collision {
    public:
        bool isCollidingSAT(const sf::Sprite& rectangle1, const sf::Sprite& rectangle2); //seperating axis theorem
        bool isCollidingAABB(const sf::Sprite& rectangle1, const sf::Sprite& rectangle2); //axis aligned bounding box
        bool isFullyCollidingAABB(const sf::Sprite &rectangle1, const sf::Sprite &rectangle2); //rectangle 2 is fully in rectangle 1
    private:
        float getVectorLength(const sf::Vector2f &vector, const sf::Vector2f &offset);
        float getDotProduct(const sf::Vector2f &vector1, const sf::Vector2f &vector2);
};

#endif