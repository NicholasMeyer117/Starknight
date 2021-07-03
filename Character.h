#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include "Entity.h"
#define PI 3.14159265

using namespace sf;
using namespace std;

class Character
{
    public:
    int credits; //purchase in-run items
    int crewSlots;
    int upgradeSlots;
    int weaponSlots;
    int starCrystals; //purchase items for next run
    int voidShards; //unlock new ships or crew members
    
    void resetCredits();



};
