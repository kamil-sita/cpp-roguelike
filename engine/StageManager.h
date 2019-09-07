#ifndef ROGUELIKE_STAGEMANAGER_H
#define ROGUELIKE_STAGEMANAGER_H

#include "Stage.h"
#include "ResourceLoader.h"
#include "Inputs.h"
#include "ApplicationStatus.h"

class MenuStage;
class Stage;

class StageManager {
private:
    double averageDeltaTimeError = 1;

    std::shared_ptr<Stage> currentStage;
    ResourceLoader& resourceLoader;
    Inputs& inputs;
    std::shared_ptr<MenuStage> menuStage;
    bool restart = false;
    bool exit = false;
public:
    StageManager(ResourceLoader& resourceLoader1, Inputs& inputHandler)
    : resourceLoader(resourceLoader1),
      inputs(inputHandler) {

    };

    const std::shared_ptr<MenuStage>& getMenuStage() const;

    void setMenuStage(const std::shared_ptr<MenuStage>& menuStage);

    void setStage(std::shared_ptr<Stage> currentStage);

    void draw(sf::RenderWindow& window);

    ResourceLoader &getResourceLoader() const;

    Inputs &getInputs() const;

    bool isRestart() const;

    void setRestart(bool restart);

    void update(double deltaTime);

    void setStageMenuStage();

    double getAmortizedAverageDeltaTimeError() const;

    void setAverageDeltaTimeError(double averageDeltaTime);

    bool isExit() const;

    void setExit(bool exit);

    ApplicationStatus getApplicationStatus();
};


#endif