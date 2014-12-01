#pragma once

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const int FPS_CAP = 60;
const int TICKS_PER_FRAME = 1000 / FPS_CAP;
const int PLAYER_SPEED = 10;
const int PROJECTILE_SPEED = 12;

const Vector2 ENEMY_STARTPOS = Vector2(128, 80);
const int ENEMY_HOR_DISTANCE = 90;
const int ENEMY_ROW_DISTANCE = 35;
const int ENEMIES_PER_ROW = 9;
const int ENEMY_NUM_ROWS = 4;
const int ENEMY_MOVE_DIST_HOR = 7;
const int ENEMY_MOVE_DIST_VERT = 30;
const int ENEMY_NUM_MOVES = 9;