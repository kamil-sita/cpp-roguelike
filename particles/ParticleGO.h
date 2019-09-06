#ifndef ROGUELIKE_PARTICLE_GO
#define ROGUELIKE_PARTICLE_GO

#include "../engine/GameObject.h"

class ParticleGO : public GameObject {
public:
    ParticleGO(ResourceLoader* resourceLoader) : GameObject(resourceLoader) {

    }
    virtual bool isMarkedForDestruction() = 0;
};


#endif
