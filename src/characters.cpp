#include <raylib.h>
#include <functional>
#include <string>
#include <map>
#include <thread>
#include <iostream>

#include "characters.hpp"
#include "map.hpp"
#include "game.hpp"
#include "Observer.hpp"
#include "functions.hpp"
#include "menu.hpp"

Observer events;

int turn = 1;
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
        if(x>pos_x){
            pos_x += 1;
            fr_x = 900;
            fr_y = 520;
        }
        if(x<pos_x){
            pos_x -= 1;
            fr_x = 900;
            fr_y = 1;
        }
        if(y>pos_y){
            pos_y += 1;
            fr_x = 35;
            fr_y = 1;
        }
        if(y<pos_y){
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

Potion Health(2, 2);
Hero Hiro(player_position.x, player_position.y, GREEN);
Monster* Enemy = new Monster(monster_position.x, monster_position.y, RED);

// a = x; b = y
void movement_monster(){
    if(turn <= 0){
        if(b < mapSize && board[b][a-1] == 0)
            if(b + 1 < y){
                b +=  1;
                turn++;
            }
    }
    if(turn <= 0){
        if(a < mapSize && board[b-1][a] == 0)
            if(a + 1 < x){
                a +=  1;
                turn++;
            }
    }
    if(turn <= 0){
        if(b > 1 && board[b-2][a-1] == 0)
            if(b > y + 1){
                b -=  1;
                turn++;
        }
    }
    if(turn <= 0){
        if(a > 1 && board[b-1][a-2] == 0)
            if(a > x + 1){
                a -=  1;
                turn++;
            }
    }
    if(turn <= 0){
        if(((board[b-1][a] == 1 && b < y ) || (board[b-1][a-2] == 1 && b < y)) && board[b][a-1] == 0){
            b +=  1;
            turn ++;
        }
    }
    if(turn <= 0){
        if(((board[b-2][a-1] == 1 && a < x) || (board[b][a-1] == 1 && a < x)) && board[b-1][a] == 0){
            a +=  1;
            turn ++;
    }
    }
    if(turn <= 0){
        if(((board[b-1][a-2] == 1 && b > y) || (board[b-1][a] == 1 && b > y)) && board[b-2][a-1] == 0){
            b -=  1;
            turn++;
        }
    }
    if(turn <= 0){
        if(((board[b][a-1] == 1 && a > x) || (board[b-2][a-1] == 1 && a > x )) && board[b-1][a-2] == 0){
            a -=  1;
            turn ++;
    }
    }
}
void movement_hiro() {
    if(turn > 0){
        if(y > 1)
            if(board[y-2][x-1] == 0)
                if (IsKeyPressed(KEY_W)){
                    y -= 1;
                    turn--;
                }
        if(y < mapSize)
            if(board[y][x-1] == 0)
                if(IsKeyPressed(KEY_S)) {
                    y += 1;
                    turn--;
                }
}
    if(turn > 0){
        if(x < mapSize)
            if(board[y-1][x] == 0)
                if(IsKeyPressed(KEY_D)){
                    x += 1;
                    turn--;
                }
    if(x > 1)
        if(board[y-1][x-2] == 0)
            if (IsKeyPressed(KEY_A)) {
                x -= 1;
                turn--;
            }
    }
    if(!isAlive){
        turn--;
    }
}
void Up_Health_Hiro(){
    if(turn <= 0 && isAlive)
        if((b + 1 == y && a == x) || (b - 1 == y && a == x) || (b == y && a + 1 == x) || (b == y && a - 1 == x)){
            Hiro.hp -= Enemy->dmg;
            turn += 2;
        }
    if(IsKeyPressed(KEY_Q) && Health.count != 0){
        Hiro.hp += Health.hp_points;
        Health.count -= 1;
    }
    if(Hiro.hp > 10)
        Hiro.hp = 10;
    if(Hiro.hp <= 0){
        Hiro.hp = 0;
        menuStateSelected = 2;
    }
    DrawText(TextFormat("Health: %d", Hiro.hp), 10, 10, 35, WHITE);
    }
void Up_Health_Enemy(){
   if(turn > 0){
       if ((y + 1 == b && x == a) || (y - 1 == b && x == a) || ((y == b && x + 1 == a) || (y == b && x - 1 == a))) 
            if(IsKeyPressed(KEY_F)){
                Enemy->hp -= Hiro.dmg;
                turn--;
            }
   }
    if(Enemy->hp <= 0){
        Enemy->hp = 0;
        isAlive = false;
        }
    DrawText(TextFormat("Health: %d", Enemy->hp), 10, 40, 35, WHITE);
}

void Char(int x_cellSize, int y_cellSize, Texture2D hiro){
    Hiro.create(x_cellSize, y_cellSize, hiro);
    movement_hiro();
    Up_Health_Hiro();
    
    if (isAlive){
        Enemy->create(x_cellSize, y_cellSize, hiro);
        movement_monster();
        Up_Health_Enemy();
    }
    else{
        board[b][a] = 0;
        turn = 1;
}
}
