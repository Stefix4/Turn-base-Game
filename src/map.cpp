#include <raylib.h>


#include "map.hpp"
#include "game.hpp"
#include "characters.hpp"
#include "Observer.hpp"
#include "check.hpp"

const int mapSize=7;

float x_cellSize =screenWidth/mapSize;

float y_cellSize=screenHeight/mapSize;

Vector2 player_position={5,4};


int board[7][7]={{0,0,0,0,0,0,0},
                 {1,1,1,1,1,1,1},
                 {0,0,1,0,0,0,0},
                 {0,0,1,0,0,0,0},
                 {0,0,1,0,0,0,0},
                 {0,0,1,0,0,0,0},
                 {0,0,1,0,0,0,0}
                };

struct Cell{

    int position_x, position_y;

    bool free;

    Cell(int x,int y,bool f=true){
        position_x=x;
        position_y=y;
        free=f;
    }
    void show_position(){
        DrawText(TextFormat("%i",position_x),position_x * x_cellSize, position_y * y_cellSize,50,PINK);
        DrawText(TextFormat(":%i",position_y),position_x * x_cellSize+30, position_y * y_cellSize,50,PINK);
    }

    void ocupied(int x,int y){
        if(position_x+1==x && position_y+1==y)
            free=false;
    }

    void unocupied(int x,int y){
        if(position_x+1==x && position_y+1==y)
            free=true;
    }

    bool check_free(int x,int y){
        if(x==position_x&&y==position_y)
            return free;
        return false;
    }
};

void movement() {
        if(player_position.y > 1)
            if (IsKeyPressed(KEY_W)){
                player_position.y -= 1;
            }
        if(player_position.y < mapSize)
            if(IsKeyPressed(KEY_S)) {
                player_position.y += 1;
            }
        if(player_position.x < mapSize)
            if(IsKeyPressed(KEY_D)){
                player_position.x += 1;
            }
        if(player_position.x > 1)
            if (IsKeyPressed(KEY_A)) {
                player_position.x -= 1;
            }
}


void DrawChessBoard(Texture2D grass) {
    Rectangle image{0, 0, 2000, 2000};
    DrawTexturePro(grass,image,Rectangle{0,0,screenWidth,screenHeight},Vector2{0,0},0.0f,WHITE);
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            Color cellColor = RED;
            DrawRectangleLines(j * x_cellSize, i * y_cellSize, x_cellSize, y_cellSize, cellColor);

            Cell cell(i,j);

            if(board[j][i]==1)
                cell.free=false;
            else if(board[j][i]==0)
                cell.free=true;

            if(player_position.x==i+1&&player_position.y==j+1)
                cell.free=false;
            

            cell.ocupied(1,1);
            cell.unocupied(1,2);


            if(cell.free)
                cell.show_position();

        }
    
    
    }
    
    movement();
}