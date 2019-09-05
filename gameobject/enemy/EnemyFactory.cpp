#include "EnemyFactory.h"
#include "../../Random.h"

EnemyGO createEnemy(int levelId, ResourceLoader& resourceLoader) {
    double random = getRandom(0, 1);
    EnemyType enemyType;
    if (random <= 0.1) {
        enemyType = EnemyType::ghost;
    } else if (random <= 0.25) {
        enemyType = EnemyType::tank;
    } else {
        enemyType = EnemyType::normal;
    }

    return std::move(EnemyGO(&resourceLoader, levelId * ENEMY_HP_PER_LEVEL, enemyType));
}
