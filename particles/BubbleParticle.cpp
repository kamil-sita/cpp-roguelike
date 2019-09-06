#include <cmath>
#include "BubbleParticle.h"

BubbleParticle::BubbleParticle(ResourceLoader* resourceLoader1, int x, int y) : SimpleParticle(resourceLoader1, "../resources/bubble.png", 0.5), x(x), y(y) {

}

void BubbleParticle::update(Stage& stage) {
    iteration += stage.delta();
    x += 0.2 * sin(iteration);
    y -= 0.3;
}

void BubbleParticle::draw(sf::RenderWindow& window) {
    sprite.setPosition(x, y);
    window.draw(sprite);
}
