#include "LevelTilesPathfinding.h"
#include <queue>
#include <math.h>

inline void LevelTilesPathfinding::clearPathCost() {
    for (int i = 0; i < width * height; i++) {
        bestPathingCost[i] = NOT_DISCOVERED_YET;
    }
}


LevelTilesPathfinding::LevelTilesPathfinding(const LevelTiles& lt, bool ignoreWalls, bool ignoreWater): width(lt.width()), height(lt.height()), ignoreWalls(ignoreWalls), ignoreWater(ignoreWater) {
    this->tileCost.reserve(width * height);
    this->bestPathingCost.reserve(width * height);
    resetLevelTiles(lt);
}

void LevelTilesPathfinding::resetLevelTiles(const LevelTiles &l) {
    clearPathCost();
    for (int i = 0; i < width * height; i++) {
        this->tileCost[i] = getCost(l.getTiles()[i], ignoreWalls, ignoreWater);
    }
}

bool LevelTilesPathfinding::generatePath() {
    PathfindingPosition start = {0, startX, startY};
    std::priority_queue<PathfindingPosition> queue;
    queue.push(start);
    bestPathingCost[getIndex(startX, startY)] = 0;
    bool found = false;
    int i = 0;
    while (!queue.empty()) {
        i++;
        auto pos = queue.top();
        queue.pop();
        if (pos.x == endX && pos.y == endY) {
            found = true;
            break;
        }
        addNeighboursToQueue(pos.x, pos.y, queue);
    }
    return found;
}

void LevelTilesPathfinding::addNeighboursToQueue(int x, int y, std::priority_queue<PathfindingPosition> &queue) {
    int thisCost = bestPathingCost[getIndex(x, y)];
    int deltaY = endY - y;
    int deltaX = endX - x;

    addToQueue(thisCost, x - 1, y, queue, deltaX <= 0 ? 1 : 8); //droższe poruszanie się w w strony przeciwne do kierunku
    addToQueue(thisCost, x + 1, y, queue, deltaX >= 0 ? 1 : 8);
    addToQueue(thisCost, x, y - 1, queue, deltaY <= 0 ? 1 : 8);
    addToQueue(thisCost, x, y + 1, queue, deltaY >= 0 ? 1 : 8);
}

inline bool LevelTilesPathfinding::isInBounds(int x, int y) {
    return (x >= 0 && x < width) && (y >= 0 && y < height);
}

void LevelTilesPathfinding::addToQueue(int costUpToThisPoint, int x, int y, std::priority_queue<PathfindingPosition> &queue, double preferablePathingCostModifier = 1) {
    if (!isInBounds(x, y)) return;

    int index = getIndex(x, y);
    if (tileCost[index] == NON_PASSABLE) return;

    int thisTileCost = tileCost[index];
    int thisPathingCost = costUpToThisPoint + thisTileCost;

    if (bestPathingCost[index] != NOT_DISCOVERED_YET) { //already found path to here
        if (bestPathingCost[index] <= thisPathingCost) { //and it is cheaper (better) path
            return; //discard this path
        }
    }

    bestPathingCost[index] = thisPathingCost;

    //weighted cost is based on:
    //costUpToThisPoint - weighted cost up to this point
    //preferablePathingCostModifier - guess whether moving in this direction is better than the others
    //euclidean distance - if this tile is closed to the END tile, it is probably closer than other tiles.
    double weightedCost = costUpToThisPoint + thisTileCost * preferablePathingCostModifier * calculateEuclideanDistance(x, y);

    queue.push({weightedCost, x, y});
}

double LevelTilesPathfinding::calculateEuclideanDistance(int x, int y) const { return std::sqrt((endX - x) * (endX - x) + (endY - y) * (
            endY - y) ); }

bool LevelTilesPathfinding::isCostLower(sf::Vector2<int> pos, int oldCost) {
    if (!isInBounds(pos.x, pos.y)) return false;
    int cost = bestPathingCost[getIndex(pos.x, pos.y)];
    if (cost == NOT_DISCOVERED_YET) return false;
    return cost < oldCost;
}

/*
 * Start and End swap optimization:
 *
 * Start and end positions don't really matter for the pathfinding process itself, but they do matter when the moving itself happens.
 * The target object will however move from the start to the end point, not the other way around. I assume that the pathfinding will be launched
 * for every probable pathing point from START to END (start, tile1 = getNextDirection from start, tile2 = getNextDirection from tile1...)
 * All that matters then for LevelTilesPathfinding object is to find tile that is part of the "correct"* path.
 *
 * If the process was running from START to END tiles and the cost increased we would be looking at 4 probable paths! Why? LevelTilesPathfinding does not
 * clear up the tiles cost that are not part of the solution - We would have to backtrack solution from the END to START again to have any usable information.
 *
 * However, when we generate paths from END to START instead we are looking at at most 1 solution, which HAS to be "correct"*, as in the last
 * iteration tile "pointer" moved from n-1th tile to END and found path. So when we need only next tile in path towards the objective (because it can move!)
 * this is a pretty interesting solution without backtracking.
 *
 *
 *
 * "correct"* - as in a path that is a complete path from START to END, but might not be the most correct one.
 */

Direction LevelTilesPathfinding::getNextDirection() {
    //due to some optimizations start and end are swapped - read explanation above

    int posX = endX;
    int posY = endY;
    int cost = bestPathingCost[getIndex(posX, posY)];

    if (isCostLower(getNewPos(posX, posY, west), cost)) return west;
    if (isCostLower(getNewPos(posX, posY, south), cost)) return south;
    if (isCostLower(getNewPos(posX, posY, north), cost)) return north;
    if (isCostLower(getNewPos(posX, posY, east), cost)) return east;

    return north;
}


void LevelTilesPathfinding::setStart(sf::Vector2i pos)  {
    //due to some optimizations start and end are swapped - read explanation above
    endX = pos.x;
    endY = pos.y;
}

void LevelTilesPathfinding::setEnd(sf::Vector2i pos)  {
    //due to some optimizations start and end are swapped - read explanation above
    startX = pos.x;
    startY = pos.y;
}