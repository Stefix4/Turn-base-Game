#include <raylib.h>
#include <functional>
#include <string>
#include <map>
#include <thread>
#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <cmath>

#include "characters.hpp"
#include "map.hpp"
#include "game.hpp"
#include "Observer.hpp"
#include "functions.hpp"
#include "menu.hpp"

std::ofstream monster_map_log("logs/monster_map.log");

int A[7][7] = {};

const int di[]={-1, 0, 1, 0},
          dj[]={ 0, 1, 0,-1};

Observer events;

int turn = 1;
int update_turn = -1;
bool isAlive = true;

struct Potion
{
    int hp_points, count;
    Potion(int a, int b){
        hp_points = a;
        count = b;
    }
};
struct Character:Observer
{  
    int pos_x,pos_y;
    int hp;
    int dmg;
    float fr_x=35,fr_y=1;
    
    void currentPosition(float x_cellSize, float y_cellSize, Color team){
        DrawRectangleV(getPosition(pos_x, pos_y, x_cellSize, y_cellSize),Vector2{x_cellSize, y_cellSize}, team);
     }
    void DrawTexture(float x_cellsize, float y_cellsize, Texture2D texture){
        Rectangle image{fr_x, fr_y, 480, 540};
        DrawTexturePro(texture, image, getSource(x_cellSize,y_cellSize), Vector2{0, 0}, 0.0f, WHITE);
    }
    
    Rectangle getSource(float x_cellSize, float y_cellSize){
        Vector2 position={x_cellSize*(pos_x-1), y_cellSize*(pos_y-2)};
        return Rectangle{position.x,position.y, x_cellSize,y_cellSize*2};
    }

    Vector2 getPosition(int x, int y, int x_cellSize, int y_cellSize){
        Vector2 coords;
        coords.x =x_cellSize*(pos_x-1);
        coords.y =y_cellSize*(pos_y-1);     
        return coords;
    }
    
};

struct Hero :Character {
    Color team;
    
    Hero(int a, int b, Color color){
        hp = 20;  
        dmg = 1;
        pos_x = a;
        pos_y = b;
        team = color;
    }

    void Update_Texture(){
        if(x > pos_x){
            pos_x += 1;
            fr_x = 900;
            fr_y = 520;
        }
        if(x < pos_x){
            pos_x -= 1;
            fr_x = 900;
            fr_y = 1;
        }
        if(y > pos_y){
            pos_y += 1;
            fr_x = 35;
            fr_y = 1;
        }
        if(y < pos_y){
            pos_y -= 1;
            fr_x = 35;
            fr_y = 520;
        }

    }
    
    void create(float x_cellSize, float y_cellSize, Texture2D hiro){
        DrawTexture(x_cellSize, y_cellSize, hiro);
        Update_Texture();
    }
    //attack//

    /////////

};

struct Monster :Character {
    Color team;
    bool isAlive;

    Monster(int a, int b, Color color){
        hp = 3;
        dmg = 2;
        pos_x = a;
        pos_y = b;
        team = color;
        isAlive = true;
    }

    void Update_Texture(){
        if(a > pos_x){
            pos_x += 1;
        }
        if(a < pos_x){
            pos_x -= 1;
        }
        if(b > pos_y){
            pos_y += 1;
        }
        if(b < pos_y){
            pos_y -= 1;
        }

    }

    void create(float x_cellSize, float y_cellSize, Texture2D hiro){
            currentPosition(x_cellSize, y_cellSize, team);
            DrawTexture(x_cellSize, y_cellSize, hiro);
            Update_Texture();
    }
    //texture//

    //////////

    //attack//

    /////////

};

void null_elements(){
     for (int i = 0; i < mapSize; i++){
        for (int j = 0; j < mapSize; j++) {
            if(board[i][j] == 0)
                map_log << board[i][j] << " ";
            else
                map_log << " ";
        }
        map_log << std::endl;
    }
}

Potion Health(2, 2);
Hero Hiro(player_position.x, player_position.y, GREEN);
Monster* Enemy = new Monster(monster_position.x, monster_position.y, RED);

bool monster_is_adjacent()
{
    return (abs(a - x) + abs(b - y)) == 1;
}

void give_turn_to_monster(){
    turn--;
    update_turn++;
    Updateboard();
}

void give_turn_to_hiro(){
    turn++;
    update_turn++;
    Updateboard();
}

void Update_monster_map(){
    for(int i = 0; i < mapSize; i++)
        for(int j = 0; j < mapSize; j++)
            if(board[i][j] == 1)
                A[i][j] = -1;
            else if(board[i][j] == -1)
                A[i][j] = -1;
            else
                A[i][j] = 0;
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            monster_map_log << std::setw(3) << A[i][j];
        }
        monster_map_log << std:: endl;
    }
    monster_map_log << std:: endl;
}

