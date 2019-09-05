#ifndef ROGUELIKE_FOGGO_H
#define ROGUELIKE_FOGGO_H

#include "../engine/GameObject.h"
#include "PictureGO.h"
#include "../ConstSettings.h"

class FogGO : public GameObject {
    int baseAlpha;
    int animationIteration = 0;
    int fogCount;

    std::vector<PictureGO> fogElements;

    void updateFogLayer(int fogId, int allFogCount);

public:
    FogGO(ResourceLoader* resourceLoader1, int baseAlpha, int fogCount = 3) : GameObject(resourceLoader1), baseAlpha(baseAlpha), fogCount(fogCount) {

        for (int i = 0; i < fogCount; i++) {
            fogElements.emplace_back(resourceLoader1, "../resources/fog.png");
            fogElements.at(i).setYPos(HEIGHT/2.0);
        }
    };

    void update(Stage& stage) override;

protected:
    void draw(sf::RenderWindow& window) override;

};

#endif
