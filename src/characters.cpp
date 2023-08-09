#include <raylib.h>

#include "characters.hpp"
#include "map.hpp"
#include "game.hpp"

int x,y;

struct Character
{   
    bool turn;
    int hp;
    int dmg;

    Vector2 getPosition(int x,int y,int x_cellSize,int y_cellSize){
        Vector2 coords;
        coords.x =x_cellSize*(x-1);
        coords.y =y_cellSize*(y-1);     
        return coords;
    }

    void currentPosition(int x,int y,float x_cellSize,float y_cellSize,Color team){
        Vector2 position=getPosition(x,y,x_cellSize,y_cellSize);
        DrawRectangleV(position,Vector2{x_cellSize,y_cellSize},team);
    }
};


struct Hero :Character {
    Color team;

    Hero(int a,int b,Color color){
        turn=true;
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

struct Monster :Character {
    Color team= RED;

    Monster(){
        turn=false;
    } 


    void create(int x,int y,float x_cellSize,float y_cellSize){
        currentPosition( x, y, x_cellSize, y_cellSize,team);
    }
    //texture//

    //////////

    //attack//

    /////////


};


Hero Hiro(4,4,BLUE);
Monster enemy;

void Char(int x_cellSize,int y_cellSize){
Hiro.create(4,4,x_cellSize,y_cellSize);
}