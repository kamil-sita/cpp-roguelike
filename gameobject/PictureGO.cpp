#include <iostream>
#include "PictureGO.h"
#include "../engine/ResourceLoader.h"


void PictureGO::draw(sf::RenderWindow& window){
    if (alpha == 0)
        return;
    sprite.setColor(sf::Color(255, 255, 255, alpha));
    sprite.setPosition(xPos - (width*scaling)/2, yPos - (height*scaling)/2);
    sprite.setScale({(float) scaling, (float) scaling});
    window.draw(sprite);
}

PictureGO::~PictureGO() {

}

void PictureGO::update(Stage &stage) {
}

void PictureGO::setTexture(std::shared_ptr<sf::Texture> text) {
    sprite.setTexture(*text.get());
    this->width = sprite.getTexture()->getSize().x;
    this->height = sprite.getTexture()->getSize().y;
}

void PictureGO::setTexture(const char *name)  {
    setTexture(resourceLoader->load(name));
    resourceLoader->load(name)->setSmooth(true);
}

PictureGO::PictureGO(ResourceLoader *resourceLoader1) : GameObject(resourceLoader1) {

}

PictureGO::PictureGO(ResourceLoader *resourceLoader1, const char *name) : GameObject(resourceLoader1) {
    setTexture(name);
}

void PictureGO::setAlpha(int alpha) {
    PictureGO::alpha = alpha;
}
