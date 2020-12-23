#include "Game.h"
/**
 * @brief Construct a new Game object
 * 
 * @param window is the window created in the engine class
 */
Game::Game(sf::RenderWindow *window) {

    //window, gamestate
    m_window = window;
    m_isActive = false;

    //initialise textures here
    resourceManager.setTexture("enemyNormal", "pics/zombie2.png");
    resourceManager.setTexture("enemyBig", "pics/zombie3.png");
    resourceManager.setTexture("bullet", "pics/bullet2.png");
    resourceManager.setTexture("cursor", "pics/crosshair4.png");
    resourceManager.setTexture("background1", "pics/bg5.png");
    resourceManager.setTexture("background2", "pics/bg6.png");
    resourceManager.setTexture("heartItemDrop", "pics/heartAnimation2.png");
    resourceManager.setTexture("coinItemDrop", "pics/coinAnimation.png");
    resourceManager.setTexture("trapItemDrop", "pics/ItemDropWall.png");
    resourceManager.setTexture("trapPlaced", "pics/trapAnimation2.png");
    resourceManager.setTexture("trapOutline", "pics/WallOutline.png");

    //init fonts
    resourceManager.setFont("arial", "fonts/arial.ttf");
    resourceManager.setFont("8bitwonder", "fonts/8bitwonder.ttf");
    resourceManager.setFont("rainyhearts", "fonts/rainyhearts.ttf");

    //init sound
    resourceManager.setSound("shoot", "sounds/shoot.wav");
    resourceManager.setSound("enemyhit", "sounds/zombiehit.wav");
    resourceManager.setSound("playerhit", "sounds/playerhit.wav");

    shootSound.setBuffer(*resourceManager.getSound("shoot"));
    enemyHit.setBuffer(*resourceManager.getSound("enemyhit"));
    playerHit.setBuffer(*resourceManager.getSound("playerhit"));

    m_backgroundTextures.push_back(*resourceManager.getTexture("background1"));
    m_backgroundTextures.push_back(*resourceManager.getTexture("background2"));

    //cursor        
    m_cursor.setTexture(*resourceManager.getTexture("cursor"));        
    m_cursor.setOrigin(m_cursor.getGlobalBounds().width / 2.f, m_cursor.getGlobalBounds().height / 2.f);
    m_cursor.setScale(1.5f, 1.5f);

    //score
    m_score = 0;

    m_scoreText.setString("Score: " + std::to_string((int)m_score));
    m_scoreText.setFont(*resourceManager.getFont("rainyhearts"));
    m_scoreText.setCharacterSize(50);
    m_scoreText.setStyle(sf::Text::Bold);
    m_scoreText.setFillColor(sf::Color(255.f, 255.f, 255.f, 170.f));
    m_scoreText.setOrigin(sf::Vector2f(m_scoreText.getGlobalBounds().width / 2.f, m_scoreText.getGlobalBounds().height / 2.f));

    //game over
    m_gameOverText.setString("Game Over");
    m_gameOverText.setFont(*resourceManager.getFont("8bitwonder"));
    m_gameOverText.setCharacterSize(70);
    m_gameOverText.setStyle(sf::Text::Bold);
    m_gameOverText.setFillColor(sf::Color(255.f, 255.f, 255.f, 170.f));
    m_gameOverText.setOrigin(sf::Vector2f(m_gameOverText.getGlobalBounds().width / 2.f, m_gameOverText.getGlobalBounds().height / 2.f));

    //pause
    m_isPausedText.setString("Pause");
    m_isPausedText.setFont(*resourceManager.getFont("8bitwonder"));
    m_isPausedText.setCharacterSize(70);
    m_isPausedText.setStyle(sf::Text::Bold);
    m_isPausedText.setFillColor(sf::Color(255.f, 255.f, 255.f, 170.f));
    m_isPausedText.setOrigin(sf::Vector2f(m_isPausedText.getGlobalBounds().width / 2.f, m_isPausedText.getGlobalBounds().height / 2.f));

    //initialize in constructor, to prevent crashes
    m_cursorWorldPosition = sf::Vector2f(0.f, 0.f);
    m_onBulletCooldown = false;
    m_enemySpawnCountDifference = 0.f;
    m_coinAmount = 0;
    m_enemiesSpawnedCount = 0;
    m_onWaveCooldown = true;
    m_drawWaveText = true;
    m_hasTrap = false;
    m_playerFiredLastFrame = false;
    m_bulletSpawnAmountRest = 0.f;
    m_dead = false;
    m_knockbackStartingPosition = sf::Vector2f(0.f, 0.f);
    m_wave = 1;
    m_isPaused = false;

    //vars to play around with
    //player
    m_movementSpeed = 100.f;
    m_bulletSpeed = 300.f;
    m_bulletCooldown = 1.f;
    m_bulletLifetime = 1000.f;
    m_bulletDamage = 25.f;
    m_playerMaxLife = 200.f;

    //chunks
    m_chunkLength = 1000.f;
    m_numberOfTilesPerChunk = 25; // only sqrt 2 numbers

    //enemy spawning
    m_enemySpawnRate = 2.f;
    m_enemySpawnRadius = 800.f;
    m_enemyMoveFactor = 100.f; //if enemy gets same spawn coordinates as other enemy, move it further

    //item drops
    m_itemDropSpawnRate = 3; //needs to be element from natural numbers
    m_heartLifeRefill = 20.f;

    //traps
    m_trapUseDamage = 50.f;

    //enemy
    m_knockbackMovementSpeed = 250.f;
    m_knockbackLength = 50.f;
    m_trappedTime = 2.f;
    m_enemyMaxDistanceFromPlayer = m_bulletLifetime; //should be greater than m_enemySpawnRadius

    //wave stuff
    m_enemyNormalMovementSpeed = 50.f;
    m_enemyNormalMaxLife = 100.f;
    m_enemyNormalDamage = 20.f;

    m_enemyTankMovementSpeed = 30.f;
    m_enemyTankMaxLife = 200.f;
    m_enemyTankDamage = 40.f;

    m_maxAllowedAliveEnemies = 5;
    m_waveCooldownLength = 3.f;
    m_enemiesTotalToBeSpawnedInWave = 10; //how many to spawn in first wave

    m_waveText.setFont(*resourceManager.getFont("8bitwonder"));
    m_waveText.setCharacterSize(70);
    m_waveText.setString("Wave " + std::to_string(m_wave));
    m_waveText.setOrigin(m_waveText.getGlobalBounds().width / 2.f, m_waveText.getGlobalBounds().height / 2.f);
    m_waveText.setFillColor(sf::Color(255.f, 255.f, 255.f, 170.f));
    m_waveText.setStyle(sf::Text::Bold);
        
    //create objects
    m_player.reset(new Player(m_playerMaxLife));
    m_upgradeMenu.reset(new UpgradeMenu(m_player->getPosition(), m_movementSpeed, m_bulletSpeed, m_bulletCooldown, m_bulletDamage, m_playerMaxLife, m_heartLifeRefill));
    m_inventory.reset(new Inventory(*resourceManager.getTexture("trapItemDrop"), *resourceManager.getFont("arial")));
        
    //field
    float fieldLength = 20000.f;
    m_field.setSize(sf::Vector2f(fieldLength, fieldLength));
    m_field.setOrigin(m_field.getGlobalBounds().width / 2.f, m_field.getGlobalBounds().height / 2.f);
    m_field.setPosition(sf::Vector2f(0.f, 0.f));

    m_borderLeft.setSize(sf::Vector2f(500.f, fieldLength + 500.f));
    m_borderTop.setSize(sf::Vector2f(fieldLength + 500.f, 500.f));
    m_borderRight.setSize(sf::Vector2f(500.f, fieldLength + 500.f));
    m_borderBottom.setSize(sf::Vector2f(fieldLength + 500.f, 500.f));

    m_borderLeft.setOrigin(m_borderLeft.getGlobalBounds().left + m_borderLeft.getGlobalBounds().width, m_borderLeft.getGlobalBounds().top);
    m_borderTop.setOrigin(m_borderTop.getGlobalBounds().left + m_borderTop.getGlobalBounds().width, m_borderTop.getGlobalBounds().top + m_borderTop.getGlobalBounds().height);
    m_borderRight.setOrigin(m_borderRight.getGlobalBounds().left, m_borderRight.getGlobalBounds().top + m_borderRight.getGlobalBounds().height);
    //m_borderBottom default origin is correct

    m_borderLeft.setPosition(m_field.getPosition().x - (fieldLength / 2.f), m_field.getPosition().y - (fieldLength / 2.f));
    m_borderTop.setPosition(m_field.getPosition().x + (fieldLength / 2.f), m_field.getPosition().y - (fieldLength / 2.f));
    m_borderRight.setPosition(m_field.getPosition().x + (fieldLength / 2.f), m_field.getPosition().y + (fieldLength / 2.f));
    m_borderBottom.setPosition(m_field.getPosition().x - (fieldLength / 2.f), m_field.getPosition().y + (fieldLength / 2.f));

    m_borderLeft.setFillColor(sf::Color(25.f, 25.f, 25.f, 255.f));
    m_borderTop.setFillColor(sf::Color(25.f, 25.f, 25.f, 255.f));
    m_borderRight.setFillColor(sf::Color(25.f, 25.f, 25.f, 255.f));
    m_borderBottom.setFillColor(sf::Color(25.f, 25.f, 25.f, 255.f));
}
/**
 * @brief gets the length of a vector minus an offset of another vector
 * note: all vectors have a length of two
 * 
 * @param vector 
 * @param offset 
 * @return float 
 */
