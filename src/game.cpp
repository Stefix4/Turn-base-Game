#include <raylib.h>

#include "functions.hpp"
#include "map.hpp"
#include "characters.hpp"
#include "game.hpp"

const int screenWidth = 1280;
const int screenHeight = 780;

int main(void)
{


    //initialling the window
    InitWindow(screenWidth,screenHeight, "Turn-base-Game");
    SetTargetFPS(144);
    SetWindowMinSize(screenWidth,screenHeight);
    
    //declaring images/textures



     //game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        toggleFullscreen();
        DrawChessBoard();
        Char();
        ClearBackground(WHITE);
        EndDrawing();
    }


    CloseWindow();        

    return 0;
}