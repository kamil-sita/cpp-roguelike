#ifndef ROGUELIKE_ROOM_H
#define ROGUELIKE_ROOM_H


#include "LevelTiles.h"

class Room {
    int startX;
    int startY;
    int endX;
    int endY;
    int levelWidth;
    int levelHeight;
    TileType tileType;
public:
    Room(int startX, int startY, int sizeX, int sizeY, int levelWidth, int levelHeight, TileType type);
    Room(int centerX, int centerY, int sizeX, int sizeY, const LevelTiles& lt, TileType type);


    LevelTiles getLevel();

    sf::Vector2<int> getPointInRoom() const;

    void setTileType(TileType tileType);
};


#endif
