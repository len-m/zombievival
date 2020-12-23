#ifndef RESORUCEMANAGER_H
#define RESORUCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <memory>

class ResourceManager {
    public:
        //texture
        void setTexture(std::string name, std::string fileName);
        std::shared_ptr<sf::Texture> getTexture(std::string name);
        
        //font
        void setFont(std::string name, std::string fileName);
        std::shared_ptr<sf::Font> getFont(std::string name);

        //sound
        void setSound(std::string name, std::string fileName);
        std::shared_ptr<sf::SoundBuffer> getSound(std::string name);
    private:
        std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
        std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts;
        std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> sounds;
};

#endif