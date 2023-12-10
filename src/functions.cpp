#include <raylib.h>
#include <thread>
#include <future>

#include "game.hpp"
#include "functions.hpp"
#include "characters.hpp"
#include "map.hpp"

int UnModify_Board[7][7];

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

bool Check_Turn(){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return turn;
}                   
void check_movement(bool& turn){
    
}