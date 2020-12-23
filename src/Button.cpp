#include "Button.h"
/**
 * @brief Construct a new Button object
 * 
 * @param position
 * @param size
 * @param buttonColor 
 * @param textColor 
 * @param fontSize 
 * @param content 
 * @param font
 */
Button::Button(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &buttonColor,
               const sf::Color &textColor, const int &fontSize, const std::string &content, const sf::Font &font) {
    m_position = position;
    m_size = size;
    m_buttonColor = buttonColor;
    m_textColor = textColor;
    m_font = font;
    m_fontSize = fontSize;

    m_rectangle.setSize(sf::Vector2f(m_size.x, m_size.y));
    m_rectangle.setPosition(m_position.x, m_position.y);
    m_rectangle.setFillColor(m_buttonColor);

    m_text.setString(content);
    m_text.setFont(m_font);
    m_text.setCharacterSize(m_fontSize);
    m_text.setStyle(sf::Text::Bold);
    m_text.setFillColor(m_textColor);
    m_text.setPosition((m_position.x + (m_size.x / 2.f)) - (m_text.getGlobalBounds().width / 2.f), (m_position.y + (m_size.y / 2.f)) - (m_text.getGlobalBounds().height / 2.f));
}

/**
 * @brief returns the box of button
 * 
 * @return sf::RectangleShape 
 */
sf::RectangleShape Button::getRectangle() {
    return m_rectangle;
}

/**
 * @brief returns the text of button
 * 
 * @return sf::Text 
 */
sf::Text Button::getText() {
    return m_text;
}

/**
 * @brief sets button text
 * 
 * @param content 
 */
void Button::setContent(const std::string &content) {
    m_text.setString(content);
}

/**
 * @brief sets the position
 * 
 * @param position 
 */
void Button::setPosition(const sf::Vector2f &position) {
    m_position = position;
    m_rectangle.setPosition(m_position.x, m_position.y);
    m_text.setPosition((m_position.x + (m_size.x / 2.f)) - (m_text.getGlobalBounds().width / 2.f), (m_position.y + (m_size.y / 2.f)) - (m_text.getGlobalBounds().height / 1.f));
}

/**
 * @brief checks if the button is pressed, according to the mouse position 
 * 
 * @param mouseX X-coordinate of mouse position
 * @param mouseY Y-coordinate of mouse position
 * @return true if button is pressed
 * @returns false otherwise
 */
bool Button::isPressed(int mouseX, int mouseY) {
    if (mouseX >= m_position.x && mouseX <= m_position.x + m_size.x && mouseY >= m_position.y && mouseY <= m_position.y + m_size.y) {
        return true;
    } else {
        return false;
    }
}