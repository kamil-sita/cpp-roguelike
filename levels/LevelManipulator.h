#ifndef ROGUELIKE_LEVELMANIPULATOR_H
#define ROGUELIKE_LEVELMANIPULATOR_H


#include "LevelTiles.h"

/*
 * "high level" manipulator of LevelTiles objects.
 */
class LevelManipulator {
    LevelTiles levelTiles;
    void setVertWall(int y, int x);

public:
    LevelManipulator(LevelTiles levelTiles1) : levelTiles(levelTiles1) {

    }

    void setMinimumWallHeight();
    void generateBorder();
    const LevelTiles &getLevelTiles() const;


};


#endif
