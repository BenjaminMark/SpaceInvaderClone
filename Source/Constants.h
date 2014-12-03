#pragma once

#include "Vector2.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const int FPS_CAP = 60;
const int TICKS_PER_FRAME = 1000 / FPS_CAP;
const int PLAYER_SPEED = 10;
const Vector2 PLAYER_STARTPOS = Vector2(WINDOW_WIDTH / 2 - 24, WINDOW_HEIGHT - 75);
const int PLAYER_PROJECTILE_SPEED = 17;
const int PLAYER_START_LIVES = 3;
const int PLAYER_UPGRADE_ONE = 500;
const int PLAYER_UPGRADE_TWO = 1500;

const Vector2 ENEMY_STARTPOS = Vector2(40, 80);
const int ENEMY_HOR_DISTANCE = 90;
const int ENEMY_ROW_DISTANCE = 35;
const int ENEMY_NUM_PER_ROW = 10;
const int ENEMY_NUM_ROWS = 4;
const int ENEMY_MOVE_DIST_HOR = 7;
const int ENEMY_MOVE_DIST_VERT = 30;
const int ENEMY_NUM_MOVES = 11;
const int ENEMY_MOVE_DELAY = FPS_CAP / 2;
const int ENEMY_MOVE_DELAY_DECREASE = 5;
const int ENEMY_SHOT_DELAY_MAX = 3000;
const int ENEMY_SHOT_DELAY_MIN = 250;
const int ENEMY_SHOT_DELAY_RANGE = ENEMY_SHOT_DELAY_MAX - ENEMY_SHOT_DELAY_MIN;
const int ENEMY_SCORE_VALUE = 10;
const int ENEMY_PROJECTILE_SPEED = 6;

const int BUNKER_NUMLIVES = 15;
const Vector2 BUNKER_STARTPOS = Vector2(100, WINDOW_HEIGHT - 175);