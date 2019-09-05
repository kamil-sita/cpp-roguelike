
#ifndef ROGUELIKE_PICTUREGO_H
#define ROGUELIKE_PICTUREGO_H


#include "../engine/GameObject.h"
#include "../engine/ResourceLoader.h"
#include <SFML/Graphics/Sprite.hpp>

//GameObject that graphically is a single image
class PictureGO : public GameObject {
private:
    sf::Sprite sprite;
    int alpha = 255;
protected:
    void draw(sf::RenderWindow& window) override;
public:
    PictureGO(ResourceLoader* resourceLoader1, const char* name);
    PictureGO(ResourceLoader* resourceLoader1);

    void update(Stage& stage) override;

    void setTexture(std::shared_ptr<sf::Texture> text);
    void setTexture(const char* name);

    void setAlpha(int alpha);

    ~PictureGO() override;
};


#endif
