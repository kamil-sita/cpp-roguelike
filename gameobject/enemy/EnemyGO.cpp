#include "EnemyGO.h"
#include "../../ConstSettings.h"
#include "../../Random.h"
#include <SFML/Graphics/Sprite.hpp>
#include <cmath>
#include "../../engine/ParticleSystem.h"
#include "../../particles/SmokeParticle.h"

EnemyGO::EnemyGO(ResourceLoader *resourceLoader1, int maxHealthPoints1, EnemyType enemyType) : DamageableGO(resourceLoader1, maxHealthPoints1), enemyType(enemyType) {


    sprites.add(resourceLoader1->load("../resources/enemy2.png"), north);
    sprites.add(resourceLoader1->load("../resources/enemy1.png"), east);
    sprites.add(resourceLoader1->load("../resources/enemy3.png"), west);
    sprites.add(resourceLoader1->load("../resources/enemy0.png"), south);


    width = PLAYER_AND_ENEMY_SIZE;
    height = PLAYER_AND_ENEMY_SIZE;
    speed = getRandom(0.9, 1);
    snapToGrid();

    if (enemyType == EnemyType::tank) {
        setScaling(1.3);
        this->maxHealthPoints *= 2;
        this->healthPoints = this->maxHealthPoints;
        this->speed *= 0.6;
    } else if (enemyType == EnemyType::ghost) {
        this->maxHealthPoints *= 0.4;
        this->healthPoints = this->maxHealthPoints;
        this->speed *= 1.25;
    }

}

void EnemyGO::update(Stage &stage) {
    double deltaTime = stage.delta();

    addDamageParticles(stage);

    if (!alive) {
        return;
    }

    auto tmpLevelLock = level.lock();
    auto pos = getTilePosition();
    auto tileOn = tmpLevelLock->getTileOn(pos.x, pos.y);
    if (tileOn == TileType::slowingFloor) {
        switch (enemyType) {
            case EnemyType::normal:
                this->dealDamage(0.0012 * getMaxHealthPoints() + 0.01);
                break;
            case EnemyType::tank:
                this->dealDamage(0.0006 * getMaxHealthPoints() + 0.01);
                break;
            case EnemyType::ghost:
                break;
        }
    }

    auto playerLock = player.lock();
    if (playerLock->intersects(*this)) {
        playerLock->dealDamageTimed();
    }

    if (!pathFound) {
        generatePath();
        return;
    }

    auto oldPos = getTilePosition();
    auto a = simpleMove(deltaTime);
    auto levelTmp = level.lock();
    auto oldGrid = getGridVector(targetPositionGrid);
    setXPos(a.x);
    setYPos(a.y);
    auto newGrid = getGridVector(targetPositionGrid);
    if (oldGrid != newGrid) {
        snapToGrid();
        generatePath();
    }
    auto newPos = getTilePosition();
    tilePosChanged = (oldPos != newPos);
    hitByBulletSpeedModifier = (15 * hitByBulletSpeedModifier + 1) / 16.0;
}

void EnemyGO::addDamageParticles(const Stage& stage) {

    const double Y_VARIETY = 6;
    const double X_VARIETY = 6;

    if (enemyType == EnemyType::ghost) return;

    if (!isAlive()) {
        if (getRandom(0, 1) > 0.6) {
            double x = xPos + getRandom(-X_VARIETY, X_VARIETY) + 6 * sin(animationIteration * 0.05);
            double y = yPos - height * 0.75 + getRandom(-Y_VARIETY, Y_VARIETY);

            stage.getParticleSystem()->add(std::make_shared<SmokeParticle>(resourceLoader, x, y, 0.3));
        }
    } else {

        if (healthPoints < maxHealthPoints) {
            double percentage = (healthPoints) / maxHealthPoints;
            if (getRandom(0, 1.04) > percentage && getRandom(0, 1) > 0.6) {

                double x = graphicalSpritePosition.x + width / 2 + getRandom(-X_VARIETY, X_VARIETY);
                double y = graphicalSpritePosition.y + height / 2 + getRandom(-Y_VARIETY, Y_VARIETY);

                sf::Vector2<int> vec = getDirectionVector(movingDir);
                x += -width / 2 * vec.x;
                y += -height / 2 * vec.y;

                stage.getParticleSystem()->add(
                        std::make_shared<SmokeParticle>(resourceLoader, x, y, healthPoints / maxHealthPoints)
                                );

            }
        }
    }

}

