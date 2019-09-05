#include "Stage.h"
#include "GameObject.h"

void Stage::draw(sf::RenderWindow& window) {
    for (const auto &object : gameObjects) {
        object->renderCall(window);
    }
}

void Stage::update(double deltaTime) {
    this->deltaTime = deltaTime;
    updateScene();
}

void Stage::add(std::shared_ptr<GameObject> gameObject) {
    gameObjects.push_back(gameObject);
    gameObject.get()->setStage(this);
}

ResourceLoader* Stage::getResourceLoader() {
    return &resourceLoader;
}

StageManager& Stage::getStageManager() const {
    return stageManager;
}

void Stage::updateScene() {

}

double Stage::delta() const {
    return deltaTime;
}

std::vector<std::shared_ptr<GameObject>> Stage::getGameObjects() {
    return gameObjects;
}

void Stage::updateAllObjects() {
    for (auto& gameObject : getGameObjects()) {
        gameObject->update(*this);
    }
}

