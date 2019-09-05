#ifndef ROGUELIKE_RESOURCELOADER_H
#define ROGUELIKE_RESOURCELOADER_H

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics/Font.hpp>

/**
 * Helper class that loads each resource once.
 */
class ResourceLoader {
    std::shared_ptr<sf::Font> font;

    std::unordered_map<const char*, std::shared_ptr<sf::Texture>> flyweightLoader;
    bool isLoaded(const char* name);
    std::shared_ptr<sf::Texture> get(const char* name);

public:
    ResourceLoader();

    std::shared_ptr<sf::Texture> load(const char* name);
    std::shared_ptr<sf::Font> getFont();
    ~ResourceLoader() = default;
};

#endif