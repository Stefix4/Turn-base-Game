#include <raylib.h>

#include "characters.hpp"
#include "map.hpp"
#include "game.hpp"
#include "movement.hpp"

struct Character
{   
    bool turn;
    int hp;
    int dmg;
    float fr_x=35,fr_y=1;

    Vector2 getPosition(int x,int y,int x_cellSize,int y_cellSize){
        Vector2 coords;
        coords.x =x_cellSize*(x-1);
        coords.y =y_cellSize*(y-1);     
        return coords;
    }

    void currentPosition(int x,int y,float x_cellSize,float y_cellSize,Color team){
        DrawRectangleRec(getSource(x,y,x_cellSize,y_cellSize),team);
    }
    Rectangle getSource(int x,int y,float x_cellSize,float y_cellSize){
        Vector2 position=getPosition(x,y,x_cellSize,y_cellSize);
        return Rectangle{position.x,position.y,x_cellSize,y_cellSize};
    }
};


struct Hero :Character {
    Color team;

    Hero(int a,int b,Color color){
        turn=true;
        team=color;
    } 

    void create(int x,int y,float x_cellSize,float y_cellSize, Texture2D hiro){
        Rectangle image{fr_x,fr_y,480, 540};
        currentPosition( x, y, x_cellSize, y_cellSize,team);
        DrawTexturePro(hiro,image,getSource(x,y,x_cellSize,y_cellSize),Vector2{0, 0},0.0f,WHITE);
        if(IsKeyPressed(KEY_W)){
            fr_x = 35;
            fr_y = 540;
        }
        if(IsKeyPressed(KEY_S)){
            fr_x = 35;
            fr_y = 1;
        }

        if(IsKeyPressed(KEY_D)){
            fr_x = 925;
            fr_y = 540;
        }

        if(IsKeyPressed(KEY_A)){
            fr_x = 925;
            fr_y = 1;
        }
    }
    //texture//
    
    //////////

    //attack//

    /////////

};

struct Monster :Character {
    Color team;

    Monster(int a,int b,Color color){
        turn=false;
        team=color;
    } 


    void create(int x,int y,float x_cellSize,float y_cellSize){
        currentPosition( x, y, x_cellSize, y_cellSize,team);
    }
    //texture//

    //////////

    //attack//

    /////////


};


Hero Hiro(4,4,GREEN);
Monster Enemy(5,4,RED);
void Char(int x,int y,int x_cellSize,int y_cellSize,Texture2D hiro){
Hiro.create(x,y,x_cellSize,y_cellSize,hiro);
Enemy.create(5,4,x_cellSize,y_cellSize);
}
