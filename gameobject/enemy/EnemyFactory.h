#ifndef ROGUELIKE_ENEMYFACTORY_H
#define ROGUELIKE_ENEMYFACTORY_H

#include "EnemyGO.h"
#include "../../engine/ResourceLoader.h"

EnemyGO createEnemy(int levelId, ResourceLoader& resourceLoader);

#endif
