#include "Direction.h"

sf::Vector2<int> getNewPos(int x, int y, Direction direction) {
    return sf::Vector2<int>(x, y) + getDirectionVector(direction);
}

sf::Vector2<int> getDirectionVector(Direction direction) {
    switch (direction) {
        case west:
            return {-1, 0};
        case north:
            return {0, -1};
        case east:
            return {1, 0};
        case south:
            return {0, 1};
    }
    return {0, 0};
}
