#ifndef ROGUELIKE_LEVELTILES_H
#define ROGUELIKE_LEVELTILES_H

#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "TileType.h"

/**
 * Represents level made up of tiles
 */
class LevelTiles {
    std::vector<TileType> tiles;
    int levelWidth;
    int levelHeight;

    ///transforms 2D index into a 1D index
    int getTileIndex(int x, int y) const {
        return y * levelWidth + x;
    }
public:
   ///sets all tiles to wall tiles
    LevelTiles(int width, int height);

     /**
      * Combines two maps so that everything that is not a wall in added map overwrites tiles on this map
      */
    void combineOverwrite(const LevelTiles &obj);

    /**
     * Combines two maps so that only walkable tiles are overwritten by only walkable tiles (for example slowing tile overwrites normal tile)
     */
    void combineOverwriteIfNotWall(const LevelTiles &obj);

    LevelTiles(const LevelTiles& l);

    bool isTileInArea(int x, int y, TileType tile);

    TileType getTileOn(int x, int y) const;

    void setTileType(int i, TileType tileType);

    void setTileType(int x, int y, TileType tileType);

    bool isWalkable(int x, int y);

    void setWalkableIfPossible(int x, int y);

    void setWalkable(int x, int y);

    bool isTileInBounds(int x, int y) const;

    ///draws a rectangle of given TileType with checks
    void setRectangle(int x, int y, int rectwidth, int rectheight, TileType tileType);

    const std::vector<TileType> &getTiles() const;

    int width() const;

    int height() const;


    ~LevelTiles() {
    }

};


#endif
