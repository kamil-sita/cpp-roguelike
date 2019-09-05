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
    double alpha1 = sin(animationIteration * 0.01 - getDisplacement(fogId, allFogCount));
    if (alpha1 < 0) alpha1 = 0;
    fogElements.at(fogId).setAlpha(alpha1 * baseAlpha);
    fogElements.at(fogId).setXPos(WIDTH/2.0 + (animationIteration - (int)(getDisplacement(fogId, allFogCount) * 100)) % 314 - 100);
}

void FogGO::draw(sf::RenderWindow& window) {
    for (auto& fog : fogElements) {
        fog.renderCall(window);
    }
}
