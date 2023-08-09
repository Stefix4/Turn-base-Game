#include <raylib.h>

#include "map.hpp"
#include "game.hpp"


int mapSize=7;
float x_cellSize =screenWidth/mapSize;
float y_cellSize=screenHeight/mapSize;

void DrawChessBoard() {
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            Color cellColor = ((i + j) % 2 == 0) ? LIGHTGRAY : DARKGRAY;
            DrawRectangle(j * x_cellSize, i * y_cellSize, x_cellSize, y_cellSize, cellColor);
        }
    }
}
