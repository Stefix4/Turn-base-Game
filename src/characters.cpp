#include <raylib.h>

#include "characters.hpp"
#include "map.hpp"
#include "game.hpp"
#include "movement.hpp"

struct Character
{ 
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


struct Hero :Character{
    bool turn=true;
    Color team =GREEN;
    
    void create(int x,int y,float x_cellSize,float y_cellSize){
        currentPosition( x, y, x_cellSize, y_cellSize,team);
    }
    //texture//

    //////////

    //attack//

    /////////

};

struct Monster :Character{
    bool turn=false;
    Color team= RED;

    void create(int x,int y,float x_cellSize,float y_cellSize){
        currentPosition( x, y, x_cellSize, y_cellSize,team);
    }
    //texture//

    //////////

    //attack//

    /////////


};


Hero Hiro;
Monster enemy;

void Char(int x,int y,int x_cellSize,int y_cellSize){
Hiro.create(x,y,x_cellSize,y_cellSize);
}
