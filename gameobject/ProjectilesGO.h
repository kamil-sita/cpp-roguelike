#ifndef ROGUELIKE_PROJECTILESGO_H
#define ROGUELIKE_PROJECTILESGO_H


#include "../engine/GameObject.h"
#include "ProjectileGO.h"

class ProjectilesGO : public GameObject {
    std::vector<ProjectileGO> projectiles;

protected:
    void draw(sf::RenderWindow& window) override;

public:
    ProjectilesGO(ResourceLoader* resourceLoader);

    void add(ProjectileGO&& projectile);

    void renderCall(sf::RenderWindow& window) override;

    void update(Stage &stage) override;

    void clear();

};


#endif
