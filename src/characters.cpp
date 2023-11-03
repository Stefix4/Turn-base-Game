#include <raylib.h>
#include <functional>
#include <string>
#include <map>

#include "characters.hpp"
#include "map.hpp"
#include "game.hpp"
#include "Observer.hpp"
#include "functions.hpp"

Observer events;

bool turn = true;

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
    
    Vector2 board_position(float x, float y){   
        return Vector2{x , y};
    }

    
};


struct Hero :Character {
    Color team;
    
    Hero(int a, int b, Color color){
        pos_x = a;
        pos_y = b;
        team = color;
    }
    void movement() {
        if(turn){
        if(pos_y > 1)
            if(board[pos_y-2][pos_x-1] == 0)
                if (IsKeyPressed(KEY_W)){
                    pos_y -= 1;
                    fr_x = 35;
                    fr_y = 520;
                    turn = false;
                }
        if(pos_y < mapSize)
            if(board[pos_y][pos_x-1] == 0)
                if(IsKeyPressed(KEY_S)) {
                    pos_y += 1;
                    fr_x = 35;
                    fr_y = 1;
                    turn = false;
                }
        }
        if(turn){
        if(pos_x < mapSize)
            if(board[pos_y-1][pos_x] == 0)
                if(IsKeyPressed(KEY_D)){
                    pos_x += 1;
                    fr_x = 900;
                    fr_y = 520;
                    turn = false;
                }
        if(pos_x > 1)
            if(board[pos_y-1][pos_x-2] == 0)
                if (IsKeyPressed(KEY_A)) {
                    pos_x -= 1;
                    fr_x = 900;
                    fr_y = 1;
                    turn = false;
                }
    }
    }
    
    void create(float x_cellSize, float y_cellSize, Texture2D hiro){
        
        //currentPosition(x_cellSize, y_cellSize, team);
        //DrawText(TextFormat("%f", pos_x),1 ,1 ,50 ,PINK);
        DrawTexture(x_cellSize, y_cellSize, hiro);
        events.add("movement_player", [=](){movement();});
        events.execute("movement_player");
    }
    //texture//
    
    //////////

    //attack//

    /////////

};


struct Monster :Character {
    Color team;

    Monster(int a, int b, Color color){
        pos_x = a;
        pos_y = b;
        team = color;
    }


    void create(float x_cellSize, float y_cellSize, Texture2D hiro){
        currentPosition(x_cellSize, y_cellSize, team);
        DrawTexture(x_cellSize, y_cellSize, hiro);
        // if(IsKeyPressed(KEY_F))
        //     turn = true;
        movement();
        
    }

    void movement(){
        if(!turn){
            if(pos_y < mapSize)
                if(pos_y + 2 == y || pos_y < y){
                    pos_y +=  1;
                    turn = true;
                }
        }
        if(!turn){
            if(pos_x < mapSize)
                if(pos_y == y - 2 || pos_x < x){
                    pos_x +=  1;
                    turn = true;
                }
        }
        if(!turn){
            if(pos_y > 1)
                if(pos_y > y + 1 || pos_x == x){
                    pos_y -=  1;
                    turn = true;
                }
        }
        if(!turn){
            if(pos_x > 1)
                if(pos_x > x){
                    pos_x -=  1;
                    turn = true;
                }
            }
        
    }
    
    //texture//

    //////////

    //attack//

    /////////


};



Hero Hiro(player_position.x, player_position.y, GREEN);
Monster Enemy(4, 4, RED);



void Char(int x_cellSize, int y_cellSize, Texture2D hiro){
    Hiro.create(x_cellSize, y_cellSize, hiro);
    Enemy.create(x_cellSize, y_cellSize, hiro);
}

