#ifndef ROGUELIKE_DAMAGEABLEGO_H
#define ROGUELIKE_DAMAGEABLEGO_H


#include "SpriteGO.h"
#include "../levels/LevelTiles.h"

class DamageableGO : public SpriteGO {
protected:
    double healthPoints;
    double maxHealthPoints;
    bool alive = true;

    double speedX = 0;
    double speedY = 0;

    bool checkNewPosition(double x, double y, std::shared_ptr<LevelTiles>& lt);

public:
    DamageableGO(ResourceLoader* resourceLoader1, int maxHealthPoints1) : SpriteGO(resourceLoader1),
    maxHealthPoints(maxHealthPoints1), healthPoints(maxHealthPoints1) {

    };


    bool isTilePosChanged() const;

    void drawHealthBar(sf::RenderWindow& window);

    void setAlive(bool val);

    const bool isAlive();

    void dealDamage(double val);

    void restoreHealth();

    void restoreHealth(double val);

    double getHealthPoints() const;

    double getMaxHealthPoints() const;
};

#endif
