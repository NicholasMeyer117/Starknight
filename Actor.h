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

class Actor: public Entity
{
    public:
    int health, shields;
    float speed, firerate, xPos, yPos;
    bool isEnemy;
    enum direction {up, down, left, right};
    
    void createActor(int Health, int Shields, float Speed, float Firerate, bool IsEnemy);

    void moveActor(enum direction);
    
    void update();



};
