#pragma once

#include <raylib.h>

void DrawChessBoard(Texture2D grass);
extern float x_cellSize;
extern float y_cellSize;
extern const int mapSize;
extern Vector2 player_position;
extern bool is_ocupied;