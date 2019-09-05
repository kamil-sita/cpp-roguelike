#ifndef ROGUELIKE_ENEMIESGO_H
#define ROGUELIKE_ENEMIESGO_H

#include "EnemyGO.h"
#include "../../levels/LevelTiles.h"
#include "../PlayerGO.h"

class PlayerGO;
class EnemyGO;
///EnemiesGO is composite for many EnemyGO.
class EnemiesGO : public GameObject {
    std::vector<EnemyGO> enemies;

protected:
    void draw(sf::RenderWindow& window) override;
public:

    EnemiesGO(ResourceLoader* resources);

    void add(EnemyGO&& en, std::shared_ptr<EnemiesGO> thisObject);
    void add(EnemyGO &en, std::shared_ptr<EnemiesGO> thisObject);
    void removeAll();

    void updatePathfinder(Stage& st, std::shared_ptr<PlayerGO> player, std::shared_ptr<LevelTiles> lt);

    void update(Stage &stage) override;

    void renderCall(sf::RenderWindow& window) override;
    void trueRenderCall(sf::RenderWindow& window);
    int aliveEnemiesCount();

    std::vector<EnemyGO> &getEnemies();
};


#endif
