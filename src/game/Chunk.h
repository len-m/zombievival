#ifndef CHUNK_H
#define CHUNK_H

#include <SFML/Graphics.hpp>
#include <Math.h>
#include <memory>
#include <vector>

class Chunk {
    public:
        Chunk(const std::vector<sf::Texture> texture, const int &numberOfTiles, const sf::Vector2f &position, const float &chunkLength);
        std::vector<sf::Sprite> getTiles();
        sf::Vector2f getPosition();
    private:
        int generateRandomNumber(const int &range);
        void createChunk();
        float m_chunkLength;
        int m_numberOfTiles;
        std::vector<sf::Texture> m_texture;
        sf::Vector2f m_position;
        std::vector<sf::Sprite> m_tiles;
};

#endif