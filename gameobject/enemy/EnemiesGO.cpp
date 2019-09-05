#include "EnemiesGO.h"

EnemiesGO::EnemiesGO(ResourceLoader* resources) : GameObject(resources) {

}

void EnemiesGO::add(EnemyGO &&en, std::shared_ptr<EnemiesGO> thisObject)  {
    std::weak_ptr<EnemiesGO> e = thisObject;
    enemies.push_back(en);
}

void EnemiesGO::add(EnemyGO &en, std::shared_ptr<EnemiesGO> thisObject)  {
    std::weak_ptr<EnemiesGO> e = thisObject;
    enemies.push_back(en);
}

void EnemiesGO::removeAll()  {
    enemies.clear();
}

void EnemiesGO::updatePathfinder(Stage &st, std::shared_ptr<PlayerGO> player, std::shared_ptr<LevelTiles> lt)  {
    for (auto& en : enemies) {
        en.setPlayer(player);
        en.setLevel(lt);
        en.pollMovement(st, *player.get());
    }
}

void EnemiesGO::update(Stage &stage)  {
    for (auto& enemy : enemies) {
        enemy.update(stage);
    }
}

void EnemiesGO::renderCall(sf::RenderWindow& window) {
}

std::vector<EnemyGO> &EnemiesGO::getEnemies() {
    return enemies;
}

void EnemiesGO::draw(sf::RenderWindow& window) {

}

void EnemiesGO::trueRenderCall(sf::RenderWindow& window) {
    for (auto& enemy : enemies) {
        enemy.renderCall(window);
    }
}

int EnemiesGO::aliveEnemiesCount() {
    int i = 0;
    for (auto& enemy : enemies) {
        if (enemy.isAlive()) i++;
    }
    return i;
}


