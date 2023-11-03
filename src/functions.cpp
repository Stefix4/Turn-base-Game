#include <raylib.h>

#include "game.hpp"
#include "functions.hpp"

void toggleFullscreen(){
    if(IsKeyPressed(KEY_F11)){
        ToggleFullscreen();
    }
    if(IsWindowFullscreen()){
        screenWidth = GetRenderWidth();
        screenHeight = GetRenderHeight();
    }
    else{
        screenWidth = 1280;
        screenHeight = 780;
    }
}

void wait(float wait_time){
    double startTime = GetTime();
    double currentTime = GetTime();
    while(true){
        double elapsedTime = currentTime - startTime;
        if (elapsedTime >= wait_time) {
            break;
        }
    }
}