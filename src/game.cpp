#include <raylib.h>
#include <future>
#include <chrono>
#include <thread>


#include "map.hpp"
#include "characters.hpp"
#include "game.hpp"
#include "functions.hpp"
#include "menu.hpp"

float screenWidth = 1280;
float screenHeight = 780;

MenuState currentMenuState = MenuState::MENU;

int main(void)
{   
    

    //initialling the window
    InitWindow(screenWidth,screenHeight, "Turn-base-Game");
    SetTargetFPS(30);
    //SetWindowMinSize(screenWidth,screenHeight);
    
    //declaring images/textures
    Texture2D hiro = LoadTexture("./resources/hiro.png");
    Texture2D grass = LoadTexture("./resources/grass.png");
    Texture2D stone_1=LoadTexture("./resources/stone_v1.png");
    Texture2D stone_2=LoadTexture("./resources/stone_v3.png");
    Texture2D bush_1 = LoadTexture("./resources/bush_v1.png");
    Texture2D bush_2 = LoadTexture("./resources/bush_v2.png");
    Texture2D bush_3 = LoadTexture("./resources/bush_v3.png");


     //game loop
    while (!WindowShouldClose())
    {   

        BeginDrawing();
        toggleFullscreen();
        menus(hiro, grass, stone_1, stone_2, bush_1, bush_2, bush_3);
        ClearBackground(WHITE);

        if (menuStateSelected == 1)
            currentMenuState = MenuState::PLAY;
        if (menuStateSelected == 2)
            currentMenuState = MenuState::GAME_OVER;
        if (menuStateSelected == 3)
            currentMenuState = MenuState::EXIT;

        EndDrawing();
    }

    UnloadTexture(hiro);
    UnloadTexture(grass);
    UnloadTexture(stone_1);
    UnloadTexture(stone_2);
    UnloadTexture(bush_1);
    UnloadTexture(bush_2);
    UnloadTexture(bush_3);

    CloseWindow();        


    return 0;
}