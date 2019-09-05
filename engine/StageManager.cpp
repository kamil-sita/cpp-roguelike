#include "StageManager.h"
#include "../stages/MenuStage.h"


void StageManager::update(double deltaTime) {
    currentStage.get()->update(deltaTime);
}

void StageManager::setStage(std::shared_ptr<Stage> currentStage) {
    this->currentStage = currentStage;
}

ResourceLoader &StageManager::getResourceLoader() const {
    return resourceLoader;
}

void StageManager::draw(sf::RenderWindow& window) {
    currentStage->draw(window);
}

Inputs &StageManager::getInputs() const {
    return inputs;
}

bool StageManager::isRestart() const {
    return restart;
}

void StageManager::setRestart(bool restartV) {
    StageManager::restart = restartV;
}


bool StageManager::isExit() const {
    return exit;
}

void StageManager::setExit(bool exit) {
    StageManager::exit = exit;
}

const std::shared_ptr<MenuStage>& StageManager::getMenuStage() const {
    return menuStage;
}

void StageManager::setMenuStage(const std::shared_ptr<MenuStage>& menuStage) {
    StageManager::menuStage = menuStage;
}

void StageManager::setStageMenuStage() {
    this->setStage(getMenuStage());
}

double StageManager::getAmortizedAverageDeltaTimeError() const {
    if (fabs(averageDeltaTimeError - 1.0) < 0.05) {
        return 1.0;
    }
    return averageDeltaTimeError;
}

void StageManager::setAverageDeltaTimeError(double averageDeltaTime) {
    StageManager::averageDeltaTimeError = averageDeltaTime;
}

ApplicationStatus StageManager::getApplicationStatus() {
    if (isExit()) {
        return ApplicationStatus::endApplication;
    } else if (isRestart()) {
        return ApplicationStatus::restartApplication;
    } else {
        return ApplicationStatus::none;
    }
}

