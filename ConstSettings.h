#ifndef ROGUELIKE_CONSTSETTINGS_H
#define ROGUELIKE_CONSTSETTINGS_H

//window settings, probably should not be changed as the game is rather rigid in placement of tiles, etc
const int HEIGHT = 900;
const int WIDTH = 1600;

const int TARGET_FRAMERATE = 60;

//tile render difference due to the bar appearing above the level
const int VERTICAL_RENDER_DIFFERENCE = 50;

//level width, height, tile size
const int LVL_WIDTH = 40;
const int LVL_HEIGHT = 22;
const int TILE_SIZE = 40;
const int PLAYER_AND_ENEMY_SIZE = 34;

//level generator
const double RANDOM_CONNECT_CHANCE = 0.1;
const double CONNECT_LENGTH = 13;

//game - movement
const double DEFAULT_SPEED = 2.2;
const double BULLET_SPEED = 8.0;
const double SIZE_OF_HITBOX_CHECKING = 12;

//game - other
const double PROJECTILE_DMG = 5;
const double ENEMY_HP_PER_LEVEL = 8;

const double BULLET_COOLDOWN = 0.5;
const double TUMBLE_COOLDOWN = 1.3;
const double TUMBLE_TIME = 0.6;
const double TUMBLE_INITIAL_SPEED_MULTIPLIER = 3.5;
const double TUMBLE_SLOWDOWN = 1.4;

//effects
const double COOLDOWN_BETWEEN_ROUNDS = 2;
const double MENU_FADEOUT_TIME = 1.7;
const double GAME_FADEOUT_TIME = 3.5;

const double INVULNERABILITY_AFTER_DAMAGE = 2.5;

#endif
