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
    bool isEquipped = false;
    
    virtual bool checkIfUnlocked(){return false;}
    virtual void applyCrew(Actor *player){}



};

class Gunner: public Crew
{

    public:
    Gunner()
    {
        ID = 0;
        name = "Gunner";
        quote = "\"Let me have the gun\"";
        desc = "10% damage increase";
        unlockReq = "";

        isUnlocked = true;
        showUnlockReq = NULL;

    }
    
    bool checkIfUnlocked()
    {
        return true;
    
    }
    
    void applyCrew(Actor *player)
    {
        player->damageMult += 0.1;
    
    }

};

class Mechanic: public Crew
{

    public:
    Mechanic()
    {
        ID = 1;
        name = "Mechanic";
        quote = "\"A little tune-up can't hurt\"";
        desc = "10% fire-rate increase";
        unlockReq = "";
        
        isUnlocked = true;
        showUnlockReq = NULL;

    }
    
    bool checkIfUnlocked()
    {
        return true;
    
    }
    
    void applyCrew(Actor *player)
    {
        player->fireRateMult += 0.1;
    
    }

};

class Pilot: public Crew
{

    public:
    Pilot()
    {
        ID = 2;
        name = "Pilot";
        quote = "\"Just let me fly, for both our sakes\"";
        desc = "20% movement speed increase";
        unlockReq = "";
        
        isUnlocked = true;
        showUnlockReq = NULL;

    }
    
    bool checkIfUnlocked()
    {
        return true;
    
    }
    
    void applyCrew(Actor *player)
    {
        player->speedMult += 0.2;
    
    }


};

class Squire: public Crew
{

    public:
    Squire()
    {
        ID = 3;
        name = "Squire";
        quote = "\"Allow me to earn my knighthood\"";
        desc = "5% increase to all stats";
        unlockReq = "";
        
        isUnlocked = true;
        showUnlockReq = NULL;

    }
    
    bool checkIfUnlocked()
    {
        return true;
    
    }
    
    void applyCrew(Actor *player)
    {
        player -> damageMult += 0.05;
        player -> fireRateMult += 0.05;
        player -> speedMult += 0.05;
        player -> bulletSpeedMult += 0.05;
        player -> healthMult += 0.05;
        player -> healingMult += 0.05; 
        player -> utilityMult += 0.05;
    
    }


};


