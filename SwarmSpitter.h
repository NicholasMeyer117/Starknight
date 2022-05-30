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

class SwarmSpitter: public Enemy //number one!
{
    public:
    bool movingUp = true;
    Sprite bulletSprite;
    Sprite subBulletSprite;
    std::vector<BombBullet*> bombBulletList;
    
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
        bulletSprite = SpriteList[4];
        subBulletSprite = SpriteList[2];
        enemyType = swarmSpitter;
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
        for (int i = 0; i < bombBulletList.size(); i++)
        {
            if (bombBulletList[i]->progressCounter == 0 || health <= 0)
	    {
	        for (int j = 0; j < 8; j++)
	        {
	            Bullet *b;
	            if (j==0)
	            	b = new OrdinalBullet("left");
	            else if (j==1)
	            	b = new OrdinalBullet("right");
	            else if (j==2)
	            	b = new OrdinalBullet("up");
	            else if (j==3)
	            	b = new OrdinalBullet("down");
	            	
	            if (j==4)
	            	b = new DiagonalBullet(true, true, 0.35);
	            else if (j==5)
	            	b = new DiagonalBullet(true, false, 0.35);
	            else if (j==6)
	            	b = new DiagonalBullet(false, true, 0.35);
	            else if (j==7)
	            	b = new DiagonalBullet(false, false, 0.35);
	            
	            b->settings(subBulletSprite,bombBulletList[i]->x,bombBulletList[i]->y,10, 10, angle, 3);
	            if (j < 4)
                        b->createBullet (10, 500);
                    else 
                        b->createBullet (10, 125);
	            bulletList->push_back(b);
	            entities->push_back(b);  
	        }
	        cout << "End life\n";
	        bombBulletList[i]->life = 0;
	        bombBulletList.erase(bombBulletList.begin()+i);
	    }
        }
        
        if (ticksSinceLastFire == firerate)
        { 
            BombBullet *b = new BombBullet();
            b->settings(bulletSprite,x,y,10, 10, angle, 3);
            b->createBullet (20, 500);
            entities->push_back(b);                
            bulletList->push_back(b); 
            bombBulletList.push_back(b); 
            ticksSinceLastFire = 0;  
        }
        else if (advanceTick)
            ticksSinceLastFire++;                   
    }
    
};
