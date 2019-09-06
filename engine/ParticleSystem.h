#ifndef ROGUELIKE_PARTICLESYSTEM_H
#define ROGUELIKE_PARTICLESYSTEM_H


#include "GameObject.h"
#include "../particles/ParticleGO.h"

class ParticleSystem {

    std::vector<std::shared_ptr<ParticleGO>> particles;

public:
    void update(Stage& stage);
    void add(std::shared_ptr<ParticleGO> particle);
    void render(sf::RenderWindow& window);
};


#endif