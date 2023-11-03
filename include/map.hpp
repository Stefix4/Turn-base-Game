#pragma once

#include <raylib.h>

void InitiateBoard(Texture2D grass, Texture2D stone_1, Texture2D stone_2 , Texture2D bush_1, Texture2D bush_2, Texture2D bush_3);
void ModifyBoard();
extern float x_cellSize;
extern float y_cellSize;
extern const int mapSize;
extern Vector2 player_position;
extern int board[7][7];
extern int x;
extern int y;