#ifndef ROGUELIKE_LEVELGO_H
#define ROGUELIKE_LEVELGO_H


#include "../engine/ResourceLoader.h"
#include "../engine/GameObject.h"
#include "../levels/LevelTiles.h"
#include "../levels/LevelGenerator.h"
#include "../Random.h"
#include "../engine/TextureGroup.h"
#include "PlayerGO.h"
#include "enemy/EnemyGO.h"
#include "../ConstSettings.h"

#include <SFML/Graphics/Sprite.hpp>
#include <cmath>

class LevelGO : public GameObject {
private:
    int levelId = 0;

    std::shared_ptr<PlayerGO> player;
    std::shared_ptr<EnemiesGO> enemies;

    std::shared_ptr<LevelTiles> level;

    //additional effects, rendered on top of walls or floors
    std::vector<std::shared_ptr<sf::Texture>> verticalWallEffects;
    std::vector<std::shared_ptr<sf::Texture>> groundEffects;

    TextureGroup floorTextures;

    std::shared_ptr<sf::Texture> wallTexture;
    std::shared_ptr<sf::Texture> verticalWallTexture;
    std::shared_ptr<sf::Texture> waterAlpha;
    std::shared_ptr<sf::Texture> topWater;

    //shadow layers so shadows are only calculated once
    std::shared_ptr<sf::Texture> shadowLayer0;
    std::shared_ptr<sf::Texture> shadowLayer1;
    std::shared_ptr<sf::Texture> shadowLayer2;
    std::shared_ptr<sf::Texture> shadowLayer3;
    std::shared_ptr<sf::Texture> shadowLayer4;

    std::vector<double> randomNumbersForTiles;
    std::vector<double> randomNumbersForTiles2;

    double iteration = 0;

    inline double semiRandomForTile(int x, int y) {
        return randomNumbersForTiles[y * level->width() + x];
    }

    inline double semiRandomForTile2(int x, int y) {
        return randomNumbersForTiles2[y * level->width() + x];
    }

    void drawWaveLayer(sf::RenderWindow& window, TileType tileFilter,
                       std::shared_ptr<sf::Texture> waterTexture,
                       double colorWaveEffect, double xVec, double yVec, int alpha);
    template<typename Proc> void drawLayer(sf::RenderWindow& window, TileType tileFilter, Proc textureFromCoord, double ratio = 1.0);
    void drawShadow(sf::RenderWindow& window, TileType shadowType, sf::Color color, std::shared_ptr<sf::Texture>& layer,
                    std::shared_ptr<sf::Shader> shader = nullptr, int diffX = 0, bool invert = false);
    void drawOnEdgeOf(sf::RenderWindow& window, TileType top, TileType mid, std::shared_ptr<sf::Texture> text);

    std::shared_ptr<sf::Shader> blurShader;
    bool shaderInitialized = false;
    std::shared_ptr<sf::Shader> getBlurShader();

    std::shared_ptr<sf::Texture> generateShadow(const TileType& shadowType, const sf::Color& color, std::shared_ptr<sf::Texture>& sLayer,
                                                const std::shared_ptr<sf::Shader>& shader, int diffX, bool invert);
    void addToxicParticles();
protected:
    void draw(sf::RenderWindow& window) override;

public:
    LevelGO(ResourceLoader* resLoad, std::shared_ptr<PlayerGO> player);

    void loadAdditionalEffects(ResourceLoader &resLoad);

    void generateNew();

    const std::shared_ptr<LevelTiles> &getLevel() const;

    void update(Stage &stage) override;

    void setEnemies(const std::shared_ptr<EnemiesGO>& enemies);


    ~LevelGO() override {

    };


};


#endif
