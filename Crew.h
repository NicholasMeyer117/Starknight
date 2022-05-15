#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>

using namespace std;

class Crew
{
    public:
    int ID; //individual ID num
    String name;
    int crewNum; //slot number of this crew member
    String quote;
    String desc;
    String unlockReq;
    
    bool isUnlocked;
    bool showUnlockReq;
    
    virtual bool checkIfUnlocked();



};

class Gunner: public Crew
{

    public:
    Gunner()
    {
        ID = 0;
        name = "Gunner";
        quote = "Let me have the gun";
        desc = "10% damage increase";
        unlockReq = "";
        
        isUnlocked = true;
        showUnlockReq = NULL;

    }
    
    bool checkIfUnlocked()
    {
        return true;
    
    }

};

class Mechanic: public Crew
{

    public:
    Mechanic()
    {
        ID = 1;
        name = "Mechanic";
        quote = "A little tune-up can't hurt";
        desc = "10% fire-rate increase";
        unlockReq = "";
        
        isUnlocked = true;
        showUnlockReq = NULL;

    }
    
    bool checkIfUnlocked()
    {
        return true;
    
    }

};

class Pilot: public Crew
{

    public:
    Pilot()
    {
        ID = 2;
        name = "Pilot";
        quote = "Just let me fly, for both our sakes";
        desc = "20% movement speed increase";
        unlockReq = "";
        
        isUnlocked = true;
        showUnlockReq = NULL;

    }
    
    bool checkIfUnlocked()
    {
        return true;
    
    }

};

class Squire: public Crew
{

    public:
    Squire()
    {
        ID = 3;
        name = "Squire";
        quote = "Allow me to earn my knighthood";
        desc = "5% increase to all stats";
        unlockReq = "";
        
        isUnlocked = true;
        showUnlockReq = NULL;

    }
    
    bool checkIfUnlocked()
    {
        return true;
    
    }

};


