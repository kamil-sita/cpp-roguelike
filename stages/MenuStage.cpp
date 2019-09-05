#include "MenuStage.h"

void MenuStage::updateScene() {
    updateAllObjects();

    bool afterFade = false;

    if (fadeIn) {
        double fadeoutAlpha = 255 * (clock.getElapsedTime().asSeconds()/MENU_FADEOUT_TIME);
        fadeEffect->setAlpha(fadeoutAlpha);
        if (clock.getElapsedTime().asSeconds() > MENU_FADEOUT_TIME) {
            afterFade = true;
            fadeIn = false;
        } else {
            return;
        }
    }

    moveCursor();

    auto input = getStageManager().getInputs();
    if ( (selectedId == 0 && (input.isTyped(sf::Keyboard::Key::Space) || input.isTyped(sf::Keyboard::Key::Enter))) || (afterFade && playAfterFadeIn)) {
        if (game == nullptr) {
            game = std::make_shared<GameStage>(*getResourceLoader(), getStageManager());
            fadeIn = true;
            clock.restart();
            playAfterFadeIn = true;
            return;
        }
        getStageManager().setStage(game);
        fadeEffect->setAlpha(0);
    }
    if (selectedId == 1 && (input.isTyped(sf::Keyboard::Key::Space) || input.isTyped(sf::Keyboard::Key::Enter))) {
        fadeIn = true;
        clock.restart();
        playAfterFadeIn = false;
    }
    if (afterFade && !playAfterFadeIn) {
        getStageManager().setExit(true);
    }
    reloadButtonTextures();
}

void MenuStage::reloadButtonTextures() {//reloading textures depending on selected option
    button0->setTexture(getResourceLoader()->load("../resources/newGame.png"));
    button1->setTexture(getResourceLoader()->load("../resources/exit.png"));

    switch (selectedId) {
        case 0:
            button0->setTexture(getResourceLoader()->load("../resources/newGameSelected.png"));
            break;
        case 1:
            button1->setTexture(getResourceLoader()->load("../resources/exitSelected.png"));
            break;
        default:
            break;
    }
}

void MenuStage::moveCursor() {
    auto &input = getStageManager().getInputs();
    if (input.isTyped(sf::Keyboard::W) || input.isTyped(sf::Keyboard::A)) {
        selectedId -= 1;
    } else if (input.isTyped(sf::Keyboard::S) || input.isTyped(sf::Keyboard::D)) {
        selectedId += 1;
    }
    //normalization
    if (selectedId < 0) {
        selectedId = 1;
    } else if (selectedId > 1) {
        selectedId = 0;
    }
}

MenuStage::MenuStage(ResourceLoader& resourceLoader, StageManager& stageManager) : Stage(resourceLoader, stageManager) {
    button0 = std::make_shared<PictureGO>(getResourceLoader());
    button1 = std::make_shared<PictureGO>(getResourceLoader());
    button0->setXPos(200);
    button1->setXPos(600);
    button0->setYPos(720);
    button1->setYPos(780);
    auto background = std::make_shared<PictureGO>(getResourceLoader(), "../resources/menu.png");
    background->setXPos(WIDTH/2.0);
    background->setYPos(HEIGHT/2.0);
    add(background);
    add(button0);
    add(button1);

    fogGo = std::make_shared<FogGO>(getResourceLoader(), 255);
    add(fogGo);

    auto vignette = std::make_shared<PictureGO>(&resourceLoader, "../resources/vignette.png");
    vignette->setPos({WIDTH/2.0f, HEIGHT/2.0f});
    add(vignette);

    fadeEffect = std::make_shared<PictureGO>(&resourceLoader, "../resources/black.png");
    fadeEffect->setXPos(WIDTH/2.0);
    fadeEffect->setYPos(HEIGHT/2.0);
    fadeEffect->setAlpha(0);
    add(fadeEffect);
}

void MenuStage::restartGameStage() {
    game = nullptr;
}
