#include "ProjectilesGO.h"

ProjectilesGO::ProjectilesGO(ResourceLoader* resourceLoader) : GameObject(resourceLoader) {


}

void ProjectilesGO::renderCall(sf::RenderWindow& window) {
    for (auto& projectile : projectiles) {
        projectile.renderCall(window);
    }
}

void ProjectilesGO::update(Stage &stage) {
    for (int i = 0; i < projectiles.size(); i++) {
        auto& proj = projectiles.at(i);
        if (proj.isMarkedForDestruction()) {
            projectiles.erase(projectiles.begin() + i);
            i--;
        } else {
            proj.update(stage);
        }
    }
}

void ProjectilesGO::draw(sf::RenderWindow& window) {

}

void ProjectilesGO::add(ProjectileGO &&projectile)  {
    projectiles.push_back(projectile);
}

void ProjectilesGO::clear() {
    projectiles.clear();
}

