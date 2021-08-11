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

//An Entity that moves and acts on in dynamic ways
class Actor: public Entity
{
    public:
    float maxHealth, health, shields;
    float speed, firerate, xPos, yPos;
    float damageMult, fireRateMult, bulletSpeedMult, speedMult, healthMult; 
    bool isEnemy;
    int ticksSinceLastHit = 0;
    int iFrames;
    enum direction {up, down, left, right};
    
    void createActor(int Health, int Shields, float Speed, float Firerate, bool IsEnemy, int IFrames,
    float damageMult = 1.0, float fireRateMult = 1.0, float bulletSpeedMult = 1.0, float speedMult = 1.0, float healthMult = 1.0);

    void moveActor(enum direction);
    
    void setActorPosition(float X, float Y);
    
    void update();



};
