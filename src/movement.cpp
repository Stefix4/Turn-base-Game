#include <raylib.h>

#include "movement.hpp"
#include "characters.hpp"
#include "map.hpp"
#include "game.hpp"


// struct move{
//     int up;
//     int down;
//     int left;
//     int right;
// };
// move space;

 void movement() {
    // space.up = 1;
    // space.down = mapSize;
    // space.left = 1;
    // space.right = mapSize;
    if(y > 1)
        if (IsKeyPressed(KEY_W))
            y -= 1;
    if(y < mapSize)
        if(IsKeyPressed(KEY_S)) 
            y += 1;
    if(x < mapSize)
        if(IsKeyPressed(KEY_D))
            x += 1;
    if(x > 1)
        if (IsKeyPressed(KEY_A)) 
            x -= 1;
    }
    
