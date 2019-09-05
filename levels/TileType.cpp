#include "TileType.h"

int getCost(TileType tileType, bool ignoreWalls, bool ignoreWater) {

    if (ignoreWalls && (tileType == TileType::wall || tileType == TileType::verticalWall)) return FLOOR_COST;
    if (ignoreWater && tileType == TileType::slowingFloor) return FLOOR_COST;

    switch (tileType) {
        case TileType::verticalWall:
        case TileType::wall:
            return WALL_COST;
        case TileType::floor:
            return FLOOR_COST;
        case TileType::slowingFloor:
            return SLOWING_FLOOR_COST;
    }
    return -1;
}
