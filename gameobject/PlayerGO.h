#ifndef ROGUELIKE_PLAYERGO_H
#define ROGUELIKE_PLAYERGO_H


#include "DamageableGO.h"
#include "../levels/LevelTiles.h"
#include "ProjectilesGO.h"

class ProjectilesGO;
class EnemiesGO;
class PlayerGO : public DamageableGO {

    Direction lookingDirection = south;
    std::shared_ptr<LevelTiles> level;
    std::shared_ptr<ProjectilesGO> projectiles;
    std::weak_ptr<EnemiesGO> enemies;
    sf::Clock bulletCooldownClock;
    sf::Clock tumbleCooldownClock;
    sf::Clock tumbleClock;
    sf::Clock playerDamageClock;
    double tumblingMultiplier = 1.0;
    bool tumbling = false;
    bool shielding = false;
    double bulletDamage = PROJECTILE_DMG;
    int iteration = 0;

protected:
    void draw(sf::RenderWindow& window) override;

public:
    void setEnemies(const std::weak_ptr<EnemiesGO> &enemies);

    PlayerGO(ResourceLoader* resLoad, Stage* stage);

    void setProjectiles(const std::shared_ptr<ProjectilesGO> &projectiles);

    void setLevel(const std::shared_ptr<LevelTiles> &level);

    void dealDamageTimed();
    void update(Stage &stage) override;
    void pollMovement(Stage& stage);
    void checkAndMove(double deltaTime);
    sf::Vector2<float> simpleMove(double deltaTime);

    void increaseDamage(double value) {
        bulletDamage += value;
    }


};


#endif
