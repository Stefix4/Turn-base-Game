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
        hp = 10;
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

    Monster(int a, int b, Color color){
        dmg = GetRandomValue(1, 5);
        pos_x = a;
        pos_y = b;
        team = color;
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
Monster Enemy(monster_position.x, monster_position.y, RED);

// a = x; b = y
void Update_Health(){
    if(turn <= 0)
        if((b + 1 == y && a == x) || (b - 1 == y && a == x) || (b == y && a + 1 == x) || (b == y && a - 1 == x)){
            Hiro.hp -= Enemy.dmg;
            turn = 2;
        }
    if(Health.count == 0)
        Health.hp_points = 0;
    if(IsKeyPressed(KEY_Q)){
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

void Char(int x_cellSize, int y_cellSize, Texture2D hiro){
    Hiro.create(x_cellSize, y_cellSize, hiro);
    Enemy.create(x_cellSize, y_cellSize, hiro);
    Update_Health();
}
