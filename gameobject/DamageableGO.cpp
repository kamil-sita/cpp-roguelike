#include <SFML/Graphics/RectangleShape.hpp>
#include "DamageableGO.h"
#include "../ConstSettings.h"


bool DamageableGO::isTilePosChanged() const {
    return tilePosChanged;
}


bool DamageableGO::checkNewPosition(double x, double y, std::shared_ptr<LevelTiles> &lt) {
    auto a = getNewTilePosition({x, y});
    auto b = getNewTilePosition({x + SIZE_OF_HITBOX_CHECKING, y + SIZE_OF_HITBOX_CHECKING});
    auto c = getNewTilePosition({x + SIZE_OF_HITBOX_CHECKING, y - SIZE_OF_HITBOX_CHECKING});
    auto d = getNewTilePosition({x - SIZE_OF_HITBOX_CHECKING, y + SIZE_OF_HITBOX_CHECKING});
    auto e = getNewTilePosition({x - SIZE_OF_HITBOX_CHECKING, y - SIZE_OF_HITBOX_CHECKING});
    return lt->isWalkable(b.x, b.y) && lt->isWalkable(a.x, a.y) && lt->isWalkable(c.x, c.y) &&
           lt->isWalkable(d.x, d.y) && lt->isWalkable(e.x, e.y);

}

void DamageableGO::drawHealthBar(sf::RenderWindow& window) {
    if (!alive) return;
    auto pos = getTopLeftSprite();
    pos.y -= 10;
    auto outlinePos = pos;
    outlinePos.x -= 1;
    outlinePos.y -= 1;

    sf::Color healthBarColor(40, 240, 40);
    sf::Color backgroundHPColor(240, 40, 40);
    sf::Color outlineColor(10, 10, 10);
    sf::Color shading(10, 10, 10, 96);

    sf::RectangleShape rectangle;

    rectangle.setSize(sf::Vector2f(width*scaling + 2, 5 + 2));
    rectangle.setPosition(outlinePos);
    rectangle.setFillColor(outlineColor);
    window.draw(rectangle);

    rectangle.setSize(sf::Vector2f(width*scaling, 5));
    rectangle.setPosition(pos);
    rectangle.setFillColor(backgroundHPColor);
    window.draw(rectangle);

    rectangle.setSize(sf::Vector2f(width*scaling * (healthPoints/maxHealthPoints), 5));
    rectangle.setFillColor(healthBarColor);
    window.draw(rectangle);

    pos.y += 3;
    rectangle.setPosition(pos);
    rectangle.setFillColor(shading);
    rectangle.setSize(sf::Vector2f(width * scaling, 2));
    window.draw(rectangle);

}

double DamageableGO::getHealthPoints() const {
    return healthPoints;
}

double DamageableGO::getMaxHealthPoints() const {
    return maxHealthPoints;
}

void DamageableGO::restoreHealth(double val)  {
    healthPoints += val;
    if (healthPoints > maxHealthPoints) {
        healthPoints = maxHealthPoints;
    }
}

void DamageableGO::restoreHealth()  {
    restoreHealth(maxHealthPoints);
}

void DamageableGO::dealDamage(double val) {
    healthPoints -= val;
    if (healthPoints <= 0) {
        setAlive(false);
    }
}

const bool DamageableGO::isAlive()  {
    return alive;
}

void DamageableGO::setAlive(bool val) {
    alive = val;
}
