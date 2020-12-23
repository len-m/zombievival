#include "ResourceManager.h"
/**
 * @brief adds a texture to textures map
 * 
 * @param name name of texture
 * @param fileName name of file
 */
void ResourceManager::setTexture(std::string name, std::string fileName) {
    textures[name].reset(new sf::Texture);
    textures[name]->loadFromFile(fileName);
}
/**
 * @brief returns ptr of texture according to name passed
 * 
 * @param name name of texture
 * @return std::shared_ptr<sf::Texture> 
 */
std::shared_ptr<sf::Texture> ResourceManager::getTexture(std::string name) {
    return textures[name];
}

/**
 * @brief adds a font to fonts map
 * 
 * @param name name of font
 * @param fileName name of file
 */    
void ResourceManager::setFont(std::string name, std::string fileName) {
    fonts[name].reset(new sf::Font);
    fonts[name]->loadFromFile(fileName);
}
/**
 * @brief returns ptr of font according to name passed
 * 
 * @param name name of font
 * @return std::shared_ptr<sf::Font> 
 */
std::shared_ptr<sf::Font> ResourceManager::getFont(std::string name) {
    return fonts[name];
}

/**
 * @brief adds a sound to sounds map
 * 
 * @param name name of sound
 * @param fileName name of file
 */
void ResourceManager::setSound(std::string name, std::string fileName) {
    sounds[name].reset(new sf::SoundBuffer);
    sounds[name]->loadFromFile(fileName);
}
/**
 * @brief returns ptr of sound according to name passed
 * 
 * @param name name of sound
 * @return std::shared_ptr<sf::SoundBuffer> 
 */
std::shared_ptr<sf::SoundBuffer> ResourceManager::getSound(std::string name) {
    return sounds[name];
}