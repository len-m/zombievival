#include "Chunk.h"

/**
 * @brief Construct a new Chunk object
 * 
 * @param texture 
 * @param numberOfTiles number of tiles per row of each chunk
 * @param position 
 * @param chunkLength the side length of a chunk
 */
Chunk::Chunk(const std::vector<sf::Texture> texture, const int &numberOfTiles, const sf::Vector2f &position, const float &chunkLength) {
    m_position = position; //set origin up left: don't change

    m_texture = texture;
    m_numberOfTiles = numberOfTiles;
    m_chunkLength = chunkLength;

    //init to prevent crashes
    for (int i = 0; i < m_numberOfTiles; i++) {
        sf::Sprite sprite;
        m_tiles.push_back(sprite);
    }

    createChunk();
}
/**
 * @brief generates a random int from [0 - range)
 * 
 * @param range 
 * @return int 
 */
int Chunk::generateRandomNumber(const int &range) {
    return rand() % range; //0 to range - 1
}

/**
 * @brief creates a new chunk
 * 
 */
void Chunk::createChunk() {
    //set the tiles
    sf::Vector2f tilePosition = m_position;
    float tileLength = m_chunkLength / sqrt(m_numberOfTiles);
    int counter = 0;
    for (int i = 0; i < sqrt(m_numberOfTiles); i++) {
        for (int j = 0; j < sqrt(m_numberOfTiles); j++) {
            int randomTexture = generateRandomNumber(2);
            int randomRotation = generateRandomNumber(4);

            m_tiles[counter].setTexture(m_texture[randomTexture]);
            //calculate the tileScale
            float tileScale = m_chunkLength / (sqrt(m_numberOfTiles) * m_texture[randomTexture].getSize().x); 

            m_tiles[counter].setScale(tileScale, tileScale);
            m_tiles[counter].setPosition(tilePosition);

            //move tile position down
            tilePosition = sf::Vector2f(tilePosition.x, tilePosition.y + tileLength);
            counter++;
        }
        //set the position to the next column
        tilePosition = sf::Vector2f(tilePosition.x + tileLength, m_position.y);
    }
}

/**
 * @brief returns a vector of all tiles 
 * 
 * @return std::vector<sf::Sprite> 
 */
std::vector<sf::Sprite> Chunk::getTiles() {
    //return tiles to draw them
    return m_tiles;
}

/**
 * @brief returns the position
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Chunk::getPosition() {
    return m_position;
}
