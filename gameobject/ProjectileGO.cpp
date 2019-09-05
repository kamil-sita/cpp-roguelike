#include "ProjectileGO.h"
#include "../ConstSettings.h"
#include "../stages/GameStage.h"

ProjectileGO::ProjectileGO(ResourceLoader* resourceLoader1, Direction movingDirection, sf::Vector2<int> pos,
        std::shared_ptr<LevelTiles> lt, int damage) : PictureGO(resourceLoader1), movingDirection(movingDirection), levelTiles(lt), damage(damage) {
    setTexture("../resources/projectile.png");
    setXPos(pos.x);
    setYPos(pos.y);
}


void ProjectileGO::update(Stage &stage) {
    if (markedForDestruction)
        return;


    simpleMove();
    auto pos = getTilePosition();
    if (!levelTiles->isWalkable(pos.x, pos.y)) {
        markedForDestruction = true;
        return;
    }

    auto gameStage = ((GameStage*) &stage);

    auto& enemiesColl = gameStage->getEnemies()->getEnemies();
    for (auto& enemy : enemiesColl) {
        if (enemy.isAlive() && enemy.intersects(*this)) {
            enemy.dealDamage(damage);
            enemy.bulletHitSlowdown();
            markedForDestruction = true;
        }
    }

}

void ProjectileGO::simpleMove() {
    auto vector = getDirectionVector(movingDirection);

    setXPos(xPos + BULLET_SPEED * vector.x);
    setYPos(yPos + BULLET_SPEED * vector.y);

}

bool ProjectileGO::isMarkedForDestruction() const {
    return markedForDestruction;
}

sf::Vector2f ProjectileGO::getTopLeftHitbox() {
    return {xPos - scaling*hitboxWidth/2, yPos - scaling*hitboxWidth/2};
}

sf::Vector2f ProjectileGO::getBottomRightHitbox() {
    return {xPos + scaling*hitboxWidth/2, yPos + scaling*hitboxWidth/2};
}
