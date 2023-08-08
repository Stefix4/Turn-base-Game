#include <raylib.h>

#include "characters.hpp"
#include "map.hpp"

float start=4*cellSize;
Vector2 coords{start,start};
struct Character
{ 
    void draw(){
        DrawCircle(start,start,10,PINK);
    }
    void position(){

    }
};
Character Hiro;
void Char(){
Hiro.draw();
}
