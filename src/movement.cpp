#include <raylib.h>

#include "movement.hpp"
#include "characters.hpp"
#include "map.hpp"
#include "game.hpp"

int x=4, y=4;

struct move{
    int up;
    int down;
    int left;
    int right;
};
move space;

 void movement(Texture2D hiro) {
    space.up = 1;
    space.down = mapSize;
    space.left = 1;
    space.right = mapSize;
    if(y > space.up)
        if (IsKeyPressed(KEY_W))
            y -= 1;
    if(y < space.down)
        if(IsKeyPressed(KEY_S)) 
            y += 1;
    if(x < space.right)
        if(IsKeyPressed(KEY_D))
            x += 1;
    if(x > space.left)
        if (IsKeyPressed(KEY_A)) 
            x -= 1;
    }
