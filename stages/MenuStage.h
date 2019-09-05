#ifndef ROGUELIKE_MENUSTAGE_H
#define ROGUELIKE_MENUSTAGE_H

#include "../engine/Stage.h"
#include "../gameobject/PictureGO.h"
#include "GameStage.h"
#include "../gameobject/FogGO.h"

class GameStage;
class MenuStage : public Stage {

    bool fadeIn = false;
    bool playAfterFadeIn = false;
    sf::Clock clock;

    int selectedId = 0;
    std::shared_ptr<PictureGO> button0;
    std::shared_ptr<PictureGO> button1;
    std::shared_ptr<GameStage> game = nullptr;

    std::shared_ptr<PictureGO> fadeEffect;

    std::shared_ptr<FogGO> fogGo;
protected:
    void updateScene() override;
public:
    MenuStage(ResourceLoader& resourceLoader, StageManager& stageManager);
    void restartGameStage();

    void moveCursor();

    void reloadButtonTextures();
};


#endif