float Game::getVectorLength(const sf::Vector2f &vector, const sf::Vector2f &offset) {
    return sqrt(pow(vector.x - offset.x, 2) + pow(vector.y - offset.y, 2));
}

/**
 * @brief returns if the player is dead
 * 
 * @return true, if player is dead
 * @return false otherwise
 */
bool Game::getIsDead() {
    return m_dead;
}

/**
 * @brief moves the player back into the field
 * 
 * @param deltaTime 
 */
void Game::moveOutOfBorder(const float &deltaTime) {
    while (m_player->getSprite().getGlobalBounds().intersects(m_borderLeft.getGlobalBounds())) {
    m_player->move(sf::Vector2f(50.f, 0.f), deltaTime); 
    }
    while (m_player->getSprite().getGlobalBounds().intersects(m_borderTop.getGlobalBounds())) {
        m_player->move(sf::Vector2f(0.f, 50.f), deltaTime); 
    }
    while (m_player->getSprite().getGlobalBounds().intersects(m_borderRight.getGlobalBounds())) {
        m_player->move(sf::Vector2f(-50.f, 0.f), deltaTime); 
    }
    while (m_player->getSprite().getGlobalBounds().intersects(m_borderBottom.getGlobalBounds())) {
        m_player->move(sf::Vector2f(0.f, -50.f), deltaTime); 
    }

}

/**
 * @brief moves tthe player according to a speed and deltatime
 * 
 * @param movement 
 * @param deltaTime 
 */
void Game::move(const sf::Vector2f &movement, const float &deltaTime) {
    //create copy of player, move copied player
    std::shared_ptr<Player> playerCopy = std::make_shared<Player>(*m_player);
    playerCopy->move(movement, deltaTime);
    //AABB collision is enough
    if (!playerCopy->getSprite().getGlobalBounds().intersects(m_borderTop.getGlobalBounds())) {
        m_player->move(movement, deltaTime);
    } else {
        //move the player into the wall, and then out again
        m_player->move(movement, deltaTime);
        moveOutOfBorder(deltaTime);
    }
}

/**
 * @brief shoots a bullet
 * 
 */
void Game::shoot() {
    sf::Vector2f distance = m_cursorWorldPosition - m_player->getPosition();
    float angle = atan2(distance.y, distance.x);
    //bulletMovement creates a vector from a given angle, which, when adding up the x and y coordinates adds up too 1
    //this vector can then be used in the sfml move function, but you can also increase the speed by multiplying the vector by a float variable
    sf::Vector2f bulletMovement(m_bulletSpeed * cos(angle), m_bulletSpeed * sin(angle));

    int bulletAmount;
    if (m_playerFiredLastFrame) {
        //this is only bigger than one, if there is no frame, that resets the cooldownClock, which means its dependant on deltatime
        bulletAmount = (int)(m_bulletCooldownClock.getElapsedTime().asSeconds() / m_bulletCooldown);
    } else {
        bulletAmount = 1;
    }

    for (int i = 0; i < bulletAmount; i++) {
        //create a new bullet object
        std::shared_ptr<Bullet> bullet(new Bullet(bulletMovement, (angle * 180.f / 3.1415f) + 90.f, *resourceManager.getTexture("bullet")));

        bullet->setBulletPos(sf::Vector2f(
            m_player->getPosition().x + (cos(angle) * 42.f + cos(angle) * i * m_bulletSpeed * m_bulletCooldown),
            m_player->getPosition().y + (sin(angle) * 42.f + sin(angle) * i * m_bulletSpeed * m_bulletCooldown)
        ));

        m_bulletVector.push_back(bullet);
        shootSound.play();
    }

    //bullet cooldown
    m_bulletCooldownClock.restart();
    m_onBulletCooldown = true;
    m_playerFiredLastFrame = true;
}

