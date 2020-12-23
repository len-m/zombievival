#include "Inventory.h"
/**
 * @brief Construct a new Inventory object
 * 
 * @param trapTexture texture of trap
 * @param itemAmountFont font of the number that holds the number of items the player currently possesses
 */
Inventory::Inventory(const sf::Texture &trapTexture, const sf::Font &itemAmountFont) {
    m_trapAmount = 0;
    m_trapSprite.setTexture(trapTexture);
    m_trapSprite.setOrigin(m_trapSprite.getGlobalBounds().width / 2.f, m_trapSprite.getGlobalBounds().height / 2.f);
    m_trapSprite.setScale(5.f, 5.f);

    m_trapAmountText.setString("0");
    m_trapAmountText.setFont(itemAmountFont);
    m_trapAmountText.setCharacterSize(25);
    m_trapAmountText.setStyle(sf::Text::Bold);
    m_trapAmountText.setOrigin(m_trapAmountText.getGlobalBounds().width / 2.f, m_trapAmountText.getGlobalBounds().height / 2.f);
    m_trapAmountText.setFillColor(sf::Color(255.f, 102.f, 102.f, 170.f));

}

/**
 * @brief updates the inventory position
 * 
 * @param playerPosition 
 */
void Inventory::update(const sf::Vector2f &playerPosition) {
    m_trapSprite.setPosition(playerPosition.x - 400.f, playerPosition.y + 400.f);
    m_trapAmountText.setPosition(m_trapSprite.getPosition().x, m_trapSprite.getPosition().y + 50.f);
}

/**
 * @brief sets the amount of traps
 * 
 * @param trapAmount 
 */
void Inventory::setTrapAmount(const int &trapAmount) {
    m_trapAmount = trapAmount;
    m_trapAmountText.setString(std::to_string(trapAmount));
}

/**
 * @brief returns the amount of traps the player has
 * 
 * @return int 
 */
int Inventory::getTrapAmount() {
    return m_trapAmount;
}

/**
 * @brief returns the sprite of the trap
 * 
 * @return sf::Sprite 
 */
sf::Sprite Inventory::getTrapSprite() {
    return m_trapSprite;
}

/**
 * @brief returns the text that represents the amount of traps the player has
 * 
 * @return sf::Text 
 */
sf::Text Inventory::getTrapText() {
    return m_trapAmountText;
}

