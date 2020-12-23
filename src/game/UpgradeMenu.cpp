#include "UpgradeMenu.h"
/**
 * @brief Construct a new Upgrade Menu object
 * 
 * @param playerPosition position of player
 * @param playerMovementSpeed player movement speed
 * @param bulletSpeed speed of bullet
 * @param bulletCooldown cooldown of bullet
 * @param bulletDamage damage of bullet
 * @param playerMaxLife max life of player
 * @param heartLifeRefill amount of life a heart gives the player
 */
UpgradeMenu::UpgradeMenu(const sf::Vector2f &playerPosition, const float &playerMovementSpeed, const float &bulletSpeed, const float &bulletCooldown,
                         const float &bulletDamage, const float &playerMaxLife, const float &heartLifeRefill) {

    m_menuRectangleBackground.setSize(sf::Vector2f(200.f, 325.f));
    m_menuRectangleBackground.setPosition(playerPosition.x + 275.f, playerPosition.y + 150.f); //margin of 50.f from window border
    m_menuRectangleBackground.setFillColor(sf::Color(255.f, 230.f, 230.f, 170.f));

    m_font.loadFromFile("fonts/arial.ttf"); 
    m_playerMovementSpeed = playerMovementSpeed;
    m_bulletSpeed = bulletSpeed;
    m_bulletCooldown = bulletCooldown;
    m_bulletDamage = bulletDamage;
    m_playerMaxLife = playerMaxLife;
    m_heartLifeRefill = heartLifeRefill;

    for (int i = 0; i < 6; i++) {
        //create the buttons
        m_buttons.push_back(std::make_shared<Button>(sf::Vector2f(playerPosition.x + 400.f, playerPosition.y - 100.f), sf::Vector2f(40.f, 40.f), 
                                                     sf::Color(255.f, 102.f, 102.f, 170.f), sf::Color(255.f, 255.f, 255.f, 170.f), 17, "1", m_font));
        //init values, to prevent crashes
        sf::RectangleShape rect;
        sf::Text text;
        m_buttonRectangles.push_back(rect);
        m_titleTexts.push_back(text);
        m_buttonTexts.push_back(text);
        m_prices.push_back(1);

        //create the title text styles
        m_titleTexts[i].setFont(m_font);
        m_titleTexts[i].setCharacterSize(15);
        m_titleTexts[i].setStyle(sf::Text::Bold);
        m_titleTexts[i].setFillColor(sf::Color(255.f, 102.f, 102.f, 170.f));
    }

    m_titleTexts[0].setString("Movement Speed");
    m_titleTexts[1].setString("Bullet Speed");
    m_titleTexts[2].setString("Bullet Cooldown");
    m_titleTexts[3].setString("Bullet Damage");
    m_titleTexts[4].setString("Max Life");
    m_titleTexts[5].setString("Heart Health");

    m_coinAmountText.setString("Coins: 0");
    m_coinAmountText.setFont(m_font);
    m_coinAmountText.setCharacterSize(25);
    m_coinAmountText.setStyle(sf::Text::Bold);
    m_coinAmountText.setFillColor(sf::Color(255.f, 102.f, 102.f, 170.f));
    m_coinAmountText.setPosition(playerPosition.x + 400.f, playerPosition.y + 160.f);

    updateVars(playerPosition);
}

/**
 * @brief updates the positions of membervariables of the upgrademenu
 * 
 * @param playerPosition 
 */
void UpgradeMenu::updateVars(const sf::Vector2f &playerPosition) {
    for (int i = 0; i < 6; i++) {
        m_buttons[i]->setPosition(sf::Vector2f(playerPosition.x + 430.f, playerPosition.y + 205.f + ((float)(i) * 45.f)));
        m_buttonRectangles[i] = m_buttons[i]->getRectangle();
        m_buttonTexts[i] = m_buttons[i]->getText();
        m_titleTexts[i].setPosition(playerPosition.x + 280.f, playerPosition.y + 215.f + ((float)(i) * 45.f));
    }
    m_coinAmountText.setPosition(playerPosition.x + 320.f, playerPosition.y + 160.f);
}

/**
 * @brief sets the amount of coins
 * 
 * @param coinAmount 
 */
void UpgradeMenu::setCoinAmount(const int &coinAmount) {
    m_coinAmountText.setString("Coins: " + std::to_string(coinAmount));
}

/**
 * @brief updates the position of the upgrademenu
 * 
 * @param playerPosition 
 */
void UpgradeMenu::update(const sf::Vector2f &playerPosition) {
    //update position
    m_menuRectangleBackground.setPosition(playerPosition.x + 275.f, playerPosition.y + 150.f);
    updateVars(playerPosition);
}

/**
 * @brief updates upgradeOption variables
 * 
 * @param i the position of the variable to be upgraded in the vectors that hold the price and the buttons
 * @param playerMovementSpeed 
 * @param bulletSpeed 
 * @param bulletCooldown 
 * @param bulletDamage 
 * @param playerMaxLife 
 * @param heartLifeRefill 
 */
void UpgradeMenu::updateUpgradeValues(const int &i, const float &playerMovementSpeed, const float &bulletSpeed, const float &bulletCooldown,
                                      const float &bulletDamage, const float &playerMaxLife, const float &heartLifeRefill) {
    //update the price
    m_prices[i] *= 2;
    m_buttons[i]->setContent(std::to_string(m_prices[i]));

    //update vars
    m_playerMovementSpeed = playerMovementSpeed;
    m_bulletSpeed = bulletSpeed;
    m_bulletCooldown = bulletCooldown;
    m_bulletDamage = bulletDamage;
    m_playerMaxLife = playerMaxLife;
    m_heartLifeRefill = heartLifeRefill;
}

/**
 * @brief returns upgrade menu background
 * 
 * @return sf::RectangleShape 
 */
sf::RectangleShape UpgradeMenu::getUpgradeMenuBackground() {
    return m_menuRectangleBackground;
}

/**
 * @brief returns buttons
 * 
 * @return std::vector<std::shared_ptr<Button>> 
 */
std::vector<std::shared_ptr<Button>> UpgradeMenu::getButtons() {
    return m_buttons;
}

/**
 * @brief returns button rectangles
 * 
 * @return std::vector<sf::RectangleShape> 
 */
std::vector<sf::RectangleShape> UpgradeMenu::getButtonRectangles() {
    return m_buttonRectangles;
}

/**
 * @brief returns button texts
 * 
 * @return std::vector<sf::Text> 
 */
std::vector<sf::Text> UpgradeMenu::getButtonTexts() {
    return m_buttonTexts;
}

/**
 * @brief returns text of upgrade variables
 * 
 * @return std::vector<sf::Text> 
 */
std::vector<sf::Text> UpgradeMenu::getTitleTexts() {
    return m_titleTexts;
}

/**
 * @brief returns amount of coins text
 * 
 * @return sf::Text 
 */
sf::Text UpgradeMenu::getCoinAmountText() {
    return m_coinAmountText;
}