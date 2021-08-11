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

class TriShooter: public Enemy
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
        enemyType = triShooter;
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
            DiagonalBullet *b1 = new DiagonalBullet();
            b1->settings(bulletSprite,x,y,5, 5, angle, 3);
            b1->createBullet (5, 2.5);
            b1->direction (false, true);
            entities->push_back(b1);                
            bulletList->push_back(b1);   
        
            DiagonalBullet *b2 = new DiagonalBullet();
            b2->settings(bulletSprite,x,y,5, 5, angle, 3);
            b2->createBullet (5, 2.5);
            b2->direction (false, false);
            entities->push_back(b2);                
            bulletList->push_back(b2);
        
            DarkBullet *b3 = new DarkBullet();
            b3->settings(bulletSprite,x,y,5, 5, angle, 3);
            b3->createBullet (5, 10);
            entities->push_back(b3);                
            bulletList->push_back(b3); 
        
            ticksSinceLastFire = 0;    
         }
         else
            ticksSinceLastFire++;                    
    }

};
