#include "TextureGroup.h"

void TextureGroup::add(const std::shared_ptr<sf::Texture>& texture)  {
    textures.push_back(texture);
}

const std::shared_ptr<sf::Texture>& TextureGroup::get(int id) {
    return textures.at(id % textures.size());
}