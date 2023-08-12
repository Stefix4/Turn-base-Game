#include <raylib.h>

#include "characters.hpp"
#include "map.hpp"
#include "game.hpp"
#include "movement.hpp"

int x,y;
struct Character
{   
    int pos_x=x,pos_y=y;
    bool turn;
    int hp;
    int dmg;
    float fr_x=35,fr_y=1;


    Vector2 getPosition(int x,int y ,int x_cellSize,int y_cellSize){
        Vector2 coords;
        coords.x =x_cellSize*(x-1);
        coords.y =y_cellSize*(y-1);     
        return coords;
    }

    void currentPosition(float x_cellSize,float y_cellSize,Color team){
        DrawRectangleV(getPosition(pos_x,pos_y,x_cellSize,y_cellSize),Vector2{x_cellSize,y_cellSize},team);
    }

    Rectangle getSource(float x_cellSize,float y_cellSize){
        Vector2 position=getPosition(x,y-1,x_cellSize,y_cellSize);
        return Rectangle{position.x,position.y,x_cellSize,y_cellSize*2};
    }
};


struct Hero :Character {
    Color team;

    Hero(int a,int b,Color color){
        pos_x=a;
        pos_y=b;
        x=a;
        y=b;
        turn=true;
        team=color;
    } 

    void create(float x_cellSize,float y_cellSize, Texture2D hiro){
        currentPosition( x_cellSize, y_cellSize,team);
        DrawText(TextFormat("%d",pos_x),1,1,50,PINK);
        Rectangle image{fr_x,fr_y,480, 540};
        DrawTexturePro(hiro,image,getSource(x_cellSize,y_cellSize),Vector2{0, 0},0.0f,WHITE);
        if(IsKeyPressed(KEY_W)){
            fr_x = 35;
            fr_y = 520;
        }
        if(IsKeyPressed(KEY_S)){
            fr_x = 35;
            fr_y = 1;
        }

        if(IsKeyPressed(KEY_D)){
            fr_x = 900;
            fr_y = 520;
        }

        if(IsKeyPressed(KEY_A)){
            fr_x = 900;
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
        pos_x=a;
        pos_y=b;
        x=a;
        y=b;
        turn=false;
        team=color;
    } 


    void create(float x_cellSize,float y_cellSize/*, Texture2D hiro*/){
        currentPosition(x_cellSize, y_cellSize,team);
        //Rectangle image{fr_x,fr_y,480, 540};
        // DrawTexturePro(hiro,image,getSource(pos_x,pos_y-1,x_cellSize,y_cellSize),Vector2{0, 0},0.0f,WHITE);
        // if(IsKeyPressed(KEY_W)){
        //     fr_x = 35;
        //     fr_y = 520;
        // }
        // if(IsKeyPressed(KEY_S)){
        //     fr_x = 35;
        //     fr_y = 1;
        // }

        // if(IsKeyPressed(KEY_D)){
        //     fr_x = 900;
        //     fr_y = 520;
        // }

        // if(IsKeyPressed(KEY_A)){
        //     fr_x = 900;
        //     fr_y = 1;
        // }
    }
    //texture//

    //////////

    //attack//

    /////////


};


Hero Hiro(4,4,GREEN);
Monster Enemy(2,4,RED);
void Char(int x_cellSize,int y_cellSize,Texture2D hiro){
Hiro.create(x_cellSize,y_cellSize,hiro);
Enemy.create(x_cellSize,y_cellSize);
}
