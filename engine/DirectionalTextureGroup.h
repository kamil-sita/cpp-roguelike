#ifndef ROGUELIKE_DIRECTIONALTEXTUREGROUP_H
#define ROGUELIKE_DIRECTIONALTEXTUREGROUP_H

#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <memory>
#include "../Direction.h"

class DirectionalTextureGroup {
    double iteration;
    Direction dir = south;
    std::vector<std::shared_ptr<sf::Texture>> northTextures;
    std::vector<std::shared_ptr<sf::Texture>> eastTextures;
    std::vector<std::shared_ptr<sf::Texture>> westTextures;
    std::vector<std::shared_ptr<sf::Texture>> southTextures;
public:
    void add(std::shared_ptr<sf::Texture> text, Direction dir);
    void setDirection(Direction direc);

    void updateIteration(double it);
    std::shared_ptr<sf::Texture> getTexture();
};


#endif
