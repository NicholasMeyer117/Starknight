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

extern float elapsedTime;

//An Entity that moves and acts on in dynamic ways
class Actor: public Entity
{
    public:
    float maxHealth, health, shields;
    float speed, firerate, xPos, yPos;
    float damageMult, fireRateMult, bulletSpeedMult, speedMult, healthMult, healingMult, utilityMult,aoeRadiusMult;
    bool isEnemy;
    int ticksSinceLastHit = 0;
    int iFrames;
    enum direction {up, down, left, right};
    
    //health, shields, speed, firerate, is enemy, IFrames, damageMult, fireRateMult, bulletSpeedMult, SpeedMult, HealthMult, HealingMult, utilityMult
    void createActor(int Health, int Shields, float Speed, float Firerate, bool IsEnemy, int IFrames,
    float DamageMult = 1.0, float FireRateMult = 1.0, float BulletSpeedMult = 1.0, float SpeedMult = 1.0, 
    float HealthMult = 1.0, float HealingMult = 1.0, float UtilityMult = 1.0,float AoeRadiusMult = 1.0);

    void moveActor(enum direction);
    
    void setActorPosition(float X, float Y);
    
    void update();



};
