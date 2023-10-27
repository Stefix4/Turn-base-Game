#pragma once

#include <raylib.h>
#include <string>
#include <map>
#include <functional>
#include <vector>



struct Observer{


    std::map<std::string,std::function<void()>>Events;
   

    void add (const std::string& name,std::function<void()>fn){
        Events[name]=fn;
    }

    void remove(std::string name){
        if(Events.find(name)!=Events.end())
            Events.erase(name);
    
    }
    
    void execute(std::string name){
        if(Events.find(name)!=Events.end())
           Events[name]();
    }
};

