#include "LevelManipulator.h"
#include "../Random.h"

const LevelTiles &LevelManipulator::getLevelTiles() const {
    return levelTiles;
}

void LevelManipulator::setMinimumWallHeight() {

    for (int y = 0; y < levelTiles.height() - 1; y++) {
        for (int x = 1; x < levelTiles.width() - 1; x++) {
            setVertWall(y, x);
        }
    }

}

void LevelManipulator::setVertWall(int y, int x) {
    if (levelTiles.getTileOn(x, y) == TileType::wall && levelTiles.getTileOn(x, y + 1) != TileType::wall) {
        //it is last wall vertically in this group


        if (!levelTiles.isWalkable(x, y - 1)) { //thick wall, swapping last wall tile vertically to vertical wall
            levelTiles.setTileType(x, y, TileType::verticalWall);
        } else if (levelTiles.isWalkable(x, y + 1) && levelTiles.isWalkable(x, y + 1)) { //passage is thick so we can make change floor tile to a wall tile
            levelTiles.setTileType(x, y + 1, TileType::wall); //we just created a thicker wall, vertical wall will be added in one of the next iterations
        } else { //no way to make vertical wall, so we delete it instead
            levelTiles.setWalkable(x, y);
        }
    }
}

void LevelManipulator::generateBorder() {
    auto levelCpy = this->levelTiles;
    levelTiles = LevelTiles(levelCpy.width() + 2, levelCpy.height() + 2);
    for (int y = 0; y < levelCpy.height(); y++) {
        for (int x = 0; x < levelCpy.width(); x++) {
            levelTiles.setTileType(x + 1, y + 1, levelCpy.getTileOn(x, y));
        }
    }
}
