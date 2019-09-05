#ifndef ROGUELIKE_TEXTUREGROUP_H
#define ROGUELIKE_TEXTUREGROUP_H


#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <memory>

class TextureGroup {
private:
    std::vector<std::shared_ptr<sf::Texture>> textures;
public:
    void add(const std::shared_ptr<sf::Texture>& texture);
    const std::shared_ptr<sf::Texture>& get(int id);

};


#endif
