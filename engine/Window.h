#ifndef SIMULATOR_WINDOWACTIONS_H
#define SIMULATOR_WINDOWACTIONS_H

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "StageManager.h"
#include "ApplicationStatus.h"

class Inputs;
class Window {
    sf::RenderWindow window;
    ResourceLoader resourceLoader;
    Inputs inputs;
    StageManager stageManager;

    int renderedFrameCount = 0;

    ApplicationStatus pollKeyboardAndWindowStatus(StageManager& stageManager);
    void calculateFpsAndAverageDeltaTime(sf::Clock& fpsClock, StageManager& stageManager);
    void setFramerateAsWindowTitle(double realFrames);
public:
    Window();
    ApplicationStatus run();
};



#endif
