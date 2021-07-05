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
#include "Actor.h"
#define PI 3.14159265

class Enemy: public Actor
{
    public:
    bool reachedBegin = false;
    int ticksSinceLastFire = 0;
    
    virtual void takeDamage(int damage){}
    
    virtual void enemySpawn(){}
    
    virtual void enemyMove(){}
    
    virtual void enemyAttack(){}
    

};