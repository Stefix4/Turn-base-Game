#include <raylib.h>
#include <cstdlib>

#include "map"
#include "utility"

#include "map.hpp"
#include "game.hpp"
#include "characters.hpp"
#include "Observer.hpp"

const int mapSize=7;

float x_cellSize =screenWidth/mapSize;

float y_cellSize=screenHeight/mapSize;

Vector2 player_position={5,4};


int x=5,y=4;

//                     0 ,1 ,2 ,3 ,4 ,5 ,6
int board[7][7]={/*0*/{0 ,0 ,1 ,0 ,0 ,0 ,0},
                 /*1*/{0 ,0 ,1 ,0 ,0 ,0 ,0},
                 /*2*/{0 ,0 ,1 ,0 ,0 ,0 ,0},
                 /*3*/{0 ,0 ,1 ,0 ,0 ,0 ,0},
                 /*4*/{0 ,0 ,1 ,0 ,0 ,0 ,0},
                 /*5*/{0 ,0 ,1 ,0 ,0 ,0 ,0},
                 /*6*/{0 ,0 ,1 ,0 ,0 ,0 ,0}
                };

struct Cell{
    
    
    int position_x, position_y;

    bool free,character=false;

    bool has_texture=false;

    Cell(int y=0,int x=0,bool f=true,bool h=false):position_x(x),position_y(y),free(f),has_texture(h){}

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
    void give_texture(int j, int i, Texture2D stone_1, Texture2D stone_2, Texture2D stone_3, Texture2D bush_1, Texture2D bush_2, Texture2D bush_3, Texture2D bush_4) {
        if (has_texture) {
            return;
        }
        int text_select = rand() % 7 + 1;
        if (text_select == 1) {
            DrawTexturePro(stone_1, Rectangle{0, 200, 555, 379}, Rectangle{j * x_cellSize, i * y_cellSize, j + 1 * x_cellSize, i + 1 * y_cellSize}, Vector2{0, 0}, 0.0f, WHITE);
        } else if (text_select == 2) {
            DrawTexturePro(stone_2, Rectangle{0, 200, 555, 379}, Rectangle{j * x_cellSize, i * y_cellSize, j + 1 * x_cellSize, i + 1 * y_cellSize}, Vector2{0, 0}, 0.0f, WHITE);
        } else if (text_select == 3) {
            DrawTexturePro(stone_3, Rectangle{0, 200, 555, 379}, Rectangle{j * x_cellSize, i * y_cellSize, j + 1 * x_cellSize, i + 1 * y_cellSize}, Vector2{0, 0}, 0.0f, WHITE);
        } else if (text_select == 4) {
            DrawTexturePro(bush_1, Rectangle{0, 200, 555, 379}, Rectangle{j * x_cellSize, i * y_cellSize, j + 1 * x_cellSize, i + 1 * y_cellSize}, Vector2{0, 0}, 0.0f, WHITE);
        } else if (text_select == 5) {
            DrawTexturePro(bush_2, Rectangle{0, 200, 555, 379}, Rectangle{j * x_cellSize, i * y_cellSize, j + 1 * x_cellSize, i + 1 * y_cellSize}, Vector2{0, 0}, 0.0f, WHITE);
        } else if (text_select == 6) {
            DrawTexturePro(bush_3, Rectangle{0, 200, 555, 379}, Rectangle{j * x_cellSize, i * y_cellSize, j + 1 * x_cellSize, i + 1 * y_cellSize}, Vector2{0, 0}, 0.0f, WHITE);
        } else if (text_select == 7) {
            DrawTexturePro(bush_4, Rectangle{0, 200, 555, 379}, Rectangle{j * x_cellSize, i * y_cellSize, j + 1 * x_cellSize, i + 1 * y_cellSize}, Vector2{0, 0}, 0.0f, WHITE);
        }
        has_texture = true;
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

std::map<std::pair<int,int>, Cell> Cell_Instance;

void InitiateBoard(Texture2D grass,Texture2D stone_1,Texture2D stone_2,Texture2D stone_3,Texture2D bush_1,Texture2D bush_2,Texture2D bush_3,Texture2D bush_4) {
    Rectangle image{0, 0, 2000, 2000};
    DrawTexturePro(grass,image,Rectangle{0,0,screenWidth,screenHeight},Vector2{0,0},0.0f,WHITE);
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            Color cellColor = RED;
            DrawRectangleLines(j * x_cellSize, i * y_cellSize, x_cellSize, y_cellSize, cellColor);


            Cell_Instance[{i,j}]=Cell(i, j, true,false);

            if(board[i][j]==1){
                Cell_Instance[{i,j}].free=false;
            }
            else if(board[i][j]==0)
                Cell_Instance[{i,j}].free=true;
            
            if(x==j+1&&y==i+1){
                Cell_Instance[{i,j}].free=false;
                Cell_Instance[{i,j}].character=true;
            }

            
            if(Cell_Instance[{i,j}].free==false && Cell_Instance[{i,j}].has_texture==false && Cell_Instance[{i,j}].character==false){
                Cell_Instance[{i,j}].give_texture(j,i,stone_1,stone_2,stone_3,bush_1,bush_2,bush_3,bush_4);
            }
        }
    
    
    }
    movement();
}
void ModifyBoard(){
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {

            if(Cell_Instance[{i,j}].free){
                Cell_Instance[{i,j}].show_position();
            }


        }
    }
}