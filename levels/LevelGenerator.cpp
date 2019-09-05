#include <random>
#include <vector>
#include <cmath>
#include <algorithm>
#include "LevelGenerator.h"
#include "Room.h"
#include "../Random.h"
#include "LevelTilesPathfinding.h"
#include "LevelManipulator.h"
#include "../ConstSettings.h"
#include "RoomGroup.h"

const int width = LVL_WIDTH;
const int height = LVL_HEIGHT;
const int roomSizeMin = 2;
const int slowingRoomCount = 20;


void fillEmptySpaceslWithRooms(std::vector<Room> &floorRooms, LevelTiles &base, double maxEmptyArea, int roomSize);
void fillEmptySpaceslWithSmallRooms(std::vector<Room> &floorRooms, LevelTiles &base, double maxEmptyArea, int roomSize);

void connectRooms(std::vector<Room> &floorRooms, LevelTiles &base);

Room getRoom(TileType tileType, int x, int y, LevelTiles& lt, int size) {
    return Room(x, y, getRandomInt(roomSizeMin, size + 2), getRandomInt(roomSizeMin, size),
            lt, tileType);
}

Room getRoom(TileType tileType, int x, int y, LevelTiles& lt, int minSize, int maxSize) {
    return Room(x, y, getRandomInt(minSize, maxSize + 1), getRandomInt(minSize, maxSize),
                lt, tileType);
}

Room getRoom(TileType tileType, LevelTiles& lt) {
    return getRoom(tileType, getRandomInt(0, lt.width()), getRandomInt(0, lt.height()), lt, roomSizeMin);
}

void connectRooms(const Room& room0, const Room& room1, LevelTiles& level) {
    auto pos = room0.getPointInRoom();
    auto end = room1.getPointInRoom();
    int deltax = abs(pos.x - end.x);
    int deltay = abs(pos.y - end.y);
    bool checkingX = (deltax >= deltay);
    while (pos != end) {
        deltax = abs(pos.x - end.x);
        deltay = abs(pos.y - end.y);
        if (checkingX && deltax == 0) checkingX = false;
        if (!checkingX && deltay == 0) checkingX = true;
        if (checkingX) {
            if (pos.x > end.x) {
                pos.x--;
            } else if (pos.x < end.x) {
                pos.x++;
            }
        } else {
            if (pos.y > end.y) {
                pos.y--;
            } else if (pos.y < end.y) {
                pos.y++;
            }
        }

        for (int i = 0; i <= 0; i++) {
            for (int j = 0; j <= 1; j++) {
                level.setWalkableIfPossible(pos.x + i, pos.y + j);
            }
        }

    }
}

void generateNormalRooms(std::vector<Room> &floorRooms, LevelTiles &base, sf::Vector2<int> playerPos) {
    floorRooms.push_back(getRoom(TileType::floor, playerPos.x, playerPos.y, base, 7, 7));
    base.combineOverwrite(floorRooms.at(floorRooms.size() - 1).getLevel());

    fillEmptySpaceslWithRooms(floorRooms, base, 7, 4);
    fillEmptySpaceslWithSmallRooms(floorRooms, base, 5, 2);
}

LevelTiles generateSimpleLevel(std::vector<Room> &floorRooms, sf::Vector2<int> playerPos) {
    LevelTiles base(width - 2, height - 2);
    std::vector<Room> slowingRooms;

    //the generated level is placed inside a border made of wall tiles, so the position of player is moved by (-1, -1) vector
    playerPos.x -= 1;
    playerPos.y -= 1;

    generateNormalRooms(floorRooms, base, playerPos);

    connectRooms(floorRooms, base);

    for (int i = 0; i < slowingRoomCount; i++) {
        slowingRooms.push_back(getRoom(TileType::slowingFloor, base));
        base.combineOverwriteIfNotWall(slowingRooms.at(slowingRooms.size()-1).getLevel());
    }

    return base;
}

