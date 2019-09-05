#include <cmath>
#include "PlayerGO.h"
#include "../ConstSettings.h"
#include "SFML/Graphics/Sprite.hpp"

void PlayerGO::pollMovement(Stage& stage) {
    if (!tumbling) {
        tumblingMultiplier = 1;
    } else {
        auto elapsedSeconds = tumbleClock.getElapsedTime().asSeconds();
        if (elapsedSeconds >= TUMBLE_TIME) {
            tumbling = false;
            shielding = false;
        } else if (elapsedSeconds >= (TUMBLE_TIME * 0.4)) {
            double speedReduction = TUMBLE_SLOWDOWN / stage.getStageManager().getAmortizedAverageDeltaTimeError();
            tumblingMultiplier /= speedReduction;
        }
    }

    double spdX = 0;
    double spdY = 0;
    bool moving = false;
    double verticalMoving = 0;
    double horizontalMoving = 0;

    if (tumbling) {
        moving = true;
    }

    if (getInputHandler(stage).isPressed(sf::Keyboard::Key::A)) {
        lookingDirection = west;
        horizontalMoving = -1;
        moving = true;
    }
    if (getInputHandler(stage).isPressed(sf::Keyboard::Key::D)) {
        lookingDirection = east;
        horizontalMoving = 1;
        moving = true;
    }
    if (getInputHandler(stage).isPressed(sf::Keyboard::Key::W)) {
        lookingDirection = north;
        verticalMoving = -1;
        moving = true;
    }
    if (getInputHandler(stage).isPressed(sf::Keyboard::Key::S)) {
        lookingDirection = south;
        verticalMoving = 1;
        moving = true;
    }

    if (getInputHandler(stage).isPressed(sf::Keyboard::Key::LShift)) {
        if (tumbleCooldownClock.getElapsedTime().asSeconds() >= TUMBLE_COOLDOWN) {
            tumbleCooldownClock.restart();
            tumbling = true;
            tumbleClock.restart();
            moving = true;
            shielding = true;
            tumblingMultiplier = TUMBLE_INITIAL_SPEED_MULTIPLIER;
        }
    }
    if (moving) {
        spdX = horizontalMoving * DEFAULT_SPEED;
        spdY = verticalMoving * DEFAULT_SPEED;
        if (verticalMoving != 0 && horizontalMoving != 0) {
            const double sqrt2 = sqrt(2);
            spdX /= sqrt2;
            spdY /= sqrt2;
        }
    }

    if (getInputHandler(stage).isPressed(sf::Keyboard::Key::Space)) {
        if (bulletCooldownClock.getElapsedTime().asSeconds() >= BULLET_COOLDOWN) {
            bulletCooldownClock.restart();
            projectiles->add(ProjectileGO(resourceLoader, lookingDirection, {(int) xPos, (int) yPos}, level, bulletDamage));
        }
    }
    speedX = spdX * tumblingMultiplier;
    speedY = spdY * tumblingMultiplier;

}

void PlayerGO::update(Stage& stage) {
    pollMovement(stage);
    checkAndMove(stage.delta());
}

void PlayerGO::draw(sf::RenderWindow& window) {
    if (!isAlive()) {
        auto text = resourceLoader->load("../resources/dead.png");
        sf::Sprite s;
        s.setTexture(*text);
        s.setPosition(getTopLeftSprite());
        window.draw(s);
        return;
    }


    //drawing player
    sf::Sprite s;

    iteration++;
    sprites.setDirection(lookingDirection);
    s.setTexture(*sprites.getTexture().get());
    s.setScale(1.0f * PLAYER_AND_ENEMY_SIZE/s.getTexture()->getSize().x, 1.0f * PLAYER_AND_ENEMY_SIZE/s.getTexture()->getSize().y);
    auto pos = getTopLeftSprite();
    pos.y += 2.2 * sin(iteration * 0.04);
    s.setPosition(pos);

    if (playerDamageClock.getElapsedTime().asSeconds() < INVULNERABILITY_AFTER_DAMAGE) {
        s.setColor(
                sf::Color(
                        255,
                        255,
                        255,
                        (sf::Uint8) (255 * sin(6 * playerDamageClock.getElapsedTime().asSeconds())))
                        );
    }


    window.draw(s);

    //drawing shield
    if (shielding) {
        s.setColor(sf::Color(255, 255, 255, 128));
        s.setTexture(*resourceLoader->load("../resources/defense.png"));
        window.draw(s);
    }
}

sf::Vector2<float> PlayerGO::simpleMove(double deltaTime) {
    auto a = getTilePosition();
    auto b = level->getTileOn(a.x, a.y);
    double coeff = 1;
    if (b == TileType::slowingFloor) coeff = 0.7;
    sf::Vector2<float> newPos;
    newPos.x = (xPos + deltaTime * speedX * coeff);
    newPos.y = (yPos + deltaTime * speedY * coeff);
    return newPos;
}

void PlayerGO::setLevel(const std::shared_ptr<LevelTiles>& level) {
    PlayerGO::level = level;
}

void PlayerGO::checkAndMove(double deltaTime) {
    auto oldPos = getTilePosition();

    auto a = simpleMove(deltaTime);
    if (checkNewPosition(a.x, yPos, level)) {
        setXPos(a.x);
    }
    if (checkNewPosition(xPos, a.y, level)) {
        setYPos(a.y);
    }
    auto newPos = getTilePosition();
    tilePosChanged = (oldPos != newPos);
}

void PlayerGO::setProjectiles(const std::shared_ptr<ProjectilesGO>& projectiles) {
    PlayerGO::projectiles = projectiles;
}

void PlayerGO::setEnemies(const std::weak_ptr<EnemiesGO>& enemies) {
    PlayerGO::enemies = enemies;
}

PlayerGO::PlayerGO(ResourceLoader* resLoad, Stage* stage) : DamageableGO(resLoad, 3) {
    setStage(stage);
    sprites.add(resLoad->load("../resources/player2.png"), north);
    sprites.add(resLoad->load("../resources/player1.png"), east);
    sprites.add(resLoad->load("../resources/player3.png"), west);
    sprites.add(resLoad->load("../resources/player0.png"), south);
    sprites.setDirection(lookingDirection);
    width = PLAYER_AND_ENEMY_SIZE;
    height = PLAYER_AND_ENEMY_SIZE;
}

void PlayerGO::dealDamageTimed() {
    if (shielding) return;
    if (playerDamageClock.getElapsedTime().asSeconds() > INVULNERABILITY_AFTER_DAMAGE) {
        this->dealDamage(1);
        playerDamageClock.restart();
    }

}
