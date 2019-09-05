#include <iostream>
#include "ResourceLoader.h"

using namespace std::string_literals;

std::shared_ptr<sf::Texture> ResourceLoader::load(const char* name) {
    if (isLoaded(name)) return get(name);
    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(name)) {
        throw std::invalid_argument("Failed to load: "s + name);
    }
    texture->setSmooth(true);
    flyweightLoader[name] = texture;
    return texture;
}

bool ResourceLoader::isLoaded(const char* name) {
    return flyweightLoader.find(name) != flyweightLoader.end();
}

std::shared_ptr<sf::Texture> ResourceLoader::get(const char* name) {
    return flyweightLoader[name];
}

std::shared_ptr<sf::Font> ResourceLoader::getFont() {
    if (font != nullptr) {
        return font;
    }
    font = std::make_shared<sf::Font>();
    if (!font.get()->loadFromFile("../resources/arial.ttf")) {
        throw std::invalid_argument("Failed to load font arial.ttf. Make sure it is placed in resources folder");
    }
    return font;
}

ResourceLoader::ResourceLoader(){

}
