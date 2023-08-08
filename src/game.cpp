#include <raylib.h>

int main(void)
{
    const int screenWidth = 1281;
    const int screenHeight = 780;

    //initialling the window
    InitWindow(screenWidth,screenHeight, "Turn-base-Game");
    SetTargetFPS(144);
    SetWindowMinSize(screenWidth,screenHeight);

     //game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }


    CloseWindow();        

    return 0;
}