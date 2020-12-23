#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>
#include <stdlib.h> //srand, rand
#include "Collision.h"
#include "Chunk.h"
#include "UpgradeMenu.h"
#include "ItemDrop.h"
#include "Trap.h"
#include "Inventory.h"
#include "../ResourceManager.h"
#include <algorithm>

class Game {
    public:
        Game(sf::RenderWindow *window);
        void update(const float &deltaTime);
        void render();
        bool getIsActive();
        void setIsActive(const bool &newIsActive);
        bool getIsDead();
        bool getIsPaused();
        void setIsPaused(const bool &isPaused);
    private:
        //general stuff
        Collision m_collision;
        int generateRandomNumber(const int &range);
        float getVectorLength(const sf::Vector2f &vector, const sf::Vector2f &offset);
        sf::RenderWindow *m_window;
        sf::View m_view;
        bool m_isActive;
        sf::Clock m_gametime;
        sf::RectangleShape m_field;
        sf::RectangleShape m_borderLeft;
        sf::RectangleShape m_borderTop;
        sf::RectangleShape m_borderRight;
        sf::RectangleShape m_borderBottom;
        ResourceManager resourceManager;
        float m_score;
        sf::Text m_scoreText;
        sf::Text m_gameOverText;
        bool m_isPaused;
        sf::Text m_isPausedText;

        //cursor
        sf::Vector2f m_cursorWorldPosition;
        sf::Sprite m_cursor;

        //bullet
        std::vector<std::shared_ptr<Bullet>> m_bulletVector;
        sf::Clock m_bulletCooldownClock;
        float m_bulletSpeed;
        float m_bulletLifetime;
        float m_bulletCooldown;
        bool m_onBulletCooldown;
        float m_bulletDamage;
        bool m_playerFiredLastFrame;
        float m_bulletSpawnAmountRest;

        //player
        void move(const sf::Vector2f &movement, const float &deltaTime);
        void moveOutOfBorder(const float &deltaTime);
        void shoot();
        void takeTrap();
        void placeTrap();
        std::shared_ptr<Player> m_player;
        float m_playerMaxLife;
        float m_movementSpeed;
        float m_knockbackMovementSpeed;
        sf::Vector2f m_knockbackStartingPosition;
        float m_knockbackLength;
        bool m_dead;

        //enemy
        std::vector<std::shared_ptr<Enemy>> m_enemyVector;
        sf::Clock m_enemySpawnClock;
        float m_enemySpawnRate;
        float m_enemySpawnCountDifference;
        float m_enemySpawnRadius;
        int m_maxAllowedAliveEnemies;
        float m_enemyMoveFactor;
        float m_enemyMaxDistanceFromPlayer;
        int m_wave;
        int m_enemiesTotalToBeSpawnedInWave;
        int m_enemiesSpawnedCount;
        sf::Text m_waveText;
        sf::Clock m_waveCooldownClock;
        bool m_onWaveCooldown;
        bool m_drawWaveText;
        float m_waveCooldownLength;
        std::vector<float> m_enemyTrappedClock;
        float m_trappedTime;

        //enemyType
        float m_enemyNormalDamage;
        float m_enemyNormalMovementSpeed;
        float m_enemyNormalMaxLife;

        float m_enemyTankDamage;
        float m_enemyTankMovementSpeed;
        float m_enemyTankMaxLife;


        //item drops
        std::vector<std::shared_ptr<ItemDrop>> m_itemDropHeartVector;
        std::vector<std::shared_ptr<ItemDrop>> m_itemDropCoinVector;
        std::vector<std::shared_ptr<ItemDrop>> m_itemDropTrapVector;
        float m_heartLifeRefill;
        int m_itemDropSpawnRate;
        int m_coinAmount;

        //trap
        bool m_hasTrap;
        std::vector<std::shared_ptr<Trap>> m_trapVector;
        float m_trapUseDamage; //damage the trap gets if an enemy steps inside

        //chunk
        void canSpawnChunk(bool *canSpawn, sf::Vector2f chunkToBeCheckedForOccupation, sf::Vector2f postion);
        void spawnChunk(bool canSpawn, sf::Vector2f position);
        void chunkSpawning(const int &i, const sf::Vector2f &chunkPosition1, const sf::Vector2f &chunkPosition2, const sf::Vector2f &chunkPosition3);
        std::vector<std::shared_ptr<Chunk>> m_chunkVector;
        float m_chunkLength;
        int m_numberOfTilesPerChunk;
        std::vector<sf::Texture> m_backgroundTextures;

        //upgrade Menu
        void upgrade(float *upgradeType, const bool &multiply, const float &amount, const int &i);
        std::shared_ptr<UpgradeMenu> m_upgradeMenu;

        //inventory
        std::shared_ptr<Inventory> m_inventory;

        //sounds
        sf::Sound shootSound;
        sf::Sound enemyHit;
        sf::Sound playerHit;
};

#endif