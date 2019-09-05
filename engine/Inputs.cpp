#include "Inputs.h"
#include <windef.h>
#include "Window.h"


void Inputs::clearTyped() {
    for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
        typed[i] = false;
    }
}

void Inputs::clear() {
    for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
        pressed[i] = false;
    }
    for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
        typed[i] = false;
    }
}


bool Inputs::isTyped(sf::Keyboard::Key key) {
    return typed[key];
}

bool Inputs::isPressed(sf::Keyboard::Key key) {
    return pressed[key];
}

void Inputs::setPressed(sf::Keyboard::Key key) {
    pressed[key] = true;
}

void Inputs::setReleased(sf::Keyboard::Key key) {
    pressed[key] = false;
    typed[key] = true;
}

