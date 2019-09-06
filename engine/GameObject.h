#ifndef SIMULATOR_GAMEOBJECT_H
#define SIMULATOR_GAMEOBJECT_H

#include <SFML/System/Vector2.hpp>
#include "ResourceLoader.h"
#include "Stage.h"

class Stage;
class Inputs;
///basic actor
class GameObject {
protected:

    ///x position of centre of this object
    float xPos;
    ///y position of centre of this object
    float yPos;
    float width;
    float height;
    float scaling = 1;
    ResourceLoader* resourceLoader;
    Stage* stage;

    sf::Vector2<int> oldTilePos;

    bool tilePosChanged = true;

    ///main drawing function
    virtual void draw(sf::RenderWindow& window) = 0;

    Inputs& getInputHandler(Stage& stage);

    sf::Vector2f getTopLeftSprite();
    sf::Vector2f getBottomRightSprite();

    virtual sf::Vector2f getTopLeftHitbox();
    virtual sf::Vector2f getBottomRightHitbox();

    ///helper method - returns tilePosition if object was in coordinates coord
    sf::Vector2<int> getNewTilePosition(sf::Vector2<double> coord);

public:
    GameObject(ResourceLoader *resourceLoader);

    bool intersects(GameObject& gameObject1);

    /**
     * Public drawing function. Normally it should not be overriden, but you can
     * if you don't want it to be drawn directly by stage.
     */
    virtual void renderCall(sf::RenderWindow& window);

    /**
     * Updates object's logic
     */
    virtual void update(Stage& stage) = 0;


    sf::Vector2<int> getTilePosition();

    ///obiekt powinien znać swój stage w celu otrzymania reszty funkcji pozwalających na interakcję z innymi obiektami
    void setStage(Stage *stage);

    void setXPos(float xPos);

    void setYPos(float yPos);

    void setPos(const sf::Vector2f& pos);

    float getXPos() const;

    float getYPos() const;

    double getScaling() const;

    void setScaling(double scaling);

    virtual ~GameObject() = default;
};

#endif