#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>

class Inventory {
    public:
        Inventory(const sf::Texture &trapTexture, const sf::Font &itemAmountFont);
        void update(const sf::Vector2f &playerPosition);
        void setTrapAmount(const int &trapAmount);
        int getTrapAmount();
        sf::Sprite getTrapSprite();
        sf::Text getTrapText();
    private:
        int m_spots;
        int m_trapAmount;
        sf::Sprite m_trapSprite;
        sf::Text m_trapAmountText;
};

#endif