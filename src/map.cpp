#include <raylib.h>
#include <cstdlib>
#include <time.h> 

#include "map"
#include "utility"

#include "map.hpp"
#include "game.hpp"
#include "characters.hpp"
#include "Observer.hpp"
#include "functions.hpp"

const int mapSize = 7;

int seed = 1000;

float x_cellSize =screenWidth / mapSize;

float y_cellSize = screenHeight / mapSize;

Vector2 player_position = {2, 4};

Vector2 monster_position = {2, 2};


int x = 2, y = 4, a = 2, b = 2;

//                     0 ,1 ,2 ,3 ,4 ,5 ,6
int board[7][7]={/*0*/{0 ,0 ,0 ,0 ,0 ,0 ,0},
                 /*1*/{0 ,0 ,0 ,0 ,0 ,0 ,0},
                 /*2*/{0 ,0 ,1 ,0 ,0 ,0 ,0},
                 /*3*/{0 ,0 ,0 ,0 ,0 ,0 ,0},
                 /*4*/{0 ,0 ,0 ,0 ,0 ,0 ,0},
                 /*5*/{0 ,0 ,0 ,0 ,0 ,0 ,0},
                 /*6*/{0 ,0 ,0 ,0 ,0 ,0 ,0}
                };

struct Cell{

    int position_x, position_y;

    bool free , character = false;

    bool has_texture = false;

    Cell(int y = 0, int x = 0, bool f = true, bool h = false):position_x(x), position_y(y), free(f), has_texture(h){}

    void show_position(){
        DrawText(TextFormat("%i",position_x + 1),position_x * x_cellSize, position_y * y_cellSize, 50 ,PINK);
        DrawText(TextFormat(":%i",position_y + 1),position_x * x_cellSize + 30, position_y * y_cellSize, 50 ,PINK);
    }

    void ocupied(int x, int y){
        if(position_x == x && position_y == y)
            board[y][x] = 1;
    }

    void unocupied(int x, int y){
        if(position_x == x && position_y == y)
            board[y][x] = 0;
    }

    bool check_free(int x, int y){
        if(x == position_x && y == position_y)
            return free;
        return false;
    }

    void give_texture(Texture2D stone_1, Texture2D stone_2, Texture2D bush_1, Texture2D bush_2, Texture2D bush_3) {
        Rectangle position {position_x * x_cellSize, position_y * y_cellSize, position_x + 1 * x_cellSize, position_y + 1 * y_cellSize};
        if (has_texture) {
            return;
        }
        int text_select = rand() % 6 + 1;
        if (text_select == 1) {
            DrawTexturePro(stone_1, Rectangle{0, 200, 555, 379},position, Vector2{0, 0}, 0.0f, WHITE);
        } else if (text_select == 2) {
            DrawTexturePro(stone_2, Rectangle{0, 200, 555, 379},position, Vector2{0, 0}, 0.0f, WHITE);
        } else if (text_select == 3) {
            DrawTexturePro(bush_1, Rectangle{0, 200, 555, 379},position, Vector2{0, 0}, 0.0f, WHITE);
        } else if (text_select == 4) {
            DrawTexturePro(bush_1, Rectangle{0, 200, 555, 379},position, Vector2{0, 0}, 0.0f, WHITE);
        } else if (text_select == 5) {
            DrawTexturePro(bush_2, Rectangle{0, 200, 555, 379},position, Vector2{0, 0}, 0.0f, WHITE);
        } else if (text_select == 6) {
            DrawTexturePro(bush_3, Rectangle{0, 200, 555, 379},position, Vector2{0, 0}, 0.0f, WHITE);
        }
        has_texture = true;
    }
    
};

std::map<std::pair<int,int>, Cell> cell_Instance;

void randomize_board(int seed,int n,Texture2D stone_1, Texture2D stone_2, Texture2D bush_1, Texture2D bush_2, Texture2D bush_3){
    srand(1);
    if(n>0){
        cell_Instance[{rand()%7+0,rand()%7+0}].give_texture(stone_1, stone_2, bush_1, bush_2, bush_3);
        cell_Instance[{rand()%7+0,rand()%7+0}].free=false;
        n--;
    }
}

void InitiateBoard(Texture2D grass, Texture2D stone_1, Texture2D stone_2, Texture2D bush_1, Texture2D bush_2, Texture2D bush_3) {
    Rectangle image{0, 0, 2000, 2000};
    DrawTexturePro(grass,image,Rectangle{0,0,screenWidth,screenHeight},Vector2{0,0},0.0f,WHITE);
    seed = 1000;
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            Color cellColor = RED;
            DrawRectangleLines(j * x_cellSize, i * y_cellSize, x_cellSize, y_cellSize, cellColor);

            srand(seed); 
            cell_Instance[{i,j}] = Cell(i, j, true, false);

            if(board[i][j] == 1){
                cell_Instance[{i,j}].free=false;
            }
            else if(board[i][j] == 0){
                cell_Instance[{i,j}].free=true;
                cell_Instance[{i,j}].character = false;
            }
            
            if(x == j + 1 && y == i + 1){
                cell_Instance[{i,j}].free = false;
                cell_Instance[{i,j}].character = true;
            }
            if((a == j + 1 && b == i + 1) && isAlive){
                cell_Instance[{i,j}].free = false;
                cell_Instance[{i,j}].character = true;
            }
            
            if(cell_Instance[{i,j}].free == false && cell_Instance[{i,j}].has_texture == false && cell_Instance[{i,j}].character == false){
                cell_Instance[{i,j}].give_texture(stone_1, stone_2, bush_1, bush_2, bush_3);
            }
            seed++;
        }
    
    }
    
}


void ModifyBoard(){
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            if(turn)
                if(cell_Instance[{i,j}].free){
                    cell_Instance[{i,j}].show_position();
                }
        }
    }
}
void Updateboard(){
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            if(board[i][j] == 1){
                cell_Instance[{i,j}].free=false;
            }
            else if(board[i][j] == 0){
                cell_Instance[{i,j}].free=true;
                cell_Instance[{i,j}].character = false;
            }
            
            if(x == j + 1 && y == i + 1){
                cell_Instance[{i,j}].free = false;
                cell_Instance[{i,j}].character = true;
            }
            if(a == j + 1 && b == i + 1){
                cell_Instance[{i,j}].free = false;
                cell_Instance[{i,j}].character = true;
            }

        }
    }
}