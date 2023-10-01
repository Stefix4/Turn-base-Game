#include <raylib.h>
#include <functional>
#include <string>
#include <map>

#include "characters.hpp"
#include "map.hpp"
#include "game.hpp"
#include "Observer.hpp"



Observer events;
struct Character:Observer
{   
    bool turn;
    int hp;
    int dmg;
    float fr_x=35,fr_y=1;
    
    
    void currentPosition(float x_cellSize,float y_cellSize,Color team){
        DrawRectangleV(getPosition(pos_x,pos_y,x_cellSize,y_cellSize),Vector2{x_cellSize,y_cellSize},team);
    }
    void DrawTexture(float x_cellsize,float y_cellsize,Texture2D texture){
        Rectangle image{fr_x,fr_y,480, 540};
        DrawTexturePro(texture,image,getSource(x_cellSize,y_cellSize),Vector2{0, 0},0.0f,WHITE);
    
    }
    
    Rectangle getSource(float x_cellSize,float y_cellSize){
        Vector2 position={x_cellSize*(pos_x-1),y_cellSize*(pos_y-2)};
        return Rectangle{position.x,position.y,x_cellSize,y_cellSize*2};
    }
    Vector2 getPosition(int x,int y ,int x_cellSize,int y_cellSize){
        Vector2 coords;
        coords.x =x_cellSize*(pos_x-1);
        coords.y =y_cellSize*(pos_y-1);     
        return coords;
    }


    
};


struct Hero :Character {
    Color team;
    
    Hero(int a,int b,Color color){
        pos_x=a;
        pos_y=b;
        turn=true;
        team=color;
    } 
    
    void movement() {
        if(pos_y > 1)
            if (IsKeyPressed(KEY_W)){
                pos_y -= 1;turn=false;
            }
        if(pos_y < mapSize)
            if(IsKeyPressed(KEY_S)) {
                pos_y += 1;turn=false;
            }
        if(pos_x < mapSize)
            if(IsKeyPressed(KEY_D)){
                pos_x += 1;turn=false;
            }
        if(pos_x > 1)
            if (IsKeyPressed(KEY_A)) {
                pos_x -= 1;turn=false;
            }
    }
    void animation(){
        
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

    void create(float x_cellSize,float y_cellSize, Texture2D hiro){
        //currentPosition( x_cellSize, y_cellSize,team);
        //DrawText(TextFormat("%f",pos_x),1,1,50,PINK);
        DrawTexture(x_cellSize,y_cellSize,hiro);
        animation();
        events.add("movement_player",[=](){movement();});
        events.execute("movement_player");
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
        turn=false;
        team=color;
    }


    void create(float x_cellSize,float y_cellSize, Texture2D hiro){
        currentPosition(x_cellSize, y_cellSize,team);
        DrawTexture(x_cellSize,y_cellSize,hiro);
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
Enemy.create(x_cellSize,y_cellSize,hiro);
}

