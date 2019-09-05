#include "DirectionalTextureGroup.h"

void DirectionalTextureGroup::add(std::shared_ptr<sf::Texture> text, Direction dir)  {
    switch (dir) {
        case west:
            westTextures.push_back(text);
            break;
        case north:
            northTextures.push_back(text);
            break;
        case east:
            eastTextures.push_back(text);
            break;
        case south:
            southTextures.push_back(text);
            break;
    }
}

void DirectionalTextureGroup::setDirection(Direction direc) {
    DirectionalTextureGroup::dir = direc;
}

void DirectionalTextureGroup::updateIteration(double it) {
    iteration += it;
}

std::shared_ptr<sf::Texture> DirectionalTextureGroup::getTexture()  {
    switch (dir) {
        case west:
            return westTextures.at((int) (iteration) % westTextures.size());
            break;
        case north:
            return northTextures.at((int) (iteration) % northTextures.size());
            break;
        case east:
            return eastTextures.at((int) (iteration) % eastTextures.size());
            break;
        case south:
            return southTextures.at((int) (iteration) % southTextures.size());
            break;
    }
    return nullptr;
}