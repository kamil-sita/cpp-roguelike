#ifndef ROGUELIKE_INPUTS_H
#define ROGUELIKE_INPUTS_H

#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>

class Window;

///this class is responsible for containing key strokes from keyboard
class Inputs {
private:
    Window* window;

    volatile bool pressed[sf::Keyboard::KeyCount];
    volatile bool typed[sf::Keyboard::KeyCount];

    void clear();

public:
    Inputs(Window* window) : window(window) {
        clear();
    }

    void clearTyped();
    void laterUpdate();

    bool isTyped(sf::Keyboard::Key key);
    bool isPressed(sf::Keyboard::Key key);

    void setPressed(sf::Keyboard::Key key);
    void setReleased(sf::Keyboard::Key key);
};


#endif
