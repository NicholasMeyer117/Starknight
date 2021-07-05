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
#include "Enemy.h"
#define PI 3.14159265

class DarkFighter: public Enemy //number one!
{
    public:
    bool movingUp = true;
    
    void takeDamage(int damage)
    {
        health = health - damage;
        if (health <= 0)
            life=0;
    }
    
    void enemySpawn()
    {
        srand(time(NULL));
        int randNum = rand() % 400 + 200;
        sprite.setPosition(1200, randNum);
        setActorPosition(1200, randNum);
        cout << to_string(randNum);
    }
    
    void enemyMove()
    {
        if (!reachedBegin)
        {
            moveActor(left);
            if (x <= 1000)
                reachedBegin = true;
        }
        else
        {
            if (movingUp)
            {
                moveActor(up);
                if (y <= 100)
                    movingUp = false;
            }
            else
            {
                moveActor(down);
                if (y >= 700)
                    movingUp = true;
            }

        }
    }
    
};
