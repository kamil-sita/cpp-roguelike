#ifndef ROGUELIKE_SMOKEPARTICLE_H
#define ROGUELIKE_SMOKEPARTICLE_H

#include "SimpleParticle.h"

class SmokeParticle : public SimpleParticle {
    double x;
    double y;
    double iteration = 0;
    double scale;
    double alpha = 1;
    double expansionScale = 1;
    double whiteness;
    double colorVariety;
public:
    SmokeParticle(ResourceLoader* resourceLoader1, int x, int y, double whiteness);
    void update(Stage& stage) override;

protected:
    void draw(sf::RenderWindow& window) override;
};


#endif
