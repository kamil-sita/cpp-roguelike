#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "Window.h"
#include "GameObject.h"
#include "../stages/MenuStage.h"
#include "Inputs.h"


Window::Window():
        inputs(this),
        window(sf::VideoMode(WIDTH, HEIGHT), name, sf::Style::Fullscreen, sf::ContextSettings(0, 0, 2)),
        stageManager(resourceLoader, inputs) {

    window.setFramerateLimit(TARGET_FRAMERATE);
    window.requestFocus();

    std::shared_ptr<MenuStage> menuStage = std::make_shared<MenuStage>(resourceLoader, stageManager);
    stageManager.setMenuStage(menuStage);
    stageManager.setStage(menuStage);
    window.setIcon(128, 128, resourceLoader.load("../resources/logo.png")->copyToImage().getPixelsPtr());

    window.setMouseCursorVisible(false);
}

ApplicationStatus Window::run() {
    sf::Clock fpsClock;
    sf::Clock deltaTimeClock;

    deltaTimeClock.restart();
    while (window.isOpen()) {
        //game loop
        double deltaTime = deltaTimeClock.restart().asSeconds() * TARGET_FRAMERATE;
        stageManager.update(deltaTime);

        //check if game is scheduled for closure/restart
        auto status = pollKeyboardAndWindowStatus(stageManager);
        if (status != ApplicationStatus::none) {
            window.close();
            return status;
        }

        //draw game
        window.clear(sf::Color::Black);
        stageManager.draw(window);
        window.display();


        calculateFpsAndAverageDeltaTime(fpsClock, stageManager);
    }

    return ApplicationStatus::endApplication;
}

void Window::calculateFpsAndAverageDeltaTime(sf::Clock& fpsClock, StageManager& stageManager) {

    renderedFrameCount++;
    const float PROBING_TIME = 1.0f;
    if (fpsClock.getElapsedTime().asSeconds() >= PROBING_TIME) {
        double time = fpsClock.getElapsedTime().asSeconds();
        double realFrames = renderedFrameCount/time;

        setFramerateAsWindowTitle(realFrames);

        renderedFrameCount = 0;
        fpsClock.restart();

        double averageDeltaTime = time/renderedFrameCount;
        double averageDeltaTimeError = averageDeltaTime * TARGET_FRAMERATE;
        stageManager.setAverageDeltaTimeError(averageDeltaTimeError);
    }
}

void Window::setFramerateAsWindowTitle(double realFrames) {
    std::ostringstream oss;
    oss << std::setprecision(4);
    oss << name << " [" << realFrames << " fps]";
    window.setTitle(oss.str());
}


ApplicationStatus Window::pollKeyboardAndWindowStatus(StageManager& stageManager) {
    inputs.clearTyped();
    sf::Event event {};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            return ApplicationStatus::endApplication;
        }
        if (event.type == sf::Event::KeyPressed) {
            inputs.setPressed(event.key.code);
        }
        if (event.type == sf::Event::KeyReleased) {
            inputs.setReleased(event.key.code);
        }
    }
    return stageManager.getApplicationStatus();
}
