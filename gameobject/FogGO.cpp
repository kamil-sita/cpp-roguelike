#include <math.h>
#include "FogGO.h"

inline double getDisplacement(double thisFog, double fogCount) {
    return - M_PI * 2.0 * thisFog / fogCount;
}

void FogGO::update(Stage& stage) {
    animationIteration++;
    for (int i = 0; i < fogCount; i++) {
        updateFogLayer(i, fogCount);
    }
}

void FogGO::updateFogLayer(int fogId, int allFogCount) {
    double alpha = sin(animationIteration * 0.01 - getDisplacement(fogId, allFogCount));
    if (alpha < 0) alpha = 0;
    fogElements.at(fogId).setAlpha(alpha * baseAlpha);
    fogElements.at(fogId).setXPos(WIDTH/2.0 + (animationIteration - (int)(getDisplacement(fogId, allFogCount) * 100)) % 314 - 100);
}

void FogGO::draw(sf::RenderWindow& window) {
    for (auto& fog : fogElements) {
        fog.renderCall(window);
    }
}

FogGO::FogGO(ResourceLoader* resourceLoader1, int baseAlpha, int fogCount) : GameObject(resourceLoader1), baseAlpha(baseAlpha), fogCount(fogCount) {
    for (int i = 0; i < fogCount; i++) {
        fogElements.emplace_back(resourceLoader1, "../resources/fog.png");
        fogElements.at(i).setYPos(HEIGHT/2.0);
    }
}
