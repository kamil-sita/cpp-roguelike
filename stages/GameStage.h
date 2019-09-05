#ifndef ROGUELIKE_GAMESTAGE_H
#define ROGUELIKE_GAMESTAGE_H


#include "../engine/Stage.h"
#include "../gameobject/PictureGO.h"
#include "../gameobject/LevelGO.h"
#include "../ConstSettings.h"
#include "../gameobject/enemy/EnemiesGO.h"
#include "MenuStage.h"
#include "../gameobject/FogGO.h"

class GameStage : public Stage {

    std::shared_ptr<PictureGO> health0;
    std::shared_ptr<PictureGO> health1;
    std::shared_ptr<PictureGO> health2;

    std::shared_ptr<PictureGO> fadeout;

    std::shared_ptr<LevelGO> level;
    std::shared_ptr<EnemiesGO> enemies;
    std::shared_ptr<PlayerGO> player;
    std::shared_ptr<ProjectilesGO> projectiles;

    std::shared_ptr<FogGO> fogGo;

    bool cooldownDuringRounds = false;
    bool losingClock = false;
    sf::Clock clock;
protected:

    void updateScene() override;
public:
    GameStage(ResourceLoader& resourceLoader, StageManager& stageManager);

    const std::shared_ptr<EnemiesGO> &getEnemies() const;

    void updateHealthVisibility() const;

    void changeLevelIfAllEnemiesDead();

    void pollIsGoToMenu() const;

    void updateFadeout();
};


#endif
