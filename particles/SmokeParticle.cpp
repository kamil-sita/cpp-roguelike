#include <cmath>
#include "SmokeParticle.h"
#include "../Random.h"

SmokeParticle::SmokeParticle(ResourceLoader* resourceLoader1, int x, int y, double whiteness) : SimpleParticle(resourceLoader1, "../resources/smoke.png", 0.9),
    x(x), y(y), whiteness(whiteness) {
    iteration = getRandom(0, 20);
    scale = getRandom(0.8, 1.4);
    colorVariety = getRandom(-0.1, 0.1);
}

void SmokeParticle::update(Stage& stage) {
    iteration += stage.delta();
    alpha *= 0.99;
    expansionScale += 0.01;
}

void SmokeParticle::draw(sf::RenderWindow& window) {
    double scaleIt = std::min(0.8, sin(iteration * 0.05));
    sprite.setScale(scaleIt, scaleIt);
    sprite.scale(scale, scale);
    sprite.scale(expansionScale, expansionScale);
    int color = 255 * (whiteness + colorVariety);
    int alphaOut = 255 * (alpha + colorVariety);

    //fixing the position, assuming that the size of texture is X by X (width == height)
    double size = sprite.getTexture()->getSize().x * sprite.getScale().x;
    double newX = x - size/2;
    double newY = y - size/2;

    sprite.setPosition(newX, newY);

    color = std::min(255, std::max(0, color));
    alphaOut = std::min(255, std::max(0, alphaOut));

    sprite.setColor(sf::Color(color, color, color, alphaOut));
    window.draw(sprite);
}
