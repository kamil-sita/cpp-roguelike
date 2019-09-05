#include "LevelGO.h"
#include "../ConstSettings.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <math.h>
#include "enemy/EnemiesGO.h"
#include "enemy/EnemyFactory.h"

const int width = 1600;
const int height = 800;

LevelGO::LevelGO(ResourceLoader* resLoad, std::shared_ptr<PlayerGO> player) : GameObject(resLoad), player(player) {
    wallTexture = resLoad->load("../resources/blockingTile.png");
    verticalWallTexture = resLoad->load("../resources/blockingTileHorizontal.png");

    waterAlpha  = resLoad->load("../resources/tileSlowingAlpha.png");
    topWater = resLoad->load("../resources/waterTileNeighbour.png");

    loadAdditionalEffects(*resLoad);
}


template<typename TextureFromCoord> void LevelGO::drawLayer(sf::RenderWindow& window, TileType tileFilter, TextureFromCoord textureFromCoord, double ratio) {
    int x = 0;
    int y = VERTICAL_RENDER_DIFFERENCE;


    sf::Sprite sprite;
    for (int j = 0; j < LVL_HEIGHT; j++) {
        for (int i = 0; i < LVL_WIDTH; i++) {
            if (ratio == 1.0 || semiRandomForTile2(i, j) < ratio) {
                sprite.setTexture(textureFromCoord(i, j));
                sprite.setScale(1.0f * TILE_SIZE/sprite.getTexture()->getSize().x, 1.0f * TILE_SIZE/sprite.getTexture()->getSize().y);
                sprite.setPosition(x, y);
                if (level->getTileOn(i, j) == tileFilter) {
                    window.draw(sprite);
                }
            }
            x += TILE_SIZE;
        }
        x = 0;
        y += TILE_SIZE;
    }
}


void LevelGO::drawShadow(sf::RenderWindow& window, TileType shadowType, sf::Color color, std::shared_ptr<sf::Texture>& sLayer,
                                 std::shared_ptr<sf::Shader> shader, int diffX, bool invert) {
    if (sLayer == nullptr) {
        sLayer = generateShadow(shadowType, color, sLayer, shader, diffX, invert);
    }
    sf::Sprite d(*sLayer);
    window.draw(d);
}

std::shared_ptr<sf::Texture> LevelGO::generateShadow(const TileType& shadowType, const sf::Color& color, std::shared_ptr<sf::Texture>& sLayer,
                        const std::shared_ptr<sf::Shader>& shader, int diffX, bool invert) {
    auto layer = std::make_shared<sf::RenderTexture>();
    layer->create(WIDTH, HEIGHT);
    layer->clear(sf::Color(0, 0, 0, 0));

    sf::RectangleShape shadowRectangle;
    shadowRectangle.setSize(sf::Vector2f(40, 40));
    shadowRectangle.setFillColor(color);

    auto shadow = std::make_shared<sf::RenderTexture>();
    shadow->create(TILE_SIZE * LVL_WIDTH, TILE_SIZE * LVL_HEIGHT);
    shadow->clear(sf::Color(0, 0, 0, 0));

    int x = 0;
    int y = 0;
    for (int j = LVL_HEIGHT - 1; j >= 0; --j) { //sfml bug - Y axis is reversed
        for (int i = 0; i < LVL_WIDTH; i++) {
            shadowRectangle.setPosition(x + diffX, y);
            if (invert) {
                if (level->getTileOn(i, j) != shadowType) {
                    shadow->draw(shadowRectangle);
                }
            } else {
                if (level->getTileOn(i, j) == shadowType) {
                    shadow->draw(shadowRectangle);
                }
            }
            x += TILE_SIZE;
        }
        x = 0;
        y += TILE_SIZE;
    }


    sf::Sprite sprite(shadow->getTexture());
    sprite.setPosition(0, VERTICAL_RENDER_DIFFERENCE);
    if (shader == nullptr) {
        layer->draw(sprite);
    } else {
        layer->draw(sprite, shader.get());
    }
    layer->display();
    sLayer = std::make_shared<sf::Texture>(layer->getTexture());
    return sLayer;
}

