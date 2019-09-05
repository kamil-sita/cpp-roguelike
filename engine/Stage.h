#ifndef ROGUELIKE_STAGE_H
#define ROGUELIKE_STAGE_H

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "StageManager.h"
#include "ResourceLoader.h"

class GameObject;
class StageManager;

/**
 * Quasi interface for various stage. Stage is basic container for GameObjects that updates them and draws them.
 */
class Stage {

    std::vector<std::shared_ptr<GameObject>> gameObjects;
    StageManager& stageManager;
    ResourceLoader& resourceLoader;
    double deltaTime = 1;
protected:
    /**
     * Adds GameObject to stage. GameObjects are drawn in the same order as they were added.
     */
    void add(std::shared_ptr<GameObject> gameObject);
    ResourceLoader* getResourceLoader();
    virtual void updateScene();
    void updateAllObjects();

public:
    Stage(ResourceLoader& resourceLoader, StageManager& stageManager) : resourceLoader(resourceLoader), stageManager(stageManager) {

    };

    void draw(sf::RenderWindow& window);
    void update(double deltaTime);

    StageManager& getStageManager() const;

    double delta() const;

    std::vector<std::shared_ptr<GameObject>> getGameObjects();


};
#endif
