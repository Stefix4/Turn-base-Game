#pragma once

#include <raylib.h>
#include <string>
#include <map>
#include <functional>
#include <vector>



struct Observer{


    std::map<std::string,std::function<void()>>Events;

    std::map<std::pair<int,int>,bool>Obstacles;

    
    
    void add (int x=0, int y=0){
        if(x&&y)
            Obstacles[{x,y}]=true;
    }

    void add (const std::string& name,std::function<void()>fn){
        Events[name]=fn;
    }

    void remove(std::string name){
        if(Events.find(name)!=Events.end())
            Events.erase(name);
    
    }

    void remove(int x=0,int y=0){
        if(x&&y)
            if(Obstacles.find({x,y})!=Obstacles.end())
                Obstacles.erase({x,y});
    }
    
    void execute(std::string name){
        if(Events.find(name)!=Events.end())
           Events[name]();
    }
};