/**
 * @brief the upgradeType variable gets multiplied or divided by a specific amount
 * 
 * @param upgradeType variable to get upgraded
 * @param multiply wether to multiply or divide
 * @param amount by what amount to upgrade the upgradeType
 * @param i what position the upgradeType variable represents in the upgradeMenu vector that stores all these values
 */
void Game::upgrade(float *upgradeType, const bool &multiply, const float &amount, const int &i) {
    if (m_coinAmount >= std::stoi(std::string(m_upgradeMenu->getButtons()[i]->getText().getString()))) {
        m_coinAmount = m_coinAmount - std::stoi(std::string(m_upgradeMenu->getButtons()[i]->getText().getString()));
        m_upgradeMenu->updateUpgradeValues(i, m_movementSpeed, m_bulletSpeed, m_bulletCooldown, m_bulletDamage, m_playerMaxLife, m_heartLifeRefill);
        if (multiply) {
            *upgradeType *= amount;
        } else {
            *upgradeType /= amount;
        }
    }
}

/**
 * @brief takes trap from inventory and shows player where it would be placed as a blueprint
 * 
 */
void Game::takeTrap() {
    if (m_hasTrap == false && m_inventory->getTrapAmount() > 0) {
        //create trap
        m_inventory->setTrapAmount(m_inventory->getTrapAmount() - 1);
        std::shared_ptr<Trap> trap(new Trap(*resourceManager.getTexture("trapPlaced"), *resourceManager.getTexture("trapOutline"), m_gametime.getElapsedTime().asSeconds()));
        m_trapVector.push_back(trap);
        m_hasTrap = true;
    }
}

/**
 * @brief trap gets placed at cursor position
 * 
 */
void Game::placeTrap() {
    if (m_hasTrap) {
        //can place on another 
        bool canPlace = true;
        if (m_trapVector.size() - 1 > 0) {
            for (int i = 0; i < m_trapVector.size() - 1; i++) {
                if (m_collision.isCollidingAABB(m_trapVector[i]->getSprite(), m_trapVector[m_trapVector.size() - 1]->getSprite())) {
                    canPlace = false;
                }
            }
        }
        if (canPlace == true) {
            //place
            m_trapVector[m_trapVector.size() - 1]->setTrap();
            m_hasTrap = false;
        }
    } 
}

/**
 * @brief checks if a chunk already exists at a specific position
 * 
 * @param canSpawn if the chunk can be spawned or not
 * @param chunkToBeCheckedForOccupation position of another chunk
 * @param postion position to spawn the chunk
 */
void Game::canSpawnChunk(bool *canSpawn, sf::Vector2f chunkToBeCheckedForOccupation, sf::Vector2f postion) {
    if (chunkToBeCheckedForOccupation.x == postion.x && chunkToBeCheckedForOccupation.y == postion.y) {
        *canSpawn = false;
    }
}

/**
 * @brief spawn a chunk if canSpawn is true
 * 
 * @param canSpawn if the chunk can be spawned or not
 * @param position the position to spawn the chunk
 */
void Game::spawnChunk(bool canSpawn, sf::Vector2f position) {
    if (canSpawn) {
        //create new chunk at position
        std::shared_ptr<Chunk> chunk(new Chunk(m_backgroundTextures, m_numberOfTilesPerChunk, position, m_chunkLength));
        m_chunkVector.push_back(chunk);
    }
}

/**
 * @brief spawns four chunks
 * 
 * @param i the current chunk
 * @param chunkPosition1 chunk1 that will be spawned adjacent to chunk i
 * @param chunkPosition2 chunk2 that will be spawned adjacent to chunk i
 * @param chunkPosition3 chunk3 that will be spawned adjacent to chunk i
 */
void Game::chunkSpawning(const int &i, const sf::Vector2f &chunkPosition1, const sf::Vector2f &chunkPosition2, const sf::Vector2f &chunkPosition3) {
    bool canSpawnPosition1 = true;
    bool canSpawnPosition2 = true;
    bool canSpawnPosition3 = true;

    for (int j = 0; j < m_chunkVector.size(); j++) {
        if (j != i) {
            //check if any chunks already exists at the following positions
            canSpawnChunk(&canSpawnPosition1, m_chunkVector[j]->getPosition(), chunkPosition1);
            canSpawnChunk(&canSpawnPosition2, m_chunkVector[j]->getPosition(), chunkPosition2);
            canSpawnChunk(&canSpawnPosition3, m_chunkVector[j]->getPosition(), chunkPosition3);
        }
    }
    //spawn chunks at 3 different positions
    spawnChunk(canSpawnPosition1, chunkPosition1);
    spawnChunk(canSpawnPosition2, chunkPosition2);
    spawnChunk(canSpawnPosition3, chunkPosition3);
}

/**
 * @brief generates a random int from [0 - range)
 * 
 * @param range 
 * @return int 
 */
int Game::generateRandomNumber(const int &range) {
    return rand() % range; //0 to range - 1
}

/**
 * @brief gets if gamestate is active
 * 
 * @return true 
 * @return false 
 */
bool Game::getIsActive() {
    return m_isActive;
}

/**
 * @brief sets the m_isActive variable to newIsActive
 * 
 * @param newIsActive 
 */
void Game::setIsActive(const bool &newIsActive) {
    m_isActive = newIsActive;
}

/**
 * @brief getter for m_isPaused
 * 
 * @return true, if m_isPaused
 * @return false, if !m_isPaused
 */
bool Game::getIsPaused() {
    return m_isPaused;
}

/**
 * @brief setter for m_isPaused
 * 
 * @param isPaused 
 */
void Game::setIsPaused(const bool &isPaused) {
    m_isPaused = isPaused;
}

/**
 * @brief updates all gamefunctions according to deltatime
 * 
 * @param deltaTime 
 */
