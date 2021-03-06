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
#include "Bullets.h"
#define PI 3.14159265

class Swarmer: public Enemy //number one!
{
    public:
    bool movingUp = true;
    Sprite bulletSprite;
    int attackCounter= 0;
    
    void takeDamage(float damage)
    {
        health = health - damage;
        if (health <= 0)
            life=0;
    }
    
    void enemySpawn(std::vector<Sprite> SpriteList, int ScreenW, int ScreenH)
    {
        screenH = ScreenH;
        screenW = ScreenW;
        relUnitX = screenW/100;
        relUnitY = screenH/100;
        srand(time(NULL));
        int randNum = rand() % screenH/2 + 200;
        sprite.setPosition(screenW, randNum);
        setActorPosition(screenW, randNum);
        enemyType = swarmer;
    }
    
    void enemyMove(float elapsed)
    {
    
        if (attackCounter > 0)
        {
            //std::cout << "ATTACKING";
            if (attackCounter >= 150)
            {
            	moveActor(left);
            	moveActor(left);
            	moveActor(left);
            	moveActor(left);
            }
            else
            {
            	moveActor(right);
            	moveActor(right);
            	moveActor(right);
            	moveActor(right);
            }
            attackCounter--;
        }
        if (!reachedBegin)
        {
            moveActor(left);
            int spawnZone = screenW - (relUnitX * 5) - (rand() % (relUnitX * 100));
            if (x <= spawnZone)
                reachedBegin = true;
        }
        else
        {
            if (movingUp)
            {
                moveActor(up);
                if (y <= relUnitY * 17)
                    movingUp = false;
            }
            else
            {
                moveActor(down);
                if (y >= relUnitY * 90)
                    movingUp = true;
            }

        }
    }
    
    void enemyAttack(std::vector<Bullet*> *bulletList, std::vector<Entity*> *entities, bool advanceTick)
    {
    
        if (ticksSinceLastFire == firerate)
        { 
            std::cout << "ATTACK\n";
            if (attackCounter == 0)
                attackCounter = 300;
            ticksSinceLastFire = 0;  
        }
        else if (advanceTick)
            ticksSinceLastFire++;                   
    }
    
};
