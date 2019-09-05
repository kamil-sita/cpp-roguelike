#ifndef ROGUELIKE_SPRITEGO_H
#define ROGUELIKE_SPRITEGO_H

#include "../engine/GameObject.h"
#include "../engine/DirectionalTextureGroup.h"

/**
 * GameObject that graphically consists of multiple sprites
 */
class SpriteGO : public GameObject {
protected:
    DirectionalTextureGroup sprites;
public:
    SpriteGO(ResourceLoader* resourceLoader1) : GameObject(resourceLoader1) {

    };
};


#endif