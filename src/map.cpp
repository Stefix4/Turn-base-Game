#include <raylib.h>

#include "map.hpp"
#include "game.hpp"
#include "characters.hpp"

const int mapSize=7;
float x_cellSize =screenWidth/mapSize;
float y_cellSize=screenHeight/mapSize;
struct map{
    int cell_number=0;
    int coord[mapSize][mapSize]={0};

    bool ocuppied=false;


    void events(int j,int i){
        if(cell_number<=mapSize*mapSize)
            cell_number++;
        if(pos_h.x==j+1&&pos_h.y==i+1){
            ocuppied=true;
            coord[j][i]=1;
        }
        else {
            ocuppied=false;
            if(coord[j][i]==1){
            }
            coord[j][i]=0;
        }
    }
};
map cell;
void DrawChessBoard() {
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            Color cellColor = ((i + j) % 2 == 0) ? LIGHTGRAY : DARKGRAY;
            DrawRectangle(j * x_cellSize, i * y_cellSize, x_cellSize, y_cellSize, cellColor);
            
            
            cell.events(j,i);
            
            DrawText(TextFormat("%d",cell.coord[j][i]),j * x_cellSize, i * y_cellSize,50,PINK);
        }
    }//j * x_cellSize, i * y_cellSize
}
