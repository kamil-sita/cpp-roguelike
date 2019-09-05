#ifndef ROGUELIKE_LEVELTILESPATHFINDING_H
#define ROGUELIKE_LEVELTILESPATHFINDING_H

#include "LevelTiles.h"
#include "../Direction.h"
#include <queue>
#include <iomanip>
#include <vector>

struct PathfindingPosition {
    double preferablePathingCost; ///weighted approximate pathing cost up to this point from
    int x;
    int y;

    //comparison operator needed for ordered queue
    bool operator <( const PathfindingPosition& rhs) const {
        return preferablePathingCost > rhs.preferablePathingCost; //comparison is inverted - we are interested in a path with lowest cost, so we will cheap tiles first
    }
};

const int NOT_DISCOVERED_YET = -1;



/**
 * Aproximmated A* pathfinding. Finds probable optimal next move from START point towards the END point.
 */
class LevelTilesPathfinding {
    std::vector<int> tileCost; ///array of cost of moving from neighbouring tile to this tile
    std::vector<int> bestPathingCost; ///sum of costs of moving up to this point on probably best path

    bool ignoreWalls;
    bool ignoreWater;

    int width;
    int height;

    int startX;
    int startY;

    int endX;
    int endY;


//converts two dimensionsial index into one dimensional one
inline int getIndex(int x, int y) {
    return width * y + x;
}

void addNeighboursToQueue(int x, int y, std::priority_queue<PathfindingPosition> &queue);
void addToQueue(int costUpToThisPoint, int x, int y, std::priority_queue<PathfindingPosition> &queue, double preferablePathingCostModifier);
bool isInBounds(int x, int y);
void clearPathCost();
bool isCostLower(sf::Vector2<int> pos, int oldCost);

public:
    LevelTilesPathfinding(const LevelTiles& lt, bool ignoreWalls = false, bool ignoreWater = false);

    ///copies level to the pathfinder without reallocating memory for new LevelTilesPathfinding object. Allows for object reuse.
    void resetLevelTiles(const LevelTiles& l);

    ///sets initial position
    void setStart(sf::Vector2i pos);

    ///sets target position
    void setEnd(sf::Vector2i pos);

    ///generates path, returns true if succeds
    bool generatePath();

     ///returns next direction of movement from starting point to ending point
    Direction getNextDirection();

    ~LevelTilesPathfinding() = default;

    double calculateEuclideanDistance(int x, int y) const;
};


#endif