void lee_from_hero(int hy, int hx){
    Update_monster_map();

    std::queue<std::pair<int,int>> Q;

    int sy = hy - 1;
    int sx = hx - 1;

    Q.push({sy, sx});
    A[sy][sx] = 1;

    while (!Q.empty()) {
        auto [i, j] = Q.front();
        Q.pop();

        for (int k = 0; k < 4; k++) {
            int iv = i + di[k];
            int jv = j + dj[k];

            if (iv >= 0 && iv < mapSize &&
                jv >= 0 && jv < mapSize &&
                A[iv][jv] == 0 &&
                board[iv][jv] == 0 &&
                !(iv == sy && jv == sx))
            {
                A[iv][jv] = A[i][j] + 1;
                Q.push({iv, jv});
            }
        }
    }
}


void move_monster_one_step()
{
    int mi = b - 1;
    int mj = a - 1;

    int best = 9999;
    int ni = mi, nj = mj;

    for (int k = 0; k < 4; k++) {
        int iv = mi + di[k];
        int jv = mj + dj[k];

        if (iv >= 0 && iv < mapSize &&jv >= 0 && jv < mapSize && A[iv][jv] > 0 && A[iv][jv] < best){
            best = A[iv][jv];
            ni = iv;
            nj = jv;
        }
    }

    board[mi][mj] = 0;
    b = ni + 1;
    a = nj + 1;
    board[ni][nj] = 2;

    give_turn_to_hiro();
}
void Up_Health_Enemy(){
    // hero turn only
    if (turn > 0){
    // must be adjacent AND press F
    if (monster_is_adjacent() && IsKeyPressed(KEY_F)){
        Enemy->hp -= Hiro.dmg;
        give_turn_to_monster();
    }
    }
    // death handling
    if (Enemy->hp <= 0){
        Enemy->hp = 0;
        Enemy->isAlive = false;
        TraceLog(LOG_TRACE, "Monster is dead!");
        board[b-1][a-1] = 0;  // clear monster tile
        a = 0;
        b = 0;
        UpdateMapLog();
        Updateboard();
    }
}

void Up_Health_Hiro(){
    if(Enemy->isAlive)
        Up_Health_Enemy();
    if (IsKeyPressed(KEY_Q) && Health.count != 0 && Hiro.hp + Health.hp_points <= 10) {
        Hiro.hp += Health.hp_points;
        Health.count--;
    }
    if (Hiro.hp > 10)
        Hiro.hp = 10;
        
    if (Hiro.hp <= 0){
        Hiro.hp = 0;
        isAlive = false;
        menuStateSelected = 1;
    }
}

void movement_hiro() {
    if(turn > 0){
        if(y > 1)
            if(board[y-2][x-1] == 0)
                if (IsKeyPressed(KEY_W)){
                    y -= 1;
                    board[y][x-1] = 0;
                    give_turn_to_monster();
                }
        if(y < mapSize)
            if(board[y][x-1] == 0)
                if(IsKeyPressed(KEY_S)) {
                    y += 1;
                    board[y-2][x-1] = 0;
                    give_turn_to_monster();
                }
}
    if(turn > 0){
        if(x < mapSize)
            if(board[y-1][x] == 0)
                if(IsKeyPressed(KEY_D)){
                    x += 1;
                    board[y-1][x-2] = 0;
                    give_turn_to_monster();
                }
    if(x > 1)
        if(board[y-1][x-2] == 0)
            if (IsKeyPressed(KEY_A)) {
                x -= 1;
                board[y-1][x] = 0;
                give_turn_to_monster();
            }
    }
    if(!Enemy->isAlive)
        turn = 1;
}

void monster_turn()
{
    if (turn <= 0 && Enemy->isAlive){
        if (monster_is_adjacent()) {
            Hiro.hp -= Enemy->dmg;
            give_turn_to_hiro();
        }
        else {
            lee_from_hero(y, x);
            move_monster_one_step();
        }
    }
}

void movement(){
    if (isAlive)
        movement_hiro();
    if (Enemy->isAlive){
        monster_turn();
        if (update_turn >= 2) {
            update_turn = 0;
            UpdateMapLog();
        }
    }
    else
        if (update_turn >= 1) {
            update_turn = 0;
            UpdateMapLog();
        }
}


void Char(int x_cellSize, int y_cellSize, Texture2D hiro){
    if(update_turn == -1){
        UpdateMapLog();
        update_turn = 0;
    }
    if(isAlive){
        Hiro.create(x_cellSize, y_cellSize, hiro);
        DrawText(TextFormat("Hiro: %d", Hiro.hp), 10, 10, 35, WHITE);
        Up_Health_Hiro();
    }
    if(Enemy->isAlive){
        Enemy->create(x_cellSize, y_cellSize, hiro);
        DrawText(TextFormat("Monster: %d", Enemy->hp), 10, 40, 35, WHITE);
    }
    else
        turn = 1;
    movement();
}