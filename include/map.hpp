#pragma once

#include <raylib.h>
#include <map>

void InitiateBoard(Texture2D grass, Texture2D stone_1, Texture2D stone_2 , Texture2D bush_1, Texture2D bush_2, Texture2D bush_3);
void ModifyBoard();
struct Cell;
extern float x_cellSize;
extern float y_cellSize;
extern const int mapSize;
extern Vector2 player_position;
extern Vector2 monster_position;
extern std::map<std::pair<int,int>, Cell> cell_Instance;
extern int board[7][7];
extern int x;
extern int y;
extern int a;
extern int b;