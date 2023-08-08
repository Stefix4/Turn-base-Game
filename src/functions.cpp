#include <raylib.h>

#include "functions.hpp"


void toggle_fullscreen(){
    if(IsKeyPressed(KEY_F11))
        ToggleFullscreen();
}
