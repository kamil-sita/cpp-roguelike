#include "LevelTiles.h"

LevelTiles::LevelTiles(const LevelTiles &l) {
    this->levelWidth = l.levelWidth;
    this->levelHeight = l.levelHeight;
    this->tiles = std::vector<TileType >(l.tiles);
}

void LevelTiles::setRectangle(int x, int y, int rectwidth, int rectheight, TileType tileType) {

    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }

    if (x + rectwidth >= levelWidth) {
        rectwidth = levelWidth - x;
    }

    if (y + rectheight >= levelHeight) {
        rectheight = levelHeight - y;
    }

    for (int j = y; j < y + rectheight; j++) {
        for (int i = x; i < x + rectwidth; i++) {
            setTileType(i, j, tileType);
        }
    }
}

const std::vector<TileType> &LevelTiles::getTiles() const {
    return tiles;
}

int LevelTiles::width() const {
    return levelWidth;
}

int LevelTiles::height() const {
    return levelHeight;
}

LevelTiles::LevelTiles(int width, int height)  : levelWidth(width), levelHeight(height) {
    tiles = std::vector<TileType>();
    tiles.reserve(width * height);
    for (int i = 0; i < width * height; i++) {
        tiles.push_back(TileType::wall);
    }
}

void LevelTiles::combineOverwrite(const LevelTiles& obj)  {
    for (int i = 0; i < levelWidth * levelHeight; i++) {
        TileType tile = obj.tiles[i];
        if (tile != TileType::wall) {
            setTileType(i, tile);
        }
    }
}

void LevelTiles::combineOverwriteIfNotWall(const LevelTiles& obj) {
    for (int i = 0; i < levelWidth * levelHeight; i++) {
        if (tiles[i] != TileType::wall) {
            TileType tile = obj.tiles[i];
            if (tile != TileType::wall) {
                setTileType(i, tile);
            }
        }
    }
}

bool LevelTiles::isTileInArea(int x, int y, TileType tile)  {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (isTileInBounds(x + i, y + j)) {
                if (getTileOn(x + i, y + j) == tile) return true;
            }
        }
    }
    return false;
}

TileType LevelTiles::getTileOn(int x, int y) const  {
#if (RANGE_CHECKS_ENABLED)
    if (!isLegalTile(x, y)) {
        std::cerr << "out of range getTileOn" << std::endl;
    }
#endif
    return tiles[getTileIndex(x, y)];
}

void LevelTiles::setTileType(int i, TileType tileType)  {
#if (RANGE_CHECKS_ENABLED)
    if (i >= 0 && i < width() * height()) {
            tiles[i] = tileType;
        } else {
            std::cerr << "out of range setTileType" << std::endl;
        }
#else
    tiles[i] = tileType;
#endif
}

void LevelTiles::setTileType(int x, int y, TileType tileType)  {
    setTileType(getTileIndex(x, y), tileType);
}

bool LevelTiles::isWalkable(int x, int y)  {
    if (!isTileInBounds(x, y)) return false;
    TileType t = tiles[getTileIndex(x, y)];
    return t == TileType::floor || t == TileType::slowingFloor;
}

void LevelTiles::setWalkableIfPossible(int x, int y) {
    if (isTileInBounds(x, y)) setWalkable(x, y);
}

void LevelTiles::setWalkable(int x, int y)  {
#if RANGE_CHECKS_ENABLED==true
    if (!isLegalTile(x, y)) {
            std::cerr << "out of range setWalkable" << std::endl;
        } else {
            TileType  t = tiles[getTileIndex(x, y)];
            if (t == TileType::wall || t == TileType::verticalWall) {
                setTileType(getTileIndex(x, y), TileType::floor);
            }
        }
#else
    if (tiles[getTileIndex(x, y)] == TileType::wall) {
        setTileType(getTileIndex(x, y), TileType::floor);
    }
#endif

}

bool LevelTiles::isTileInBounds(int x, int y) const {
    return (x >= 0 && x < levelWidth) && (y >= 0 && y < levelHeight);
}
