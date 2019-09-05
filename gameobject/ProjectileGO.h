#ifndef ROGUELIKE_PROJECTILEGO_H
#define ROGUELIKE_PROJECTILEGO_H

#include "PictureGO.h"
#include "../Direction.h"
#include "../levels/LevelTiles.h"
#include "../ConstSettings.h"

class ProjectileGO : public PictureGO {
    Direction movingDirection;
    bool markedForDestruction = false;
    std::shared_ptr<LevelTiles> levelTiles;
    int hitboxWidth = 16;
    int damage = PROJECTILE_DMG;
    void simpleMove();

protected:
    sf::Vector2f getTopLeftHitbox() override;

    sf::Vector2f getBottomRightHitbox() override;
public:
    ProjectileGO(ResourceLoader* resourceLoader1, Direction movingDirection, sf::Vector2<int> pos, std::shared_ptr<LevelTiles> lt, int damage);

    void update(Stage &stage) override;

    bool isMarkedForDestruction() const;


};


#endif
