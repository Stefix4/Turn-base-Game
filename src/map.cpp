#include <raylib.h>

#include "map.hpp"
#include "game.hpp"
#include "characters.hpp"
#include "Observer.hpp"

const int mapSize=7;

float x_cellSize =screenWidth/mapSize;

float y_cellSize=screenHeight/mapSize;

Vector2 player_position={5,4};
int x=5,y=4;

//                     0,1,2,3,4,5,6
int board[7][7]={/*0*/{0,0,0,0,1,0,0},
                 /*1*/{0,0,0,0,1,1,0},
                 /*2*/{0,0,1,0,0,0,0},
                 /*3*/{0,0,0,1,0,0,0},
                 /*4*/{0,0,0,1,0,0,0},
                 /*5*/{0,0,0,0,0,0,0},
                 /*6*/{0,0,0,0,0,1,0}
                };

struct Board{

    int position_x, position_y;

    bool free;

    Board(int y,int x,bool f=true){
        position_x=x;
        position_y=y;
        free=f;
    }
    void show_position(){
        DrawText(TextFormat("%i",position_x),position_x * x_cellSize, position_y * y_cellSize,50,PINK);
        DrawText(TextFormat(":%i",position_y),position_x * x_cellSize+30, position_y * y_cellSize,50,PINK);
    }

    void ocupied(int x,int y){
        if(position_x==x && position_y==y)
            board[y][x]=1;
    }

    void unocupied(int x,int y){
        if(position_x==x && position_y==y)
            board[y][x]=0;
    }

    bool check_free(int x,int y){
        if(x==position_x&&y==position_y)
            return free;
        return false;
    }
    void rand_ocupied(int n){
    int a,b;
    while(n){
        a=GetRandomValue(0,6);
        b=GetRandomValue(0,6);
        if(board[a][b]==0)
            ocupied(a,b);
        n--;
    }
}

};

void movement() {
        if(y > 1)
            if(board[y-2][x-1]==0)
                if (IsKeyPressed(KEY_W)){
                    y -= 1;
                }
        if(y < mapSize)
            if(board[y][x-1]==0)
            if(IsKeyPressed(KEY_S)) {
                y += 1;
            }
        if(x < mapSize)
            if(board[y-1][x]==0)
            if(IsKeyPressed(KEY_D)){
                x += 1;
            }
        if(x > 1)
            if(board[y-1][x-2]==0)
            if (IsKeyPressed(KEY_A)) {
                x -= 1;
            }
}


void DrawChessBoard(Texture2D grass) {
    Rectangle image{0, 0, 2000, 2000};
    DrawTexturePro(grass,image,Rectangle{0,0,screenWidth,screenHeight},Vector2{0,0},0.0f,WHITE);
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            Color cellColor = RED;
            DrawRectangleLines(j * x_cellSize, i * y_cellSize, x_cellSize, y_cellSize, cellColor);

            Board cell(i,j);


            if(board[i][j]==1)
                cell.free=false;
            else if(board[i][j]==0)
                cell.free=true;
            if(x==j+1&&y==i+1)
                cell.free=false;



            if(cell.free)
                cell.show_position();

        }
    
    
    }
    
    movement();
}