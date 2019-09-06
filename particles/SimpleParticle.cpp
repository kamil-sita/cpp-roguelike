#include "SimpleParticle.h"

SimpleParticle::SimpleParticle(ResourceLoader* resourceLoader1, const char* name, double secondsToLive) : ParticleGO(resourceLoader1), sprite(), secondsToLive(secondsToLive) {
    clock.restart();
    sprite = sf::Sprite(*resourceLoader1->load(name));
}


bool SimpleParticle::isMarkedForDestruction() {
    return clock.getElapsedTime().asSeconds() > secondsToLive;
}
