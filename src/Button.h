#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
    public:
        Button(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &buttonColor, 
               const sf::Color &textColor, const int &fontSize, const std::string &content, const sf::Font &font);
        bool isPressed(int mouseX, int mouseY);
        sf::RectangleShape getRectangle();
        void setContent(const std::string &content);
        sf::Text getText();
        void setPosition(const sf::Vector2f &position);
    private:
        sf::Font m_font;
        sf::Text m_text;
        sf::RectangleShape m_rectangle;
        sf::Vector2f m_position, m_size;
        sf::Color m_buttonColor;
        sf::Color m_textColor;
        int m_fontSize;
};

#endif