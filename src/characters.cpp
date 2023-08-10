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

    void create(int x,int y,float x_cellSize,float y_cellSize){
        currentPosition( x, y, x_cellSize, y_cellSize,team);
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
Monster enemy(4,4,RED);
Rectangle source =Hiro.getSource(x,y,x_cellSize,y_cellSize);
void Char(int x,int y,int x_cellSize,int y_cellSize){
Hiro.create(x,y,x_cellSize,y_cellSize);
}
