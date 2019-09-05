#ifndef ROGUELIKE_DIRECTIONFUN_H
#define ROGUELIKE_DIRECTIONFUN_H

#include <SFML/System/Vector2.hpp>

enum Direction {
    west, north, east, south
};

///returns new position after moving from (X, Y) towards direction
sf::Vector2<int> getNewPos(int x, int y, Direction direction);

///returns direction vector
sf::Vector2<int> getDirectionVector(Direction direction);

#endif