void EnemyGO::draw(sf::RenderWindow& window) {
    if (alive) {
        if (enemyType == EnemyType::tank) {
            animationIteration += 0.5;
        } else {
            animationIteration += 1;
        }
        drawHealthBar(window);
        sf::Sprite s;
        sprites.setDirection(movingDir);
        s.setTexture(*sprites.getTexture().get());
        s.setScale(1.0f * PLAYER_AND_ENEMY_SIZE/s.getTexture()->getSize().x * getScaling(), 1.0f * PLAYER_AND_ENEMY_SIZE/s.getTexture()->getSize().y * getScaling());
        auto pos = getTopLeftSprite();
        if (movingDir == north || movingDir == south) {
            pos.x += 3.5 * sin(0.12 * animationIteration);
        } else {
            pos.y += 3.5 * sin(0.12 * animationIteration);
        }
        graphicalSpritePosition = pos;
        s.setPosition(pos);

        sf::Uint8 blackout = slowdownSpeedModifier * 255;
        sf::Uint8 alpha = enemyType == EnemyType::ghost ? 96 : 255;
        s.setColor(sf::Color(
                    255,
                    blackout,
                    blackout,
                    alpha
                ));

        window.draw(s);
    } else {
        animationIteration += 1;

        auto text = resourceLoader->load("../resources/dead.png");
        sf::Sprite s;
        s.setTexture(*text);
        s.setScale(1.0f * PLAYER_AND_ENEMY_SIZE/s.getTexture()->getSize().x * getScaling(), 1.0f * PLAYER_AND_ENEMY_SIZE/s.getTexture()->getSize().y * getScaling());
        s.setPosition(getTopLeftSprite());
        sf::Uint8 alpha = enemyType == EnemyType::ghost ? 96 : 255;
        s.setColor(sf::Color(
                255,
                255,
                255,
                alpha
        ));

        window.draw(s);
    }
}

void EnemyGO::setLevel(const std::shared_ptr<LevelTiles> &level) {
    EnemyGO::level = level;
}

sf::Vector2<float> EnemyGO::simpleMove(double deltaTime) {
    auto a = getTilePosition();
    auto tmpLevelLock = level.lock();
    auto b = tmpLevelLock->getTileOn(a.x, a.y);
    slowdownSpeedModifier = 1;
    if (b == TileType::slowingFloor) slowdownSpeedModifier = 0.55;
    slowdownSpeedModifier *= hitByBulletSpeedModifier;
    sf::Vector2<float> newPos;

    speedX = 0;
    speedY = 0;
    if (movingDir == west) speedX = -DEFAULT_SPEED;
    if (movingDir == east) speedX = DEFAULT_SPEED;
    if (movingDir == north) speedY = -DEFAULT_SPEED;
    if (movingDir == south) speedY = DEFAULT_SPEED;

    newPos.x = (xPos + deltaTime * speed * speedX * slowdownSpeedModifier);
    newPos.y = (yPos + deltaTime * speed * speedY * slowdownSpeedModifier);


    return newPos;
}

void EnemyGO::snapToGrid() {
    auto gridPos = getTilePosition();
    setXPos(gridPos.x * TILE_SIZE + 0.5 * TILE_SIZE);
    setYPos(gridPos.y * TILE_SIZE + 0.5 * TILE_SIZE + VERTICAL_RENDER_DIFFERENCE);
}


sf::Vector2<int> EnemyGO::getGridVector(sf::Vector2<int> gridPos) {
    double x = gridPos.x * TILE_SIZE + 0.5 * TILE_SIZE;
    double y = gridPos.y * TILE_SIZE + 0.5 * TILE_SIZE + VERTICAL_RENDER_DIFFERENCE;

    int vecX = 0;
    int vecY = 0;

    if (x > xPos) vecX = 1;
    if (x < xPos) vecX = -1;
    if (y > yPos) vecY = 1;
    if (y < yPos) vecY = -1;

    return {vecX, vecY};
}

void EnemyGO::calcTargetPosition() {
    auto currentGridPos = getTilePosition();
    auto nextPos = getNewPos(currentGridPos.x, currentGridPos.y, movingDir);

    targetPositionGrid = nextPos;
}


void EnemyGO::pollMovement(Stage &stage, PlayerGO &pl) {
    playerPosChanged = playerPosChanged | pl.isTilePosChanged();
    playerPos = pl.getTilePosition();
}


void EnemyGO::generatePath() {
    if (!alive) return;

    LevelTiles& levelTiles = *level.lock();
    LevelTilesPathfinding pathfinder(levelTiles, enemyType == EnemyType::ghost, enemyType != EnemyType::normal);
    auto tilePos = getTilePosition();
    pathfinder.setStart(tilePos);
    pathfinder.setEnd({playerPos.x, playerPos.y});

    if (pathfinder.generatePath()) { //path found
        movingDir = pathfinder.getNextDirection();
        calcTargetPosition();
        pathFound = true;
        return;
    }

    //path not found - it should not happen, workarounds:

    if (levelTiles.getTileOn(tilePos.x, tilePos.y) == TileType::verticalWall) {
        movingDir = south;
        calcTargetPosition();
        pathFound = true;
    } else {
        alive = false;
        pathFound = false;
    }

}

void EnemyGO::bulletHitSlowdown() {
    switch (enemyType) {
        case EnemyType::normal:
            hitByBulletSpeedModifier = 0.22;
            break;
        case EnemyType::tank:
            hitByBulletSpeedModifier = 0.3;
            break;
        case EnemyType::ghost:
            hitByBulletSpeedModifier = 0.5;
            break;
    }
}

void EnemyGO::setPlayer(const std::weak_ptr<PlayerGO>& player) {
    EnemyGO::player = player;
}
