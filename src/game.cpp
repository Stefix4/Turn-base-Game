#include <raylib.h>

#include "functions.hpp"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 780;

    //initialling the window
    InitWindow(screenWidth,screenHeight, "Turn-base-Game");
    SetTargetFPS(144);
    SetWindowMinSize(screenWidth,screenHeight);
    
    //declaring images/textures



     //game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        toggle_fullscreen();
        ClearBackground(WHITE);
        EndDrawing();
    }


    CloseWindow();        

    return 0;
}