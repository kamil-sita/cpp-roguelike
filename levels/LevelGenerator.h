#ifndef ROGUELIKE_LEVELGENERATOR_H
#define ROGUELIKE_LEVELGENERATOR_H

#include "LevelTiles.h"
#include <memory>

LevelTiles generateLevel(sf::Vector2<int> playerPos, std::vector<sf::Vector2<int>>& enemyPositions, int enemyCount);

#endif
