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
        srand(time(NULL));
        int randNum = rand() % screenH/2 + 200;
        sprite.setPosition(screenW, randNum);
        setActorPosition(screenW, randNum);
        bulletSprite = SpriteList[2];
        enemyType = doubleShooter;

    }
    
    void enemyMove()
    {
        if (!reachedBegin)
        {
            moveActor(left);
            int spawnZone = (screenW - screenW/10) - rand() %  screenW/5;
            if (x <= spawnZone)
                reachedBegin = true;
        }
        else
        {
            if (movingUp)
            {
                moveActor(up);
                if (y <= screenH/10)
                    movingUp = false;
            }
            else
            {
                moveActor(down);
                if (y >= screenH - screenH/10)
                    movingUp = true;
            }

        }
    }
    
    void enemyAttack(std::vector<Bullet*> *bulletList, std::vector<Entity*> *entities)
    {
        if (ticksSinceLastFire == firerate)
        { 
            DarkBullet *b1 = new DarkBullet();
            b1->settings(bulletSprite,x,y + 13,5, 5, angle, 3);
            b1->createBullet (2, 25);
            entities->push_back(b1);                
            bulletList->push_back(b1);   
        
            DarkBullet *b2 = new DarkBullet();
            b2->settings(bulletSprite,x,y - 13,5, 5, angle, 3);
            b2->createBullet (2, 25);
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
        else
            ticksSinceLastFire++;  
                    
    }

};
