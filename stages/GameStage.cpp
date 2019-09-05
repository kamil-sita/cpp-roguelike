#include "GameStage.h"


GameStage::GameStage(ResourceLoader& resourceLoader, StageManager& stageManager) :
        Stage(resourceLoader, stageManager) {

    health0 = std::make_shared<PictureGO>(&resourceLoader, "../resources/plusSign.png");
    health1 = std::make_shared<PictureGO>(&resourceLoader, "../resources/plusSign.png");
    health2 = std::make_shared<PictureGO>(&resourceLoader, "../resources/plusSign.png");
    health0->setScaling(0.05);
    health1->setScaling(0.05);
    health2->setScaling(0.05);
    health0->setPos({780, 30});
    health1->setPos({820, 30});
    health2->setPos({860, 30});

    projectiles = std::make_shared<ProjectilesGO>(&resourceLoader);

    player = std::make_shared<PlayerGO>(&resourceLoader, this);
    level = std::make_shared<LevelGO>(&resourceLoader, player);
    player->setXPos(WIDTH/2.0);
    player->setYPos(HEIGHT/2.0);
    enemies = std::make_shared<EnemiesGO>(&resourceLoader);
    level->setEnemies(enemies);
    level->generateNew();
    player->setLevel(level->getLevel());
    player->setEnemies(enemies);
    player->setProjectiles(projectiles);

    auto hudBeam = std::make_shared<PictureGO>(&resourceLoader, "../resources/banner.png");
    hudBeam->setXPos(WIDTH/2.0f);
    hudBeam->setYPos(VERTICAL_RENDER_DIFFERENCE);
    add(level);
    add(enemies);
    add(projectiles);

    fogGo = std::make_shared<FogGO>(getResourceLoader(), 96);
    add(fogGo);


    add(hudBeam);
    add(health0);
    add(health1);
    add(health2);

    auto vignette = std::make_shared<PictureGO>(&resourceLoader, "../resources/vignette.png");
    vignette->setPos({WIDTH/2.0f, HEIGHT/2.0f});
    add(vignette);

    fadeout = std::make_shared<PictureGO>(&resourceLoader, "../resources/black.png");
    fadeout->setXPos(WIDTH/2.0);
    fadeout->setYPos(HEIGHT/2.0);
    fadeout->setAlpha(0);


    add(player);

    add(fadeout);
}

void GameStage::updateScene() {

    if (!player->isAlive()) {
        updateFadeout();
        return;
    }

    enemies->updatePathfinder(*this, player, level->getLevel());

    updateAllObjects();

    pollIsGoToMenu();

    changeLevelIfAllEnemiesDead();

    updateHealthVisibility();
}

void GameStage::updateFadeout() {
    if (!losingClock) {
        losingClock = true;
        clock.restart();
    } else {
        double fadeoutAlpha = 255 * (clock.getElapsedTime().asSeconds() / GAME_FADEOUT_TIME);
        fadeout->setAlpha(fadeoutAlpha);
        if (clock.getElapsedTime().asSeconds() > GAME_FADEOUT_TIME) {
            getStageManager().getMenuStage()->restartGameStage();
            getStageManager().setStageMenuStage();
        }
    }
}

void GameStage::pollIsGoToMenu() const {
    if (getStageManager().getInputs().isTyped(sf::Keyboard::Escape)) {
        getStageManager().setStageMenuStage();
    }
}

void GameStage::changeLevelIfAllEnemiesDead() {
    if (enemies->aliveEnemiesCount() == 0) {
        if (!cooldownDuringRounds) {
            clock.restart();
            cooldownDuringRounds = true;
        } else {
            if (clock.getElapsedTime().asSeconds() > COOLDOWN_BETWEEN_ROUNDS) {
                cooldownDuringRounds = false;
                level->generateNew();
                player->setLevel(level->getLevel());
                if (player->getMaxHealthPoints() == player->getHealthPoints()) {
                    player->increaseDamage(2);
                } else {
                    player->restoreHealth();
                    player->increaseDamage(1);
                }
                projectiles->clear();
            }

        }
    }
}

void GameStage::updateHealthVisibility() const {
    double hp = player->getHealthPoints();
    health2->setAlpha(hp >= 3 ? 255 : 0);
    health1->setAlpha(hp >= 2 ? 255 : 0);
    health0->setAlpha(hp >= 1 ? 255 : 0);
}

const std::shared_ptr<EnemiesGO>& GameStage::getEnemies() const {
    return enemies;
}