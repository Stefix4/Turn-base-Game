#include <raylib.h>


#include "map.hpp"
#include "game.hpp"
#include "characters.hpp"
#include "Observer.hpp"

const int mapSize=7;
float x_cellSize =screenWidth/mapSize;
float y_cellSize=screenHeight/mapSize;
Observer obstacles;
struct Cell{
    int position_x, position_y;
    bool free;
    Cell(int x,int y,bool f){
        position_x=x;
        position_y=y;
        free=f;
    }
    void show_position(){
        DrawText(TextFormat("%i",position_x),position_x * x_cellSize, position_y * y_cellSize,100,PINK);
    }
    
};
void DrawChessBoard(Texture2D grass) {
    Rectangle image{0, 0, 2000, 2000};
    DrawTexturePro(grass,image,Rectangle{0,0,screenWidth,screenHeight},Vector2{0,0},0.0f,WHITE);
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            Color cellColor = RED;
            DrawRectangleLines(j * x_cellSize, i * y_cellSize, x_cellSize, y_cellSize, cellColor);

            
            Cell cell(i,j,false);
            cell.show_position();
        }
    
    
    }//j * x_cellSize, i * y_cellSize
}
