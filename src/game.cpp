#include <raylib.h>

#include "map.hpp"
#include "characters.hpp"
#include "game.hpp"
#include "movement.hpp"

int screenWidth = 1280;
int screenHeight = 780;

//fullscreen
void toggleFullscreen(){
    if(IsKeyPressed(KEY_F11)){
        ToggleFullscreen();
    }
    if(IsWindowFullscreen()){
        screenWidth = GetRenderWidth();
        screenHeight = GetRenderHeight();
    }
    else{
        screenWidth = 1280;
        screenHeight = 780;
    }
}

int main(void)
{

    //initialling the window
    InitWindow(screenWidth,screenHeight, "Turn-base-Game");
    SetTargetFPS(144);
    //SetWindowMinSize(screenWidth,screenHeight);
    
    //declaring images/textures



     //game loop
    while (!WindowShouldClose())
    {   

        BeginDrawing();
        toggleFullscreen();
        DrawChessBoard();
        Char(x,y,x_cellSize,y_cellSize);
        movement();
        ClearBackground(WHITE);
        EndDrawing();
    }


    CloseWindow();        

    return 0;
}