void Game::update(const float &deltaTime) {

    //update cursor world position
    sf::Vector2i mousePositionOfWindow = sf::Mouse::getPosition(*m_window);
    m_cursorWorldPosition = m_window->mapPixelToCoords(mousePositionOfWindow);

    //EVENTHANDLING
    sf::Event event;
    //this window is a different window
    while (m_window->pollEvent(event)) {
                
        // Close window: exit
        if (event.type == sf::Event::Closed)
            m_window->close();

        
        if (!m_window->hasFocus() || event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
            m_isPaused = true;
        }
        
        //upgrade menu
        if ((event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) || 
            (event.type == sf::Event::JoystickButtonReleased && event.joystickButton.joystickId == 0 && event.joystickButton.button == 5)) {
            for (int i = 0; i < 6; i++) {
                if (m_upgradeMenu->getButtons()[i]->isPressed(m_cursorWorldPosition.x, m_cursorWorldPosition.y)) {
                    switch(i) {
                        case 0:
                            upgrade(&m_movementSpeed, true, 1.4f, 0);
                            break;
                        case 1:
                            upgrade(&m_bulletSpeed, true, 1.4f, 1);
                            break;
                        case 2:
                            upgrade(&m_bulletCooldown, false, 1.7f, 2);
                            break;
                        case 3:
                            upgrade(&m_bulletDamage, true, 1.4f, 3);
                            break;
                        case 4:
                            upgrade(&m_playerMaxLife, true, 1.4f, 4);
                            m_player->setMaxLife(m_playerMaxLife);
                            break;
                        case 5:
                            upgrade(&m_heartLifeRefill, true, 1.4f, 5);
                            break;
                        }
                    break;
                }
            }
        }
    }
    //mouse set position by controller
    if (sf::Joystick::isConnected(0)) {
        sf::Vector2i joystickMousePosition(0, 0);
        if (sf::Joystick::getAxisPosition(0, sf::Joystick::U) > 1.5f || sf::Joystick::getAxisPosition(0, sf::Joystick::U) < -1.5f) {
            joystickMousePosition.x = (int)sf::Joystick::getAxisPosition(0, sf::Joystick::U) / 20.f;
        }
        if (sf::Joystick::getAxisPosition(0, sf::Joystick::V) > 1.5f || sf::Joystick::getAxisPosition(0, sf::Joystick::V) < -1.5f) {
            joystickMousePosition.y = (int)sf::Joystick::getAxisPosition(0, sf::Joystick::V) / 20.f;
        }
        sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition().x + joystickMousePosition.x, sf::Mouse::getPosition().y + joystickMousePosition.y));
    }

    //keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            move(sf::Vector2f(0.f, -m_movementSpeed), deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            move(sf::Vector2f(-m_movementSpeed, 0.f), deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            move(sf::Vector2f(0.f, m_movementSpeed), deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            move(sf::Vector2f(m_movementSpeed, 0.f), deltaTime);
        }
    } else if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10.f || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10.f ||
            sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 10.f || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -10.f) {
        //create copy of player, move copied player
        std::shared_ptr<Player> playerCopy = std::make_shared<Player>(*m_player);
        playerCopy->move(sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100.f * m_movementSpeed, sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100.f * m_movementSpeed), deltaTime);
        //AABB collision is enough
        if (!playerCopy->getSprite().getGlobalBounds().intersects(m_borderLeft.getGlobalBounds()) &&
            !playerCopy->getSprite().getGlobalBounds().intersects(m_borderTop.getGlobalBounds()) &&
            !playerCopy->getSprite().getGlobalBounds().intersects(m_borderRight.getGlobalBounds()) &&
            !playerCopy->getSprite().getGlobalBounds().intersects(m_borderBottom.getGlobalBounds())) {
            m_player->move(sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100.f * m_movementSpeed, sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100.f * m_movementSpeed), deltaTime);
        }
    }

    if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Joystick::isButtonPressed(0, 5)) && m_onBulletCooldown == false) {
        shoot();
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Joystick::isButtonPressed(0, 5)) {
        m_bulletSpawnAmountRest = 0.f;
        m_playerFiredLastFrame = false;
    }

    //check if player wants to take trap in hand
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0, 0)) {
        takeTrap();
    }

    //check trap placement input
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Joystick::isButtonPressed(0, 4)) {
        placeTrap();
    }

    //COLLISION
    //if player is in wall, move player out of wall
    moveOutOfBorder(deltaTime);

    //check if enemy collides with player & if player should get knockback in the next frames
    bool knockback = false;

    for (int i = 0; i < m_enemyVector.size(); i++) {
        //at the start of each frame, every enemy can move
        m_enemyVector[i]->setCanMove(true);

        //check if enemy is too far away from player, if yes delete enemy
        if (getVectorLength(m_enemyVector[i]->getPosition(), m_player->getPosition()) > m_enemyMaxDistanceFromPlayer) {
            m_enemyVector.erase(m_enemyVector.begin() + i);

            m_enemySpawnCountDifference++;
            //decrease m_enemiesSpawnedCount by one, since we arent spawning a "new" enemies
            m_enemiesSpawnedCount--;
        } else {
            //loops through all enemies and check for collision
            if (m_collision.isCollidingAABB(m_player->getSprite(), m_enemyVector[i]->getSprite())) {
                if (m_collision.isCollidingSAT(m_player->getSprite(), m_enemyVector[i]->getSprite())) {
                    if (m_player->getOnKnockback() == false) {
                        if (knockback == false) {
                            //enemy colliding with player, so set knockback to true
                            //can only get knockback from one enemy, so only do this for the first enemy in the loop
                            m_player->setOnKnockback(true);
                            m_knockbackStartingPosition = m_player->getPosition();
                            m_player->setKnockbackAngle(m_enemyVector[i]->getAngle());
                            //player damage
                            playerHit.play();
                            if (m_enemyVector[i]->getType() == 0) {
                                //normal enemy
                                m_player->setCurrentLife(m_player->getCurrentLife() - m_enemyNormalDamage);
                            } else if (m_enemyVector[i]->getType() == 1) {
                                //tank enemy
                                m_player->setCurrentLife(m_player->getCurrentLife() - m_enemyTankDamage);
                            }
                            if (m_player->getCurrentLife() < 0) {
                                m_player->setCurrentLife(0);
                            }
                            knockback = true;
                        }
                    }
                    //enemy cant move since hes colliding with player
                    m_enemyVector[i]->setCanMove(false);
                    break;
                }
            }
        }
    }

    //enemy-trap collision
    if (m_trapVector.size() > 0) {
        int trapLoopAmount = m_trapVector.size();
        if (m_hasTrap) {
            trapLoopAmount--;
        }
        if (trapLoopAmount > 0) {
            for (int i = 0; i < m_enemyVector.size(); i++) {
                //only check the enemies that can still move
                if (m_enemyVector[i]->getCanMove()) {
                    for (int j = 0; j < trapLoopAmount; j++) {
                        if (m_enemyVector[i]->getIsTapped()) {
                            //check if enemy is still trapped
                            if (m_gametime.getElapsedTime().asSeconds() - m_enemyTrappedClock[i] > m_trappedTime) {
                                m_enemyVector[i]->setIsTrapped(false);
                                //enemy not trapped anymore, trap takes damage here
                                //check in what trap the enemy was
                                for (int k = 0; k < trapLoopAmount; k++) {
                                    if (m_trapVector[k]->isAlreadyTrapped(m_enemyVector[i])) {
                                        m_trapVector[k]->setCurrentLife(m_trapVector[k]->getCurrentLife() - m_trapUseDamage);
                                        m_score += 2.f;
                                        m_scoreText.setString("Score: " + std::to_string((int)m_score));
                                    }
                                }
                            } else {
                                //still trapped so cant move
                                m_enemyVector[i]->setCanMove(false);
                                break;
                            }
                        } else {
                            //check if it has already been trapped by this trap. if yes, it can move
                            if (!m_trapVector[j]->isAlreadyTrapped(m_enemyVector[i])) {
                                //check if enemy is in trap
                                if (m_collision.isFullyCollidingAABB(m_trapVector[j]->getSprite(), m_enemyVector[i]->getSprite())) {
                                    //enemy is trapped
                                    m_enemyVector[i]->setCanMove(false);
                                    m_enemyVector[i]->setIsTrapped(true);
                                    m_trapVector[j]->addTrappedEnemy(m_enemyVector[i]);
                                    m_enemyTrappedClock[i] = m_gametime.getElapsedTime().asSeconds();
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        } 
    }

    //player knockback on enemy collision
    if (m_player->getOnKnockback() == true) {
        //check if knockbackdistance is already passed
        if (getVectorLength(m_knockbackStartingPosition, m_player->getPosition()) < m_knockbackLength) {
            //move the player
            sf::Vector2f knockbackMovement(-m_knockbackMovementSpeed * cos(m_player->getKnockbackAngle()), -m_knockbackMovementSpeed * sin(m_player->getKnockbackAngle()));
            m_player->move(knockbackMovement, deltaTime);
        } else {
            m_player->setOnKnockback(false);
        }
    }

    //check for item drop collision
    //heart
    for (int i = 0; i < m_itemDropHeartVector.size(); i++) {
        if (m_collision.isCollidingAABB(m_player->getSprite(), m_itemDropHeartVector[i]->getSprite())) {
            if (m_collision.isCollidingSAT(m_player->getSprite(), m_itemDropHeartVector[i]->getSprite())) {
                //there is collision
                if (m_player->getCurrentLife() != m_player->getMaxLife()) {
                    //player already full so leave the heart drop be
                    if (m_player->getCurrentLife() + m_heartLifeRefill > m_player->getMaxLife()) {
                        //player life would be more than the player life bar can accept
                        m_player->setCurrentLife(m_player->getMaxLife());
                    } else {
                        m_player->setCurrentLife(m_player->getCurrentLife() + m_heartLifeRefill);
                    }
                    m_itemDropHeartVector.erase(m_itemDropHeartVector.begin() + i);
                }
            }
        }
    }

    //coin
    for (int i = 0; i < m_itemDropCoinVector.size(); i++) {
        if (m_collision.isCollidingAABB(m_player->getSprite(), m_itemDropCoinVector[i]->getSprite())) {
            if (m_collision.isCollidingSAT(m_player->getSprite(), m_itemDropCoinVector[i]->getSprite())) {
                //increase m_coinAmount
                ++m_coinAmount;
                m_upgradeMenu->setCoinAmount(m_coinAmount);
                m_itemDropCoinVector.erase(m_itemDropCoinVector.begin() + i);
            }
        }
    }

    //trap
    for (int i = 0; i < m_itemDropTrapVector.size(); i++) {
        if (m_collision.isCollidingAABB(m_player->getSprite(), m_itemDropTrapVector[i]->getSprite())) {
            if (m_collision.isCollidingSAT(m_player->getSprite(), m_itemDropTrapVector[i]->getSprite())) {
                //has one more trap in inventory
                m_inventory->setTrapAmount(m_inventory->getTrapAmount() + 1);
                //delete itemDrop trap
                m_itemDropTrapVector.erase(m_itemDropTrapVector.begin() + i);
            }
        }
    }

    //makes the zombie rotate towards the player
    for (int i = 0; i < m_enemyVector.size(); i++) {
        //update rotation
        sf::Vector2f distanceEnemyPlayer = m_enemyVector[i]->getPosition() - m_player->getPosition();
        m_enemyVector[i]->setAngle(atan2(distanceEnemyPlayer.y, distanceEnemyPlayer.x));
        m_enemyVector[i]->setRotation((m_enemyVector[i]->getAngle() * 180.f / 3.1415f) + 90.f);

        //update life
        m_enemyVector[i]->updateLife();

        //move the enemy
        if (m_enemyVector.size() > 1) {
            for (int j = i + 1; j < m_enemyVector.size(); j++) {
                //its ok to just use AABB collision detection between enemies for performance
                if (m_collision.isCollidingAABB(m_enemyVector[i]->getSprite(), m_enemyVector[j]->getSprite())) {
                    //if there is one collision with another enemy, then is colliding is true
                    //the person closest to player gets to move
                    if (getVectorLength(m_enemyVector[i]->getPosition(), m_player->getPosition()) > getVectorLength(m_enemyVector[j]->getPosition(), m_player->getPosition())) {
                        //the i-th enemy further away from the person, so dont move the i-th enemy this frame
                        m_enemyVector[i]->setCanMove(false);
                    } else {
                        m_enemyVector[j]->setCanMove(false);
                    }
                }
            }
        }
        if (m_enemyVector[i]->getCanMove()) {
            //is not colliding with other enemies or player, so move the enemy
            if (m_enemyVector[i]->getType() == 0) {
                //normal enemy
                sf::Vector2f enemyMovement(-m_enemyNormalMovementSpeed * cos(m_enemyVector[i]->getAngle()), -m_enemyNormalMovementSpeed * sin(m_enemyVector[i]->getAngle()));
                m_enemyVector[i]->move(enemyMovement, deltaTime);
            } else if (m_enemyVector[i]->getType() == 1) {
                //tank enemy
                sf::Vector2f enemyMovement(-m_enemyTankMovementSpeed * cos(m_enemyVector[i]->getAngle()), -m_enemyTankMovementSpeed * sin(m_enemyVector[i]->getAngle()));
                m_enemyVector[i]->move(enemyMovement, deltaTime);
            }
        }
    }

    //ENEMY SPAWNING
    if (m_enemiesTotalToBeSpawnedInWave > m_enemiesSpawnedCount) {
        if (m_wave == 1 && m_waveCooldownClock.getElapsedTime().asSeconds() < m_waveCooldownLength) {
            m_onWaveCooldown = true;
            m_drawWaveText = true;
            m_enemySpawnClock.restart().asSeconds();
            m_enemySpawnCountDifference = 0.f;
        } else if (m_wave == 1 && m_waveCooldownClock.getElapsedTime().asSeconds() > m_waveCooldownLength) {
            m_onWaveCooldown = false;
            m_drawWaveText = false;
        }

        if (m_onWaveCooldown == false) {
            //when greater than one, at least one enemy will be spawned. this way with low fps the amount of enemies spawned will still overlap with high fps.

            float enemySpawnCount = (m_enemySpawnClock.getElapsedTime().asSeconds() + m_enemySpawnCountDifference) / m_enemySpawnRate;
            if (m_enemyVector.size() < m_maxAllowedAliveEnemies) {
                //new enemies can be spawned
                if (enemySpawnCount > 1.f) {
                    m_enemySpawnCountDifference = enemySpawnCount - (int)enemySpawnCount;
                    //at least one enemy should be spawned this frame

                    int enemiesToBeSpawned;
                    if (m_enemyVector.size() + enemySpawnCount <= m_maxAllowedAliveEnemies) {
                        enemiesToBeSpawned = (int)enemySpawnCount;
                    } else {
                        //we can start - 1, because we already know (counter + enemySpawnCount > m_maxAllowedAliveEnemies) == true
                        int counter = enemySpawnCount;
                        //find the biggest number where m_enemyVector.size() + int i < m_maxAllowedAliveEnemies
                        while (m_enemyVector.size() + counter > m_maxAllowedAliveEnemies) {
                            counter--;
                        }
                        enemiesToBeSpawned = counter;
                    }

                    for (int i = 0; i < enemiesToBeSpawned; i++) {
                        //create random angle
                        int randomAngle = generateRandomNumber(360);
                        //start with the player position vector and move the coordinates by a random angle and a specific length to a new position
                        sf::Vector2f spawnCoordinates(m_player->getPosition().x + cos(randomAngle) * m_enemySpawnRadius, m_player->getPosition().y + sin(randomAngle) * m_enemySpawnRadius);

                        //check wether spawnCoordinates is in the map
                        while (!m_field.getGlobalBounds().contains(spawnCoordinates.x, spawnCoordinates.y)) {
                            randomAngle = generateRandomNumber(360);
                            spawnCoordinates = sf::Vector2f(m_player->getPosition().x + cos(randomAngle) * m_enemySpawnRadius, m_player->getPosition().y + sin(randomAngle) * m_enemySpawnRadius);
                        }

                        //if there are other enemies
                        if (m_enemyVector.size() > 0) {
                            bool canSpawn = false;
                            int counter = 0;
                            while (canSpawn == false) {
                                for (int i = 0; i < m_enemyVector.size(); i++) {
                                    //loop through all enemies, and check, wether this position is already occupied
                                    if (m_enemyVector[i]->getSprite().getGlobalBounds().contains(spawnCoordinates)) {
                                        //the position is already occupied, move the coordinates, and start over    
                                        spawnCoordinates.x = m_player->getPosition().x + cos(randomAngle) * (m_enemySpawnRadius + m_enemyMoveFactor * counter);
                                        spawnCoordinates.y = m_player->getPosition().y + sin(randomAngle) * (m_enemySpawnRadius + m_enemyMoveFactor * counter);

                                        //check if new positions are still in map
                                        while (!m_field.getGlobalBounds().contains(spawnCoordinates.x, spawnCoordinates.y)) {
                                            randomAngle = generateRandomNumber(360);
                                            spawnCoordinates = sf::Vector2f(m_player->getPosition().x + cos(randomAngle) * m_enemySpawnRadius, m_player->getPosition().y + sin(randomAngle) * m_enemySpawnRadius);
                                        }
                                        break;
                                    }
                                    if (i == m_enemyVector.size() - 1) {
                                        //it doesn't collide with any enemies, so break out of the while loop
                                        canSpawn = true;
                                    }
                                }
                                counter++;
                            }
                        }

                        //create enemy object
                        //randomize the enemy type
                        if (generateRandomNumber(2) == 0) {
                            std::shared_ptr<Enemy> enemy(new Enemy(spawnCoordinates, *resourceManager.getTexture("enemyNormal"), m_enemyNormalMaxLife, 0));
                            m_enemyVector.push_back(enemy);
                            m_enemyTrappedClock.push_back(0.f);
                        } else {
                            std::shared_ptr<Enemy> enemy(new Enemy(spawnCoordinates, *resourceManager.getTexture("enemyBig"), m_enemyTankMaxLife, 1));
                            m_enemyVector.push_back(enemy);
                            m_enemyTrappedClock.push_back(0.f);
                        }
                        m_enemiesSpawnedCount++;
                        m_enemySpawnClock.restart();
                    }
                }    
            }
        }
    } else {
        //check if no enemies are alive
        if (m_enemyVector.size() == 0 && m_onWaveCooldown == false) {
            m_waveCooldownClock.restart().asSeconds();
            ++m_wave;
            m_waveText.setString("Wave " + std::to_string(m_wave));
            m_score += 10.f;
            m_scoreText.setString("Score: " + std::to_string((int)m_score));
            m_onWaveCooldown = true;

        } else if (m_enemyVector.size() == 0 && m_onWaveCooldown == true) {
            if (m_waveCooldownClock.getElapsedTime().asSeconds() > m_waveCooldownLength) {

                m_onWaveCooldown = false;
                m_drawWaveText = false;

                //update stats
                m_enemyNormalMovementSpeed *= 1.1f;
                m_enemyNormalMaxLife *= 1.1f;
                m_enemyNormalDamage *= 1.1f;

                m_enemyTankMovementSpeed *= 1.1f;
                m_enemyTankMaxLife *= 1.1f;
                m_enemyTankDamage *= 1.1f;

                m_maxAllowedAliveEnemies += 3;
                m_enemiesSpawnedCount = 0;
                m_enemiesTotalToBeSpawnedInWave += 5; //how many to spawn in first wave
                m_enemySpawnClock.restart().asSeconds();
                m_enemySpawnCountDifference = 0.f;
                if (m_enemySpawnRate > 0.1f) {
                    m_enemySpawnRate -= 0.05f;
                }

            } else {
                //while on wave cooldown, display wave text
                m_drawWaveText = true;
            }
        }
    }

    //background-chunk 
    //if player a specific quadrant of the current chunk he's in, then generate 3 more chunks that border the the quadrant
    if (m_chunkVector.size() > 0) {

        //check in what chunk the player is
        bool isInChunk = false;
        for (int i = 0; i < m_chunkVector.size(); i++) {

            if (m_player->getPosition().x >= m_chunkVector[i]->getPosition().x && m_player->getPosition().x < m_chunkVector[i]->getPosition().x + m_chunkLength &&
                m_player->getPosition().y >= m_chunkVector[i]->getPosition().y && m_player->getPosition().y < m_chunkVector[i]->getPosition().y + m_chunkLength) {
                //player is in this chunk
                isInChunk = true;
                //check in what quadrant of the chunk the player is
                if (m_player->getPosition().x >= m_chunkVector[i]->getPosition().x && m_player->getPosition().x < m_chunkVector[i]->getPosition().x + (m_chunkLength / 2.f) &&
                    m_player->getPosition().y >= m_chunkVector[i]->getPosition().y && m_player->getPosition().y < m_chunkVector[i]->getPosition().y + (m_chunkLength / 2.f)) {
                    //upper left quadrant
                    chunkSpawning(i, 
                        sf::Vector2f(m_chunkVector[i]->getPosition().x - m_chunkLength, m_chunkVector[i]->getPosition().y), 
                        sf::Vector2f(m_chunkVector[i]->getPosition().x - m_chunkLength, m_chunkVector[i]->getPosition().y - m_chunkLength), 
                        sf::Vector2f(m_chunkVector[i]->getPosition().x, m_chunkVector[i]->getPosition().y - m_chunkLength)
                    );
                } else if (m_player->getPosition().x >= m_chunkVector[i]->getPosition().x + (m_chunkLength / 2.f) && m_player->getPosition().x < m_chunkVector[i]->getPosition().x + m_chunkLength &&
                        m_player->getPosition().y >= m_chunkVector[i]->getPosition().y && m_player->getPosition().y < m_chunkVector[i]->getPosition().y + (m_chunkLength / 2.f)) {
                    //upper right quadrant
                    chunkSpawning(i, 
                        sf::Vector2f(m_chunkVector[i]->getPosition().x + m_chunkLength, m_chunkVector[i]->getPosition().y), 
                        sf::Vector2f(m_chunkVector[i]->getPosition().x + m_chunkLength, m_chunkVector[i]->getPosition().y - m_chunkLength), 
                        sf::Vector2f(m_chunkVector[i]->getPosition().x, m_chunkVector[i]->getPosition().y - m_chunkLength)
                    );
                } else if (m_player->getPosition().x >= m_chunkVector[i]->getPosition().x && m_player->getPosition().x < m_chunkVector[i]->getPosition().x + (m_chunkLength / 2.f) &&
                        m_player->getPosition().y >= m_chunkVector[i]->getPosition().y + (m_chunkLength / 2.f) && m_player->getPosition().y < m_chunkVector[i]->getPosition().y + m_chunkLength) {
                    //lower left quadrant
                    chunkSpawning(i, 
                        sf::Vector2f(m_chunkVector[i]->getPosition().x - m_chunkLength, m_chunkVector[i]->getPosition().y), 
                        sf::Vector2f(m_chunkVector[i]->getPosition().x - m_chunkLength, m_chunkVector[i]->getPosition().y + m_chunkLength), 
                        sf::Vector2f(m_chunkVector[i]->getPosition().x, m_chunkVector[i]->getPosition().y + m_chunkLength)
                    );
                } else {
                    //lower right quadrant
                    chunkSpawning(i, 
                        sf::Vector2f(m_chunkVector[i]->getPosition().x + m_chunkLength, m_chunkVector[i]->getPosition().y), 
                        sf::Vector2f(m_chunkVector[i]->getPosition().x + m_chunkLength, m_chunkVector[i]->getPosition().y + m_chunkLength), 
                        sf::Vector2f(m_chunkVector[i]->getPosition().x, m_chunkVector[i]->getPosition().y + m_chunkLength)
                    );
                }
            }
        }
        if (isInChunk == false) {
            //player is not in a chunk, so delete all chunks and create a new chunk
            for (int i = m_chunkVector.size() -1; i >= 0; i--) {
                m_chunkVector.erase(m_chunkVector.begin() + i);
            }
            std::shared_ptr<Chunk> chunk(new Chunk(m_backgroundTextures, m_numberOfTilesPerChunk, sf::Vector2f(m_player->getPosition().x - (m_chunkLength / 2), m_player->getPosition().y - (m_chunkLength / 2)), m_chunkLength));
            m_chunkVector.push_back(chunk);
        }
    } else {
        
        //if there is no chunk then create one generate one at player position
        std::shared_ptr<Chunk> chunk(new Chunk(m_backgroundTextures, m_numberOfTilesPerChunk, sf::Vector2f(m_player->getPosition().x - (m_chunkLength / 2), m_player->getPosition().y - (m_chunkLength / 2)), m_chunkLength));
        m_chunkVector.push_back(chunk);
    }

    //cursor
    m_cursor.setPosition(sf::Vector2f(m_cursorWorldPosition));
    m_player->updateLife();

    //rotations
    //makes the rotate towards the cursor
    sf::Vector2f distancePlayerCursor = m_player->getPosition() - m_cursorWorldPosition;
    float anglePlayerRotation = atan2(distancePlayerCursor.y, distancePlayerCursor.x);
    m_player->setRotation((anglePlayerRotation * 180.f / 3.1415f) + 90.f);

    //bullets lifetime and movement
    if (m_bulletVector.size() > 0) {
        for (int i = 0; i < m_bulletVector.size(); i++) {

            //check for lifetime
            if (getVectorLength(m_bulletVector[i]->getPosition(), m_player->getPosition()) > m_bulletLifetime) {
                m_bulletVector.erase(m_bulletVector.begin() + i);
            } else {
                //still in lifetime, check for collision / move
                bool isColliding = false;
                if (m_enemyVector.size() > 0) {
                    //there are enemies alive
                    for (int j = 0; j < m_enemyVector.size(); j++) {
                        //loop through all enemies
                        //first AABB then SAT for performance
                        if (m_collision.isCollidingAABB(m_bulletVector[i]->getSprite(), m_enemyVector[j]->getSprite())) {
                            //check for true collision
                            if (m_collision.isCollidingSAT(m_bulletVector[i]->getSprite(), m_enemyVector[j]->getSprite())) {
                                //enemy takes damage
                                m_enemyVector[j]->setCurrentLife(m_enemyVector[j]->getCurrentLife() - m_bulletDamage);
                                if (m_enemyVector[j]->getCurrentLife() <= 0) {
                                    //the enemy is dead
                                        
                                    //item drops
                                    if (generateRandomNumber(m_itemDropSpawnRate) == 0) {
                                        //generate a random item drop
                                        int item = generateRandomNumber(5);
                                        if (item == 0) {
                                            //generate heart
                                            std::shared_ptr<ItemDrop> heart(new ItemDrop(*resourceManager.getTexture("heartItemDrop"), sf::Vector2i(13, 11), m_enemyVector[j]->getPosition(), m_gametime.getElapsedTime().asSeconds(), 0.2f, 2.5f));
                                            m_itemDropHeartVector.push_back(heart);
                                        } else if (item == 1 || item == 2 || item == 3) {
                                            //generate coin
                                            std::shared_ptr<ItemDrop> coin(new ItemDrop(*resourceManager.getTexture("coinItemDrop"), sf::Vector2i(12, 14), m_enemyVector[j]->getPosition(), m_gametime.getElapsedTime().asSeconds(), 0.02f, 2.f));
                                            m_itemDropCoinVector.push_back(coin);
                                        } else {
                                            //generate trap
                                            std::shared_ptr<ItemDrop> trap(new ItemDrop(*resourceManager.getTexture("trapItemDrop"), sf::Vector2i(14, 16), m_enemyVector[j]->getPosition(), m_gametime.getElapsedTime().asSeconds(), 0.2f, 2.f));
                                            m_itemDropTrapVector.push_back(trap);
                                        }
                                    }
                                    //delete enemy
                                    m_enemyVector.erase(m_enemyVector.begin() + j);

                                    //update score
                                    m_score += 5.f;
                                    m_scoreText.setString("Score: " + std::to_string((int)m_score));

                                }
                                m_bulletVector.erase(m_bulletVector.begin() + i);
                                enemyHit.play();
                                isColliding = true;
                                break;
                            }
                        }
                    }
                } 
                if (isColliding == false) {
                    //move the bullet
                    m_bulletVector[i]->move(deltaTime);
                }
            }
        }
    }

    //bullet cooldown
    if (m_onBulletCooldown == true) {
        if (m_bulletCooldownClock.getElapsedTime().asSeconds() > m_bulletCooldown) {
            m_onBulletCooldown = false;
        }
    }
    if (m_bulletCooldownClock.getElapsedTime().asSeconds() > m_bulletCooldown) {
        m_bulletCooldownClock.restart();
    }

    //update trap position
    if (m_hasTrap) {
        m_trapVector[m_trapVector.size() - 1]->setPosition(sf::Vector2f(m_cursorWorldPosition.x, m_cursorWorldPosition.y));
    }

    //delete traps with no life
    for (int i = 0; i < m_trapVector.size(); i++) {
        if (m_trapVector[i]->getCurrentLife() <= 0.f) {
            m_trapVector.erase(m_trapVector.begin() + i);
        }
    }

    //update upgradeMenu
    m_upgradeMenu->update(m_player->getPosition());
    m_upgradeMenu->setCoinAmount(m_coinAmount);

    //update inventory
    m_inventory->update(m_player->getPosition());

    //update wave text
    m_waveText.setPosition(m_player->getPosition().x, m_player->getPosition().y - 200.f);

    //update animations
    //heart
    for (int i = 0; i < m_itemDropHeartVector.size(); i++) {
        m_itemDropHeartVector[i]->update(m_gametime.getElapsedTime().asSeconds());
    }

    //coin
    for (int i = 0; i < m_itemDropCoinVector.size(); i++) {
        m_itemDropCoinVector[i]->update(m_gametime.getElapsedTime().asSeconds());
    }

    //trap animation
    if (m_hasTrap) {
        for (int i = 0; i < m_trapVector.size() - 1; i++) {
            m_trapVector[i]->updateAnimation(m_gametime.getElapsedTime().asSeconds());
        }
    } else {
        for (int i = 0; i < m_trapVector.size(); i++) {
            m_trapVector[i]->updateAnimation(m_gametime.getElapsedTime().asSeconds());
        }
    }

    //move texts
    m_scoreText.setPosition(m_player->getPosition().x, m_player->getPosition().y - 450.f);
    m_gameOverText.setPosition(m_player->getPosition().x, m_player->getPosition().y);
    m_isPausedText.setPosition(m_player->getPosition().x, m_player->getPosition().y);

    //check if player is dead
    if (m_player->getCurrentLife() == 0) {
        m_dead = true;
    }
}

/**
 * @brief renders all gamefunctions
 * 
 */
void Game::render() {

    // Clear screen
    m_window->clear(sf::Color::White);
    m_view.setCenter(m_player->getPosition());
    m_window->setView(m_view);

    //draw items here, note: z-index
    for (int i = 0; i < m_chunkVector.size(); i++) {
        std::vector<sf::Sprite> chunkTiles = m_chunkVector[i]->getTiles();
        for (int j = 0; j < m_numberOfTilesPerChunk; j++) {
            m_window->draw(chunkTiles[j]);
        }
    }

    m_window->draw(m_borderRight);
    m_window->draw(m_borderTop);
    m_window->draw(m_borderLeft);
    m_window->draw(m_borderBottom);

    //trap
    //player here is still alive
    if (m_trapVector.size() > 0) {
        for (int i = 0; i < m_trapVector.size(); i++) {
            //trap texture
            m_window->draw(m_trapVector[i]->getSprite());
            //trap life
            if (i != m_trapVector.size() - 1 || m_hasTrap == false) {
                m_window->draw(m_trapVector[i]->getLifeRectangles()[0]);
                m_window->draw(m_trapVector[i]->getLifeRectangles()[1]);
            }
        }
    }
    
    //item drops
    for (std::shared_ptr<ItemDrop> heart : m_itemDropHeartVector) {
        m_window->draw(heart->getSprite());
    }
    for (std::shared_ptr<ItemDrop> coin : m_itemDropCoinVector) {
        m_window->draw(coin->getSprite());
    }
    for (std::shared_ptr<ItemDrop> trap : m_itemDropTrapVector) {
        m_window->draw(trap->getSprite());
    }
    //bullets
    for (std::shared_ptr<Bullet> bullet : m_bulletVector) {
        m_window->draw(bullet->getSprite());
    }
    //enemies
    for (std::shared_ptr<Enemy> enemy : m_enemyVector) {
        m_window->draw(enemy->getSprite());
        m_window->draw(enemy->getLifeRectangles()[0]);
        m_window->draw(enemy->getLifeRectangles()[1]);
    }

    //player
    m_window->draw(m_player->getSprite());

    //player life
    m_window->draw(m_player->getLifeRectangles()[0]);
    m_window->draw(m_player->getLifeRectangles()[1]);

    //wave text
    if (m_drawWaveText) {
        m_window->draw(m_waveText);
    }

    //upgrade menu
    m_window->draw(m_upgradeMenu->getUpgradeMenuBackground());
    
    for (int i = 0; i < 6; i++) {
        m_window->draw(m_upgradeMenu->getTitleTexts()[i]);
        m_window->draw(m_upgradeMenu->getButtonRectangles()[i]);
        m_window->draw(m_upgradeMenu->getButtonTexts()[i]);
    }
    m_window->draw(m_upgradeMenu->getCoinAmountText());

    //inventory
    m_window->draw(m_inventory->getTrapSprite());
    m_window->draw(m_inventory->getTrapText());

    //score
    m_window->draw(m_scoreText);

    if (!m_dead) {
        if (m_isPaused) {
            m_window->draw(m_isPausedText);
        } else {
            m_window->draw(m_cursor);
        }
    } else {
        m_window->draw(m_gameOverText);
    }

    // Update the window
    m_window->display();

}