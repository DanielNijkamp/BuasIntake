#include "SpriteLoader.h"
#include <iostream>

sf::Sprite SpriteLoader::LoadSprite(const std::string& name) const
{
    if (textures.find(name) == textures.end()){
        sf::Texture texture;
        std::string fullPath = path + name;
        if (!texture.loadFromFile(fullPath)) {
            std::cout << "Failed to load sprite texture!" << '\n';
            return {};
        }
        textures[name] = texture;
    }
    std::cout << "Loaded sprite: " << name << " successfully" << '\n';
    return sf::Sprite(textures[name]);
}
