#ifndef ROGUELIKE_ENEMYGO_H
#define ROGUELIKE_ENEMYGO_H
#include "../DamageableGO.h"
#include "../../levels/LevelTiles.h"
#include "../PlayerGO.h"
#include "../../Direction.h"
#include "../../levels/LevelTilesPathfinding.h"
#include "EnemiesGO.h"
#include "EnemyType.h"

class PlayerGO;
class EnemiesGO;
class EnemyGO : public DamageableGO {
    EnemyType enemyType;

    Direction movingDir = Direction::north;
    std::weak_ptr<LevelTiles> level;
    double speed; //relative speed
    sf::Vector2<int> targetPositionGrid;
    sf::Vector2<int> playerPos;
    bool playerPosChanged = false;
    bool pathFound = false;
    double hitByBulletSpeedModifier = 1;
    double animationIteration = 0;
    double slowdownSpeedModifier; //speed slowdown
    std::weak_ptr<PlayerGO> player;

    sf::Vector2<float> graphicalSpritePosition;

    void generatePath();
    void addDamageParticles(const Stage& stage);
protected:
    void draw(sf::RenderWindow& window) override;

public:
    EnemyGO(ResourceLoader *resourceLoader1, int maxHealthPoints1, EnemyType enemyType);

    void update(Stage &stage) override;
    void pollMovement(Stage& stage, PlayerGO &pl);
    sf::Vector2<float> simpleMove(double deltaTime);
    void setLevel(const std::shared_ptr<LevelTiles> &level);
    void snapToGrid();
    sf::Vector2<int> getGridVector(sf::Vector2<int> gridPos);
    void calcTargetPosition();
    void bulletHitSlowdown();
    void setPlayer(const std::weak_ptr<PlayerGO>& player);

};


#endif
