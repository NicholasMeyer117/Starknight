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
#include "Item.h"
#define PI 3.14159265

using namespace sf;
using namespace std;

class Character
{
    public:
    int credits = 100; //purchase in-run items
    int crewSlots = 1;
    int attachmentSlots = 3;
    int starCrystals = 0; //purchase items for next run
    int voidShards = 0; //unlock new ships or crew members
    int shipType = 0; //fighter, tank, interceptor, smuggler, weaponsPlatform, commandShip, techShip
    
    std::vector<Attachment*> attachments;
    std::vector<Item*> items;
    std::array<bool, 4> crewUnlocks; //element corresponds to crew ID, to check if members are unlocked across a save file
    
    void resetCredits();




};
