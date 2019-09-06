#include "ParticleSystem.h"

void ParticleSystem::update(Stage& stage) {
    for (int i = 0; i < particles.size(); i++) {
        auto& particle = particles.at(i);
        if (particle->isMarkedForDestruction()) {
            particles.erase(particles.begin() + i);
        } else {
            particle->update(stage);
        }
    }
}

void ParticleSystem::render(sf::RenderWindow& window) {
    for (auto& particle : particles) {
        particle->renderCall(window);
    }
}

void ParticleSystem::add(std::shared_ptr<ParticleGO> particle) {
    particles.push_back(particle);
}
