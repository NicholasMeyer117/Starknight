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
#include "Attachment.h"
#define PI 3.14159265

using namespace sf;
using namespace std;

class Character
{
    public:
    int credits = 0; //purchase in-run items
    int crewSlots = 1;
    int upgradeSlots = 3;
    int weaponSlots = 3;
    int starCrystals = 0; //purchase items for next run
    int voidShards = 0; //unlock new ships or crew members
    
    std::vector<Attachment*> attachments;
    
    void resetCredits();




};
