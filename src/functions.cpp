#include <raylib.h>

#include "functions.hpp"


void toggleFullscreen(){
    if(IsKeyPressed(KEY_F11))
        ToggleFullscreen();
}
