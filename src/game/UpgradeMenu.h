#ifndef UPGRADE_H
#define UPGRADE_H

#include <SFML/Graphics.hpp>
#include "../Button.h"
#include <iostream>
#include <memory>
#include <vector>

class UpgradeMenu {
    public:
        UpgradeMenu(const sf::Vector2f &playerPosition, const float &playerMovementSpeed, const float &bulletSpeed, const float &bulletCooldown,
                    const float &bulletDamage, const float &playerMaxLife, const float &heartLifeRefill);
        void updateUpgradeValues(const int &i, const float &playerMovementSpeed, const float &bulletSpeed, const float &bulletCooldown,
                    const float &bulletDamage, const float &playerMaxLife, const float &heartLifeRefill);
        void update(const sf::Vector2f &playerPosition);

        sf::RectangleShape getUpgradeMenuBackground();
        std::vector<std::shared_ptr<Button>> getButtons();
        std::vector<sf::RectangleShape> getButtonRectangles();
        std::vector<sf::Text> getButtonTexts();
        std::vector<sf::Text> getTitleTexts();

        void setCoinAmount(const int &coinAmount);
        sf::Text getCoinAmountText();
    private:
        void updateVars(const sf::Vector2f &playerPosition);

        sf::RectangleShape m_menuRectangleBackground;
        sf::Font m_font;

        sf::Text m_coinAmountText;

        float m_playerMovementSpeed;
        float m_bulletSpeed;
        float m_bulletCooldown;
        float m_bulletDamage;
        float m_playerMaxLife;
        float m_heartLifeRefill;

        float m_playerMovementSpeedPrice;
        float m_bulletSpeedPrice;
        float m_bulletCooldownPrice;
        float m_bulletDamagePrice;
        float m_playerMaxLifePrice;
        float m_heartLifeRefillPrice;

        std::vector<std::shared_ptr<Button>> m_buttons;

        std::vector<sf::RectangleShape> m_buttonRectangles;
        //sf::RectangleShape m_buttonRectangles[6];

        std::vector<sf::Text> m_buttonTexts;
        //sf::Text m_buttonTexts[6];

        std::vector<sf::Text> m_titleTexts;
        //sf::Text m_titleTexts[6];

        std::vector<int> m_prices;
        //int m_prices[6];
};

#endif