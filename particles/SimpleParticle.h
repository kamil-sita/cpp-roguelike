#ifndef ROGUELIKE_SIMPLEPARTICLE_H
#define ROGUELIKE_SIMPLEPARTICLE_H

#include <SFML/Graphics/Sprite.hpp>
#include "ParticleGO.h"

class SimpleParticle : public ParticleGO{
private:
    double secondsToLive;
    sf::Clock clock;
protected:
    sf::Sprite sprite;
public:
    SimpleParticle(ResourceLoader* resourceLoader1, const char* name, double secondsToLive);

    bool isMarkedForDestruction() override;
};

#endif