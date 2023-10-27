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
    Texture2D stone_1=LoadTexture("./resources/stone_v1.png");
    Texture2D stone_2=LoadTexture("./resources/stone_v2.png");
    Texture2D stone_3=LoadTexture("./resources/stone_v2(2).png");
    Texture2D bush_1 = LoadTexture("./resources/bush_v1.png");
    Texture2D bush_2 = LoadTexture("./resources/bush_v1(2).png");
    Texture2D bush_3 = LoadTexture("./resources/bush_v2.png");
    Texture2D bush_4 = LoadTexture("./resources/bush_v2(2).png");


     //game loop
    while (!WindowShouldClose())
    {   

        BeginDrawing();
        toggleFullscreen();
        InitiateBoard(grass,stone_1,stone_2,stone_3,bush_1,bush_2,bush_3,bush_4);
        ModifyBoard();
        Char(x_cellSize,y_cellSize,hiro);
        ClearBackground(WHITE);
        EndDrawing();
    }

    UnloadTexture(hiro);
    UnloadTexture(grass);
    UnloadTexture(stone_1);
    UnloadTexture(stone_2);
    UnloadTexture(stone_3);
    UnloadTexture(bush_1);
    UnloadTexture(bush_2);
    UnloadTexture(bush_3);
    UnloadTexture(bush_4);

    CloseWindow();        


    return 0;
}