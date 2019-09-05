#include "Room.h"

Room::Room(int startX, int startY, int sizeX, int sizeY, int levelWidth, int levelHeight, TileType tileType) : startX(startX),
                                                                                          startY(startY),
                                                                                          levelWidth(levelWidth),
                                                                                          levelHeight(levelHeight),
                                                                                          tileType(tileType){
    if (startX + sizeX >= levelWidth) {
        sizeX = levelWidth - startX;
    }
    if (startY + sizeY >= levelHeight) {
        sizeY = levelHeight - startY;
    }
    this->endX = startX + sizeX;
    this->endY = startY + sizeY;
}


Room::Room(int centerX, int centerY, int sizeX, int sizeY, const LevelTiles &lt, TileType type) : levelWidth(lt.width()), levelHeight(lt.height()), tileType(type) {
    startX = centerX - sizeX/2;
    endX = centerX + sizeX/2;
    if (startX < 0) startX = 0;
    if (startX >= levelWidth) startX = levelWidth - 1;
    if (endX < 0) endX = 0;
    if (endX >= levelWidth) endX = levelWidth - 1;

    startY = centerY - sizeY/2;
    endY = centerY + sizeY/2;
    if (startY < 0) startY = 0;
    if (startY >= levelHeight) startY = levelHeight - 1;
    if (endY < 0) endY = 0;
    if (endY >= levelHeight) endY = levelHeight - 1;

    if (endY - startY < sizeY) endY++;
    if (endX - startX < sizeX) endX++;

}

void Room::setTileType(TileType tileType) {
    Room::tileType = tileType;
}

LevelTiles Room::getLevel() {
    LevelTiles level(levelWidth, levelHeight);
    level.setRectangle(startX, startY, endX - startX, endY - startY, tileType);
    return level;
}

sf::Vector2<int> Room::getPointInRoom() const {
    return {(endX-startX)/2+startX, (endY-startY)/2+startY};
}

