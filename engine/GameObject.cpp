#include "GameObject.h"
#include "../ConstSettings.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

GameObject::GameObject(ResourceLoader *resourceLoader) : resourceLoader(resourceLoader){

}

sf::Vector2f GameObject::getTopLeftSprite() {
    return {xPos - scaling*width/2, yPos - scaling*height/2};
}

sf::Vector2f GameObject::getBottomRightSprite() {
    return {xPos + scaling*width/2, yPos + scaling*height/2};
}

bool GameObject::intersects(GameObject& gameObject1) {
    auto lt0 = getTopLeftHitbox();
    auto br0 = getBottomRightHitbox();

    auto lt1 = gameObject1.getTopLeftHitbox();
    auto br1 = gameObject1.getBottomRightHitbox();

    if (lt0.x > br1.x || lt1.x > br0.x) {
        return false;
    }

    if (lt0.y > br1.y || lt1.y > br0.y) {
        return false;
    }

    return true;
}

void GameObject::renderCall(sf::RenderWindow& window) {
    draw(window);
}

void GameObject::setStage(Stage *stage) {
    GameObject::stage = stage;
}

Inputs& GameObject::getInputHandler(Stage& stage) {
    return stage.getStageManager().getInputs();
}

void GameObject::setXPos(float xPos) {
    GameObject::xPos = xPos;
}

void GameObject::setYPos(float yPos) {
    GameObject::yPos = yPos;
}

float GameObject::getXPos() const {
    return xPos;
}

float GameObject::getYPos() const {
    return yPos;
};


double GameObject::getScaling() const {
    return scaling;
}

void GameObject::setScaling(double scaling) {
    GameObject::scaling = scaling;
}


sf::Vector2<int> GameObject::getTilePosition() {
    return getNewTilePosition({xPos, yPos});
}

sf::Vector2<int> GameObject::getNewTilePosition(sf::Vector2<double> coord) {
    int tileX = (int) coord.x - 0;
    int tileY = (int) coord.y - VERTICAL_RENDER_DIFFERENCE;

    tileX /= TILE_SIZE;
    tileY /= TILE_SIZE;

    sf::Vector2<int> tilePos(tileX, tileY);

    tilePosChanged = oldTilePos != tilePos;
    oldTilePos = tilePos;
    return oldTilePos;
}


sf::Vector2f GameObject::getTopLeftHitbox() {
    return {xPos - scaling*width/2, yPos - scaling*height/2};
}

sf::Vector2f GameObject::getBottomRightHitbox() {
    return {xPos + scaling*width/2, yPos + scaling*height/2};
}

void GameObject::setPos(const sf::Vector2f& pos) {
    xPos = pos.x;
    yPos = pos.y;
}