std::shared_ptr<sf::Shader> LevelGO::getBlurShader() {
    if (shaderInitialized) {
        return blurShader;
    } else {
        blurShader = std::make_shared<sf::Shader>();
        if (!blurShader->loadFromFile("../resources/blur.shader", sf::Shader::Fragment)) {
            throw std::exception();
        }
        blurShader->setUniform("texture", sf::Shader::CurrentTexture);
        blurShader->setUniform("blur_radius", 0.001f);
        shaderInitialized = true;
        return blurShader;
    }
}

void LevelGO::draw(sf::RenderWindow& window) {
    drawWaveLayer(window, TileType::slowingFloor, floorTextures.get(0), 12, 0, 0, 255);
    drawWaveLayer(window, TileType::slowingFloor, waterAlpha,12, 0.03, 0.298, 192);
    drawWaveLayer(window, TileType::slowingFloor, waterAlpha,14, -0.302, -0.02, 128);
    drawOnEdgeOf(window, TileType::floor, TileType::slowingFloor, topWater);
    drawOnEdgeOf(window, TileType::verticalWall, TileType::slowingFloor, topWater);

    drawShadow(window, TileType::slowingFloor, sf::Color(0, 0, 0, 192), shadowLayer0, getBlurShader(), 0, true);
    drawLayer(window, TileType::floor,
              [this](int x, int y) -> sf::Texture& {
                  return *floorTextures.get((int) (1000 * semiRandomForTile(x, y)));
              }
    );
    drawLayer(window, TileType::floor,
              [this](int x, int y) -> sf::Texture& {
                  return *groundEffects.at(doubleToInt(0, groundEffects.size(), semiRandomForTile(x, y)));
              },
              0.06
    );


    drawShadow(window, TileType::verticalWall, sf::Color::Black, shadowLayer1, getBlurShader());
    //jakby poniżej było zwykłe TILE_SIZE/2 to cień idealnie nakłada się na kafelki, co psuje efekt oraz wygląda jakby ktoś źle ułożył kafelki
    drawShadow(window, TileType::verticalWall, sf::Color(0, 0, 0, 64), shadowLayer2, getBlurShader(), TILE_SIZE / 2 + 5);

    drawLayer(window, TileType::verticalWall,
              [this](int x, int y) -> sf::Texture& {
                  return *verticalWallTexture;
              }
    );
    drawLayer(window, TileType::verticalWall,
              [this](int x, int y) -> sf::Texture& {
                  return *verticalWallEffects.at(doubleToInt(0, verticalWallEffects.size(), semiRandomForTile(x, y)));
              },
              0.14
    );

    enemies.get()->trueRenderCall(window);
    player->renderCall(window);

    drawShadow(window, TileType::wall, sf::Color::Black, shadowLayer3, getBlurShader());
    drawShadow(window, TileType::wall, sf::Color(0, 0, 0, 128), shadowLayer4, getBlurShader(), TILE_SIZE / 2 + 5);
    drawLayer(window, TileType::wall,
              [this](int x, int y) -> sf::Texture& {
                  return *wallTexture;
              }
    );
}

const std::shared_ptr<LevelTiles> &LevelGO::getLevel() const {
    return level;
}


void LevelGO::drawWaveLayer(sf::RenderWindow& window, TileType tileFilter,
                                    std::shared_ptr<sf::Texture> texture,
                                    double colorWaveEffect, double xVec, double yVec, int alpha) {

    int x = 0;
    int y = VERTICAL_RENDER_DIFFERENCE;

    double xOffset = (xVec > 0 ? 1 : -1) *  fmod(iteration * abs(xVec), TILE_SIZE);
    double yOffset = (yVec > 0 ? 1 : -1) *  fmod(iteration * abs(yVec), TILE_SIZE);
    double waveEffectOffs = sqrt(xVec * xVec + yVec * yVec) * 8 * sin(iteration * 0.03);

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    for (int j = 0; j < LVL_HEIGHT; j++) {
        for (int i = 0; i < LVL_WIDTH; i++) {
            sprite.setPosition((float) (x + xOffset), (float) (y + yOffset + waveEffectOffs));

            sprite.setColor(sf::Color(
                    (int) (232 + colorWaveEffect * sin(i * 0.345 + j * 0.1256 + 1 + 0.03 * iteration)),
                    (int) (232 + colorWaveEffect * sin(i * 0.345 + j * 0.1256 + 2 - 0.03 * iteration)),
                    (int) (232 + colorWaveEffect * sin(-i * 0.345 - j * 0.1256 + 3 + 0.03 * iteration)),
                    alpha));

            if (level->isTileInArea(i, j, tileFilter)) {
                window.draw(sprite);
            }
            x += TILE_SIZE;
        }
        x = 0;
        y += TILE_SIZE;
    }
}

