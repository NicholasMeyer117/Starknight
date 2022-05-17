#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include "Crew.h"

using namespace std;

class CrewHandler
{

    public:
    std::array<Crew*, 4> crewArray; //all crew
    std::vector<Crew*> crewList; //currently equipped cre
    
    CrewHandler()
    {
        Gunner *gunner = new Gunner();
        crewArray[0] = gunner;
        Mechanic *mechanic = new Mechanic();
        crewArray[1] = mechanic;
        Pilot *pilot = new Pilot();
        crewArray[2] = pilot;
        Squire *squire = new Squire();
        crewArray[3] = squire;

    }
    
    String getName(int num)
    {
        return crewArray[num]->name;
    }
    
    String getQuote(int num)
    {
        return crewArray[num]->quote;
    }
    
    String getDesc(int num)
    {
        return crewArray[num]->desc;
    }
    
    void checkCrew()
    {
    
    }
    
    void applyCrew(Actor *player)
    {
        for (int i = 0; i < crewList.size(); i++)
        {
            crewList.at(i)->applyCrew(player);
        
        }
    }



};
