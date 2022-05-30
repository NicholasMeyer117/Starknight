#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include <unistd.h>
#include "Entity.h"
#include "Actor.h"
#include "Enemy.h"
#define PI 3.14159265

class DoubleShooter: public Enemy
{

    public:
    bool movingUp = true;
    Sprite bulletSprite;
    int volleyNum = 0;
    
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
        bulletSprite = SpriteList[2];
        enemyType = doubleShooter;

    }
    
    void enemyMove(float elapsed)
    {
        if (!reachedBegin)
        {
            moveActor(left, elapsed);
            int spawnZone = screenW - (relUnitX * 5) - (rand() % (relUnitX * 100));
            if (x <= spawnZone)
                reachedBegin = true;
        }
        else
        {
            if (movingUp)
            {
                moveActor(up, elapsed);
                if (y <= relUnitY * 17)
                    movingUp = false;
            }
            else
            {
                moveActor(down, elapsed);
                if (y >= relUnitY * 90)
                    movingUp = true;
            }

        }
    }
    
    void enemyAttack(std::vector<Bullet*> *bulletList, std::vector<Entity*> *entities, bool advanceTick)
    {
        if (ticksSinceLastFire == firerate)
        { 
            DarkBullet *b1 = new DarkBullet();
            b1->settings(bulletSprite,x,y + 13,5, 5, angle, 3);
            b1->createBullet (5, 750);
            entities->push_back(b1);                
            bulletList->push_back(b1);   
        
            DarkBullet *b2 = new DarkBullet();
            b2->settings(bulletSprite,x,y - 13,5, 5, angle, 3);
            b2->createBullet (5, 750);
            entities->push_back(b2);                
            bulletList->push_back(b2); 
        
            if (volleyNum < 1)
            {
                volleyNum++;
                ticksSinceLastFire = firerate - 10;
            }
            else
            {
                ticksSinceLastFire = 0;
                volleyNum = 0;
            }
        }
        else if (advanceTick)
            ticksSinceLastFire++;  
                    
    }

};