void LevelGO::drawOnEdgeOf(sf::RenderWindow& window, TileType top, TileType mid, std::shared_ptr<sf::Texture> text) {
    int x = 0;
    int y = VERTICAL_RENDER_DIFFERENCE;
    sf::Sprite sprite;
    text->setSmooth(true);
    sprite.setTexture(*text);
    for (int j = 0; j < LVL_HEIGHT; j++) {
        for (int i = 0; i < LVL_WIDTH; i++) {
            sprite.setPosition(x, y);
            if (level->getTileOn(i, j) == mid && level->getTileOn(i, j-1) == top) {
                window.draw(sprite);
            }
            x += TILE_SIZE;
        }
        x = 0;
        y += TILE_SIZE;
    }
}

void LevelGO::setEnemies(const std::shared_ptr<EnemiesGO>& enemies) {
    LevelGO::enemies = enemies;
}

void LevelGO::loadAdditionalEffects(ResourceLoader& resLoad) {
    floorTextures.add(resLoad.load("../resources/floor1.png"));
    floorTextures.add(resLoad.load("../resources/floor2.png"));
    floorTextures.add(resLoad.load("../resources/floor3.png"));
    floorTextures.add(resLoad.load("../resources/floor4.png"));

    verticalWallEffects.push_back(resLoad.load("../resources/eyeGrafittiC.png"));
    verticalWallEffects.push_back(resLoad.load("../resources/brickErr.png"));
    verticalWallEffects.push_back(resLoad.load("../resources/shadow.png"));
    verticalWallEffects.push_back(resLoad.load("../resources/pipe.png"));
    verticalWallEffects.push_back(resLoad.load("../resources/sink.png"));
    verticalWallEffects.push_back(resLoad.load("../resources/decals01.png"));
    verticalWallEffects.push_back(resLoad.load("../resources/decals02.png"));
    verticalWallEffects.push_back(resLoad.load("../resources/decals03.png"));
    verticalWallEffects.push_back(resLoad.load("../resources/barricadedDoor2.png"));
    verticalWallEffects.push_back(resLoad.load("../resources/door.png"));
    verticalWallEffects.push_back(resLoad.load("../resources/doorDoNotEnter.png"));
    verticalWallEffects.push_back(resLoad.load("../resources/doorMarked.png"));

    groundEffects.push_back(resLoad.load("../resources/paper3.png"));
    groundEffects.push_back(resLoad.load("../resources/bumper.png"));
    groundEffects.push_back(resLoad.load("../resources/line.png"));
    groundEffects.push_back(resLoad.load("../resources/gloves.png"));
    groundEffects.push_back(resLoad.load("../resources/paper4.png"));
    groundEffects.push_back(resLoad.load("../resources/sewer02.png"));
    groundEffects.push_back(resLoad.load("../resources/decals03.png"));
}

void LevelGO::generateNew() {
    levelId++;
    enemies->removeAll();

    std::vector<sf::Vector2<int>> enemyPos;
    int enemyCount = 1 + (int) (2.5 * log(4.4 * levelId - 2) - 0.7);
    level = std::make_shared<LevelTiles>(generateLevel(player->getTilePosition(), enemyPos, enemyCount));
    shadowLayer0 = nullptr;
    shadowLayer1 = nullptr;
    shadowLayer2 = nullptr;
    shadowLayer3 = nullptr;
    shadowLayer4 = nullptr;

    randomNumbersForTiles.clear();
    for (int i = 0; i < level->width() * level->height(); i++) {
        randomNumbersForTiles.push_back(getRandom(0, 1));
        randomNumbersForTiles2.push_back(getRandom(0, 1));
    }

    for (int i = 0; i < enemyPos.size(); i++) {
        EnemyGO e = createEnemy(levelId, *resourceLoader);
        auto pos = enemyPos.at(i);
        float xPos = pos.x * TILE_SIZE + TILE_SIZE/2;
        float yPos = pos.y * TILE_SIZE + TILE_SIZE/2 + VERTICAL_RENDER_DIFFERENCE;
        e.setPos({xPos, yPos});
        enemies->add(e, enemies);
    }

}

void LevelGO::update(Stage& stage) {
    iteration += stage.delta();
};