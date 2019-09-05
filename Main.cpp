#include "engine/Window.h"
#include "levels/LevelTiles.h"
#include "levels/LevelTilesPathfinding.h"

//macro that enables range checks in some functions
#define RANGE_CHECKS_ENABLED false


int main() {
    if (RANGE_CHECKS_ENABLED) {
        std::cerr << "RANGE_CHECKS_ENABLED" << std::endl;
    }
    try {
        ApplicationStatus windowOutput = ApplicationStatus::none;
        while (windowOutput != ApplicationStatus::endApplication) {
            Window w;
            windowOutput = w.run();
        }
    } catch (std::exception& s) {
        std::cerr << s.what() << std::endl;
    }
    return 0;
}

