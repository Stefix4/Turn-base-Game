#include <raylib.h>

#include "menu.hpp"
#include "game.hpp"
#include "map.hpp"
#include "characters.hpp"
#include "functions.hpp"

int menuStateSelected = 0;

const float backgroundWidth = 1280;
const float backgroundHeight = 780;

Rectangle image{0, 0, 2000, 2000};
Rectangle StartButton_hb = { backgroundWidth/2-97,backgroundHeight/2+133, 156, 50};

void menus(Texture2D hiro,Texture2D background, Texture2D grass, Texture2D stone_1, Texture2D stone_2, Texture2D bush_1, Texture2D bush_2, Texture2D bush_3){
    if(menuStateSelected == 0){
        DrawTexture(background,0,0,WHITE);
    
        if(CheckCollisionPointRec(GetMousePosition(), StartButton_hb) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            menuStateSelected = 1;
}
    else if(menuStateSelected == 1){
        InitiateBoard(grass, stone_1, stone_2, bush_1, bush_2, bush_3);
        Char(x_cellSize,y_cellSize,hiro);
        ModifyBoard();
        Updateboard();
    }
    else if(menuStateSelected == 2){
        DrawTexturePro(grass,image,Rectangle{0,0,screenWidth,screenHeight},Vector2{0,0},0.0f,WHITE);
    }
    else if(menuStateSelected == 3){
        CloseWindow();
    }
}