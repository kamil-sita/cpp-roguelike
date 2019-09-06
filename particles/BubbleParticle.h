#ifndef ROGUELIKE_BUBBLEPARTICLE_H
#define ROGUELIKE_BUBBLEPARTICLE_H


#include "SimpleParticle.h"

class BubbleParticle : public SimpleParticle {
    double x;
    double y;
    double iteration = 0;
public:
    BubbleParticle(ResourceLoader* resourceLoader1, int x, int y);
    void update(Stage& stage) override;

protected:
    void draw(sf::RenderWindow& window) override;
};


#endif
