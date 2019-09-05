#ifndef ROGUELIKE_TILETYPE_H
#define ROGUELIKE_TILETYPE_H

enum class TileType {
    wall,
    floor,
    slowingFloor,
    verticalWall
};

const int NON_PASSABLE = -1;
const int FLOOR_COST = 1;
const int SLOWING_FLOOR_COST = 6;
const int WALL_COST = NON_PASSABLE;

int getCost(TileType tileType, bool ignoreWalls, bool ignoreWater);

#endif