void connectRooms(std::vector<Room> &floorRooms, LevelTiles &base) {
    std::vector<RoomGroup> rooms;


    for (int i = 0; i < floorRooms.size(); i++) {
        rooms.emplace_back(floorRooms.at(i));
    }

    //connecting closest rooms
    int size = floorRooms.size();
    for (int i = 0; i < size - 1; i++) {
        std::shuffle(rooms.begin(), rooms.end(), std::mt19937(std::random_device()()));
        auto &r0 = rooms.at(0);
        double minLength = std::numeric_limits<double>::max();
        int minLengthIndex = 1;

        for (int j = 1; j < rooms.size(); j++) {
            double length = rooms.at(j).getApproximateDistance(r0);
            if (length < minLength) {
                minLength = length;
                minLengthIndex = j;
            }
        }

        auto &closest = rooms.at(minLengthIndex);
        auto pairToConnect = closest.getClosestRooms(r0);
        connectRooms(pairToConnect.first, pairToConnect.second, base);
        RoomGroup newR(r0, closest);
        rooms.erase(rooms.begin() + minLengthIndex);
        rooms[0] = newR;
    }

    //connecting rooms based on distance
    for (int i = 0; i < floorRooms.size(); i++) {
        for (int j = i + 1; j < floorRooms.size(); j++) {
            auto pos0 = floorRooms.at(i).getPointInRoom();
            auto pos1 = floorRooms.at(j).getPointInRoom();

            double dist = sqrt( (pos0.x - pos1.x) * (pos0.x - pos1.x) + (pos0.y - pos1.y) * (pos0.y - pos1.y));
            if (dist < CONNECT_LENGTH && getRandom(0, 1) <= RANDOM_CONNECT_CHANCE) {
                connectRooms(floorRooms.at(i), floorRooms.at(j), base);
            }
        }
    }


}


void fillEmptySpaceslWithRooms(std::vector<Room> &floorRooms, LevelTiles &base, double maxEmptyArea, int roomSize) {
    for (int x = 0; x < base.width(); x++) {
        for (int y = 0; y < base.height(); y++) {

            double maxLength = WIDTH * HEIGHT;

            for (int i = 0; i < floorRooms.size(); i++) {
                auto &room = floorRooms.at(i);
                auto point = room.getPointInRoom();
                double length = sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
                if (length < maxLength) maxLength = length;
            }

            if (maxLength > maxEmptyArea) {
                auto room = getRoom(TileType::floor, x, y, base, roomSize);
                base.combineOverwrite(room.getLevel());
                floorRooms.push_back(room);
            }

        }
    }
}

void fillEmptySpaceslWithSmallRooms(std::vector<Room> &floorRooms, LevelTiles &base, double maxEmptyArea, int roomSize) {
    for (int x = 0; x < base.width(); x++) {
        for (int y = 0; y < base.height(); y++) {

            double maxLength = WIDTH * HEIGHT;

            for (int i = 0; i < floorRooms.size(); i++) {
                auto &room = floorRooms.at(i);
                auto point = room.getPointInRoom();
                double length = sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
                if (length < maxLength) maxLength = length;
            }

            if (maxLength > maxEmptyArea) {
                auto room = getRoom(TileType::floor, x, y, base, roomSize - 1, roomSize);
                base.combineOverwrite(room.getLevel());
                floorRooms.push_back(room);
            }

        }
    }
}


LevelTiles generateLevel(sf::Vector2<int> playerPos, std::vector<sf::Vector2<int>>& enemyPositions, int enemyCount) {
    //generowanie poziomu
    std::vector<Room> rooms;
    LevelTiles level = generateSimpleLevel(rooms, playerPos);
    LevelManipulator levelManipulator(level);
    levelManipulator.generateBorder();
    levelManipulator.setMinimumWallHeight();
    level = levelManipulator.getLevelTiles();

    //generowanie pozycji przeciwników
    std::shuffle(rooms.begin(), rooms.end(), std::mt19937(std::random_device()()));
    int j = 0;
    for (int i = 0; i < enemyCount; i++) {
        j++;
        long roomId = (j + i) % rooms.size();
        auto room = rooms.at(roomId);
        auto roomPos = room.getPointInRoom();
        int x = roomPos.x;
        int y = roomPos.y;
        double length = sqrt((x - playerPos.x) * (x - playerPos.x) + (y - playerPos.y) * (y - playerPos.y));

        if (length > 15) {
            enemyPositions.emplace_back(x, y);
        } else {
            i--;
        }

    }


    return level;
}
