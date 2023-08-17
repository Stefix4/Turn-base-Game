#include <raylib.h>

#include "map.hpp"
#include "characters.hpp"
#include "game.hpp"

float screenWidth = 1280;
float screenHeight = 780;

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
    Texture2D hiro = LoadTexture("./resources/hiro.png");
    Texture2D grass = LoadTexture("./resources/grass.png");


     //game loop
    while (!WindowShouldClose())
    {   

        BeginDrawing();
        toggleFullscreen();
        DrawChessBoard(grass);
        Char(x_cellSize,y_cellSize,hiro);
        ClearBackground(WHITE);
        EndDrawing();
    }

    UnloadTexture(hiro);
    UnloadTexture(grass);

    CloseWindow();        


    return 0;
}