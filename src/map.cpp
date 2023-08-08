#include <raylib.h>

#include "map.hpp"
#include "game.hpp"

int boardSize = 8;
int cellSize =screenWidth/boardSize;

void DrawChessBoard() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            Color cellColor = ((i + j) % 2 == 0) ? LIGHTGRAY : DARKGRAY;
            DrawRectangle(j * cellSize, i * cellSize, cellSize, cellSize, cellColor);
        }
    }
}
