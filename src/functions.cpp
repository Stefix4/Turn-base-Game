#include <raylib.h>

#include "functions.hpp"
#include "characters.hpp"


void toggleFullscreen(){
    if(IsKeyPressed(KEY_F11))
        ToggleFullscreen();
}
