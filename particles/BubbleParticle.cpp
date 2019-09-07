#include <cmath>
#include "BubbleParticle.h"
#include "../Random.h"

BubbleParticle::BubbleParticle(ResourceLoader* resourceLoader1, int x, int y) : SimpleParticle(resourceLoader1, "../resources/bubble.png", 0.5), x(x), y(y) {
    iteration = getRandom(0, 20);
}

void BubbleParticle::update(Stage& stage) {
    iteration += stage.delta();
    x += 0.2 * sin(iteration);
    y -= 0.3;
}

void BubbleParticle::draw(sf::RenderWindow& window) {
    sprite.setPosition(x, y);
    double scale = std::min(0.3, 0.6 * sin(iteration * 0.05));
    sprite.setScale(scale, scale);
    window.draw(sprite);
}
