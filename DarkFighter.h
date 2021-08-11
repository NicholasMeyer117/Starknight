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

class DarkFighter: public Enemy //number one!
{
    public:
    bool movingUp = true;
    Sprite bulletSprite;
    
    void takeDamage(float damage)
    {
        health = health - damage;
        if (health <= 0)
            life=0;
    }
    
    void enemySpawn(Sprite BulletSprite, int ScreenW, int ScreenH)
    {
        screenH = ScreenH;
        screenW = ScreenW;
        srand(time(NULL));
        int randNum = rand() % screenH/2 + 200;
        sprite.setPosition(screenW, randNum);
        setActorPosition(screenW, randNum);
        bulletSprite = BulletSprite;
        enemyType = darkFighter;
    }
    
    void enemyMove()
    {
        if (!reachedBegin)
        {
            moveActor(left);
            if (x <= screenW - screenW/10)
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
            DarkBullet *b = new DarkBullet();
            b->settings(bulletSprite,x,y,5, 5, angle, 3);
            b->createBullet (5, 20);
            entities->push_back(b);                
            bulletList->push_back(b);  
            ticksSinceLastFire = 0;  
        }
        else
            ticksSinceLastFire++;                   
    }
    
};
