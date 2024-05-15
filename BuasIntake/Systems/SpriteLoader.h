#pragma once
#include <map>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class SpriteLoader final
{
public:
    explicit SpriteLoader(std::string path) : path(std::move(path)){}

    sf::Sprite LoadSprite(const std::string& name) const;
private:
    const std::string path;
    mutable std::map<std::string, sf::Texture> textures;
};
